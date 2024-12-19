#include "headers/floppy_driver.h"
#include "headers/asm_fync.h"
#include "headers/printf.h"
#include "headers/dma_driver.h"
#include "headers/loger.h"

/* globals */
static volatile byte call_interupt_6 = FALSE;
static byte status[7] = { 0 };
static byte statsz = 0;
static byte sr0 = 0;
static byte fdc_track = 0xff;
static DrvGeom geometry = { DG144_HEADS,DG144_TRACKS,DG144_SPT };

u32 tbaddr = 0x1000L;    /* physical address of track buffer located below 1M */

void floppy_send_cmd(u32 byte);
u16 floppy_read_data();
void floppy_irq(void);
byte floppy_universal_waiting(byte sensei);
byte floppy_rw_interface(u32 block,byte *buffer,byte read, u32 count);

void floppy_init(void) {
   floppy_reset();
   floppy_send_cmd(CMD_VERSION);
   u32 ver = floppy_read_data();
   log_massage("Initialising Floppy driver...  ", -1, 0);
   if (ver == 0x80) {
       log_massage("NEC765 controller found\n", -1, 0);
   } else {
       log_massage("Enhanced controller found", -1, 0);
   }
} //+

void floppy_send_cmd(u32 byte) {
    u32 msr;
    for (u32 tmo = 0;tmo < 128;tmo++) {
        msr = inb(FDC_MSR);
        if ((msr & 0xc0) == 0x80) {
            outb(FDC_DATA,byte);
            return;
        }
        inb(0x80);   /* delay */
    }
} //+
u16 floppy_read_data() {
    u16 msr;
    for (u32 tmo = 0;tmo < 128; tmo++) {
        msr = inb(FDC_MSR);
        if ((msr & 0xd0) == 0xd0) {
            return inb(FDC_DATA);
        }
        inb(0x80);
    }
    return -1;
} //+

byte floppy_universal_waiting(byte sensei) {
    while (!call_interupt_6) ; // wait for IRQ6 handler to signal command finished
    statsz = 0; // read in command result bytes
    while ((statsz < 7) && (inb(FDC_MSR) & (1<<4))) {
        status[statsz++] = floppy_read_data();
    }
    if (sensei) { // send a "sense interrupt status" command
        floppy_send_cmd(CMD_SENSEI);
        log_massage("MSR: ", inb(FDC_MSR), 0);
        sr0 = floppy_read_data();
        log_massage("sr0:", sr0, 0);
        //fdc_track = floppy_read_data();
        //log_massage("fds_track:", fdc_track, 0);
    }
    call_interupt_6 = FALSE;
    return TRUE;
}

void floppy_irq(void) {
   call_interupt_6 = TRUE;
}
void block_to_hts(u32 block,u32 *head,u32 *track,u32 *sector)
{
   *head = (block % (geometry.spt * geometry.heads)) / (geometry.spt);
   *track = block / (geometry.spt * geometry.heads);
   *sector = block % geometry.spt + 1;
}

