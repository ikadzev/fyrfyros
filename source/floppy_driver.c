#include "headers/floppy_driver.h"

void floppy_detect_drives() {

   outb(0x70, 0x10);
   unsigned drives = inb(0x71);

   print_fyr(" - Floppy drive 0: %s\r\n", drive_types[drives >> 4]);
   print_fyr(" - Floppy drive 1: %s\r\n", drive_types[drives & 0xf]);

}

void floppy_write_cmd(char cmd) {
    if(0x80 & inb(FLOPPY_MSR)) return (void) outb(FLOPPY_FIFO, cmd);
}

byte floppy_read_data() {
    if(0x80 & inb(FLOPPY_MSR)) return inb(FLOPPY_FIFO);
}

void floppy_check_interrupt(int *st0, int *cyl) {
    
    floppy_write_cmd(CMD_SENSE_INTERRUPT);

    *st0 = floppy_read_data();
    *cyl = floppy_read_data();
}

// Move to cylinder 0, which calibrates the drive..
void floppy_calibrate() {
    floppy_motor(1);
    floppy_write_cmd(CMD_RECALIBRATE);
    floppy_write_cmd(0);
    // irq_wait(floppy_irq);
    int st0, cyl;
    floppy_check_interrupt(&st0, &cyl);
    floppy_motor(0);
}

void floppy_reset() {

    outb(FLOPPY_DOR, 0x00); // disable controller
    outb(FLOPPY_DOR, 0x0C); // enable controller

    // set transfer speed 500kb/s
    outb(FLOPPY_CCR, 0x00);

    //  - 1st byte is: bits[7:4] = steprate, bits[3:0] = head unload time
    //  - 2nd byte is: bits[7:1] = head load time, bit[0] = no-DMA
    // 
    //  steprate    = (8.0ms - entry*0.5ms)*(1MB/s / xfer_rate)
    //  head_unload = 8ms * entry * (1MB/s / xfer_rate), where entry 0 -> 16
    //  head_load   = 1ms * entry * (1MB/s / xfer_rate), where entry 0 -> 128
    //
    floppy_write_cmd(CMD_SPECIFY);
    floppy_write_cmd(0xdf); /* steprate = 3ms, unload time = 240ms */
    floppy_write_cmd(0x02); /* load time = 16ms, no-DMA = 0 */
    floppy_calibrate();
}


void floppy_motor(int on) { 
    if(on) {
        outb(FLOPPY_DOR, 0x1c);
    } else {
        outb(FLOPPY_DOR, 0x0c);
    }
}

// Seek for a given cylinder, with a given head
void floppy_seek(int base, unsigned cyli, int head) {
    floppy_motor(1);
    floppy_write_cmd(CMD_SEEK);
    floppy_write_cmd(head<<2);
    floppy_write_cmd(cyli);
    // irq_wait(floppy_irq);
    int st0, cyl;
    floppy_check_interrupt(&st0, &cyl);
    floppy_motor(0);
}

// // Used by floppy_dma_init and floppy_do_track to specify direction
// typedef enum {
//     floppy_dir_read = 1,
//     floppy_dir_write = 2
// } floppy_dir;


// // we statically reserve a totally uncomprehensive amount of memory
// // must be large enough for whatever DMA transfer we might desire
// // and must not cross 64k borders so easiest thing is to align it
// // to 2^N boundary at least as big as the block
// #define floppy_dmalen 0x4800
// static const char floppy_dmabuf[floppy_dmalen]
//                   __attribute__((aligned(0x8000)));

// static void floppy_dma_init(floppy_dir dir) {

//     union {
//         unsigned char b[4]; // 4 bytes
//         unsigned long l;    // 1 long = 32-bit
//     } a, c; // address and count

//     a.l = (unsigned) &floppy_dmabuf;
//     c.l = (unsigned) floppy_dmalen - 1; // -1 because of DMA counting

//     // check that address is at most 24-bits (under 16MB)
//     // check that count is at most 16-bits (DMA limit)
//     // check that if we add count and address we don't get a carry
//     // (DMA can't deal with such a carry, this is the 64k boundary limit)
//     if((a.l >> 24) || (c.l >> 16) || (((a.l&0xffff)+c.l)>>16)) {
//         panic("floppy_dma_init: static buffer problem\n");
//     }

//     unsigned char mode;
//     switch(dir) {
//         // 01:0:0:01:10 = single/inc/no-auto/to-mem/chan2
//         case floppy_dir_read:  mode = 0x46; break;
//         // 01:0:0:10:10 = single/inc/no-auto/from-mem/chan2
//         case floppy_dir_write: mode = 0x4a; break;
//         default: panic("floppy_dma_init: invalid direction");
//                  return; // not reached, please "mode user uninitialized"
//     }

//     out8_p(0x0a, 0x06);   // mask chan 2

//     out8_p(0x0c, 0xff);   // reset flip-flop
//     out8_p(0x04, a.b[0]); //  - address low byte
//     out8_p(0x04, a.b[1]); //  - address high byte

//     out8_p(0x81, a.b[2]); // external page register

//     out8_p(0x0c, 0xff);   // reset flip-flop
//     out8_p(0x05, c.b[0]); //  - count low byte
//     out8_p(0x05, c.b[1]); //  - count high byte

//     out8_p(0x0b, mode);   // set mode (see above)

//     out8_p(0x0a, 0x02);   // unmask chan 2
// }