void floppy_reset(void) {
    outb(FDC_DOR,0); // stop the motor and disable IRQ/DMA
    outb(FDC_DRS,0); // program data rate (500K/s)
    outb(FDC_DOR,0x0c); //* re-enable u32errupts
    floppy_universal_waiting(TRUE); // floppy_resetting triggered an u32errupt - handle it
    // specify drive timings (got these off the BIOS)
    floppy_send_cmd(CMD_SPECIFY);
    floppy_send_cmd(0xdf);    // SRT = 3ms, HUT = 240ms
    floppy_send_cmd(0x02);    // HLT = 16ms, ND = 0
    floppy_seek(1);           // clear "disk change" status
    floppy_recalibrate();
}
void floppy_motor_start(byte number) {
    log_massage("Start floppy_motor_start", -1, 0);
    if (number > 3) {
        log_warning("The disk does not exist", -1, 0);
        return;
    }
    byte old_cond = inb(FDC_DOR);
    log_massage_cond((old_cond & 3) != number, "The wrong disk is selected", -1, 0);
    outb(FDC_DOR, old_cond | 1 << (number + 4));
    for (int i = 0; i < 2000000; ++i){
        outb(0x80, 0);
    }
    log_massage("now cond FLOPPY_DOR: ", inb(FDC_DOR), 0);
    log_massage("End floppy_motor_start", -1, 0);
}
void floppy_motor_stop(byte number) {
    log_massage("Start floppy_motor_end", -1, 0);
    if (number > 3) {
        log_warning("The disk does not exist", -1, 0);
        return;
    }
    byte old_cond = inb(FDC_DOR);
    log_massage_cond((old_cond & 3) != number, "The wrong disk is selected", -1, 0);
    outb(FDC_DOR, old_cond & (-1 ^ (1 << (number + 4))));
    log_massage("Now cond FLOPPY_DOR: ", inb(FDC_DOR), 0);
    log_massage("End floppy_motor_end", -1, 0);
}
void floppy_recalibrate(void) {
   floppy_motor_start(0);
   floppy_send_cmd(CMD_RECAL);
   floppy_send_cmd(0);
   floppy_universal_waiting(TRUE);
   floppy_motor_stop(0);
}
byte floppy_seek(u32 track) {
   floppy_send_cmd(CMD_SEEK);
   floppy_send_cmd(0);
   floppy_send_cmd(track);
    return TRUE;
}
byte floppy_read_block(u32 block,byte *buffer, u32 count) {
	u32 track=0, sector=0, head=0, track2=0, result=0, loop=0;
	block_to_hts(block, &head, &track, &sector);
	block_to_hts(block+count, &head, &track2, &sector);
	if(track!=track2)
	{
		for(loop=0; loop<count; loop++)
			result = floppy_rw_interface(block+loop, buffer+(loop*512), TRUE, 1);
		return result;
	}
   return floppy_rw_interface(block,buffer,TRUE,count);
}
byte floppy_write_block(u32 block,byte *buffer, u32 count) {
   return floppy_rw_interface(block,buffer,FALSE, count);
}
byte floppy_rw_interface(u32 block,byte *buffer, byte read, u32 count) {
    u32 head,track,sector,tries, copycount = 0;
    byte *p_tbaddr = (byte*)tbaddr;
    byte *p_buffer = buffer;
    block_to_hts(block,&head,&track,&sector);
    floppy_motor_start(0);
    if (!read && buffer) {
        /* copy data from data buffer u32o track buffer */
        for(copycount=0; copycount<(count*512); copycount++) {
            *p_tbaddr = *p_buffer;
            p_buffer++;
            p_tbaddr++;
        }
    }
    for (tries = 0;tries < 3;tries++) {
        if (inb(FDC_DIR) & 0x80) {
            floppy_seek(1);  /* clear "disk change" status */
            floppy_recalibrate();
            floppy_motor_stop(0);
            print_fyr("FDC: Disk change detected. Trying again.\n");

            return floppy_rw_interface(block, buffer, read, count);
        }
        if (!floppy_seek(track)) {
            floppy_motor_stop(0);
            print_fyr("FDC: Error floppy_seeking to track\n");
            return FALSE;
        }
        outb(FDC_CCR,0); // program data rate (500K/s)
        if (read) {
            dma_xfer(2,tbaddr,count*512,FALSE);
            floppy_send_cmd(CMD_READ);
        } else {
            dma_xfer(2,tbaddr,count*512,TRUE);
            floppy_send_cmd(CMD_WRITE);
        }
        floppy_send_cmd(head << 2);
        floppy_send_cmd(track);
        floppy_send_cmd(head);
        floppy_send_cmd(sector);
        floppy_send_cmd(2);               /* 512 bytes/sector */
        floppy_send_cmd(geometry.spt);
        if (geometry.spt == DG144_SPT)
            floppy_send_cmd(DG144_GAP3RW);  /* gap 3 size for 1.44M read/write */
        else
            floppy_send_cmd(DG168_GAP3RW);  /* gap 3 size for 1.68M read/write */
        floppy_send_cmd(0xff);            /* DTL = unused */
        /* wait for command completion */
        /* read/write don't need "sense u32errupt status" */
        if (!floppy_universal_waiting(TRUE)) {
            print_fyr("Timed out, trying operation again after floppy_reset()\n");
            floppy_reset();
            return floppy_rw_interface(block, buffer, read, count);
        }
        if ((status[0] & 0xc0) == 0) break;   /* worked! outta here! */
        floppy_recalibrate();  /* oops, try again... */
    }

    floppy_motor_stop(0);
    if (read && buffer) {
        /* copy data from track buffer u32o data buffer */
        p_buffer = buffer;
        p_tbaddr = (byte*)tbaddr;
        for(copycount=0; copycount<(count*512); copycount++) {
            *p_buffer = *p_tbaddr;
            p_buffer++;
            p_tbaddr++;
        }
    }

    return (tries != 3);
}