// // This monster does full cylinder (both tracks) transfer to
// // the specified direction (since the difference is small).
// //
// // It retries (a lot of times) on all errors except write-protection
// // which is normally caused by mechanical switch on the disk.
// //
// int floppy_do_track(int base, unsigned cyl, floppy_dir dir) {
    
//     // transfer command, set below
//     unsigned char cmd;

//     // Read is MT:MF:SK:0:0:1:1:0, write MT:MF:0:0:1:0:1
//     // where MT = multitrack, MF = MFM mode, SK = skip deleted
//     // 
//     // Specify multitrack and MFM mode
//     static const int flags = 0xC0;
//     switch(dir) {
//         case floppy_dir_read:
//             cmd = CMD_READ_DATA | flags;
//             break;
//         case floppy_dir_write:
//             cmd = CMD_WRITE_DATA | flags;
//             break;
//         default: 

//             panic("floppy_do_track: invalid direction");
//             return 0; // not reached, but pleases "cmd used uninitialized"
//     }

//     // seek both heads
//     if(floppy_seek(base, cyl, 0)) return -1
//     if(floppy_seek(base, cyl, 1)) return -1

//     int i;
//     for(i = 0; i < 20; i++) {
//         floppy_motor(base, motor_on);

//         // init dma..
//         floppy_dma_init(dir);

//         timer_sleep(10); // give some time (100ms) to settle after the seeks

//         floppy_write_cmd(base, cmd);  // set above for current direction
//         floppy_write_cmd(base, 0);    // 0:0:0:0:0:HD:US1:US0 = head and drive
//         floppy_write_cmd(base, cyl);  // cylinder
//         floppy_write_cmd(base, 0);    // first head (should match with above)
//         floppy_write_cmd(base, 1);    // first sector, strangely counts from 1
//         floppy_write_cmd(base, 2);    // bytes/sector, 128*2^x (x=2 -> 512)
//         floppy_write_cmd(base, 18);   // number of tracks to operate on
//         floppy_write_cmd(base, 0x1b); // GAP3 length, 27 is default for 3.5"
//         floppy_write_cmd(base, 0xff); // data length (0xff if B/S != 0)
        
//         irq_wait(floppy_irq); // don't SENSE_INTERRUPT here!

//         // first read status information
//         unsigned char st0, st1, st2, rcy, rhe, rse, bps;
//         st0 = floppy_read_data(base);
//         st1 = floppy_read_data(base);
//         st2 = floppy_read_data(base);
//         /*
//          * These are cylinder/head/sector values, updated with some
//          * rather bizarre logic, that I would like to understand.
//          *
//          */
//         rcy = floppy_read_data(base);
//         rhe = floppy_read_data(base);
//         rse = floppy_read_data(base);
//         // bytes per sector, should be what we programmed in
//         bps = floppy_read_data(base);

//         int error = 0;

//         if(st0 & 0xC0) {
//             static const char * status[] =
//             { 0, "error", "invalid command", "drive not ready" };
//             printk("floppy_do_sector: status = %s\n", status[st0 >> 6]);
//             error = 1;
//         }
//         if(st1 & 0x80) {
//             printk("floppy_do_sector: end of cylinder\n");
//             error = 1;
//         }
//         if(st0 & 0x08) {
//             printk("floppy_do_sector: drive not ready\n");
//             error = 1;
//         }
//         if(st1 & 0x20) {
//             printk("floppy_do_sector: CRC error\n");
//             error = 1;
//         }
//         if(st1 & 0x10) {
//             printk("floppy_do_sector: controller timeout\n");
//             error = 1;
//         }
//         if(st1 & 0x04) {
//             printk("floppy_do_sector: no data found\n");
//             error = 1;
//         }
//         if((st1|st2) & 0x01) {
//             printk("floppy_do_sector: no address mark found\n");
//             error = 1;
//         }
//         if(st2 & 0x40) {
//             printk("floppy_do_sector: deleted address mark\n");
//             error = 1;
//         }
//         if(st2 & 0x20) {
//             printk("floppy_do_sector: CRC error in data\n");
//             error = 1;
//         }
//         if(st2 & 0x10) {
//             printk("floppy_do_sector: wrong cylinder\n");
//             error = 1;
//         }
//         if(st2 & 0x04) {
//             printk("floppy_do_sector: uPD765 sector not found\n");
//             error = 1;
//         }
//         if(st2 & 0x02) {
//             printk("floppy_do_sector: bad cylinder\n");
//             error = 1;
//         }
//         if(bps != 0x2) {
//             printk("floppy_do_sector: wanted 512B/sector, got %d", (1<<(bps+7)));
//             error = 1;
//         }
//         if(st1 & 0x02) {
//             printk("floppy_do_sector: not writable\n");
//             error = 2;
//         }

//         if(!error) {
//             floppy_motor(base, floppy_motor_off);
//             return 0;
//         }
//         if(error > 1) {
//             printk("floppy_do_sector: not retrying..\n");
//             floppy_motor(base, floppy_motor_off);
//             return -2;
//         }
//     }

//     printk("floppy_do_sector: 20 retries exhausted\n");
//     floppy_motor(base, floppy_motor_off);
//     return -1;

// }

// int floppy_read_track(int base, unsigned cyl) {
//     return floppy_do_track(base, cyl, floppy_dir_read);
// }

// int floppy_write_track(int base, unsigned cyl) {
//     return floppy_do_track(base, cyl, floppy_dir_write);
// }
