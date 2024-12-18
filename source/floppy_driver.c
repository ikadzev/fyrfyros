#include "headers/floppy_driver.h"
#include "headers/printf.h"
#include "headers/loger.h"

byte _floppy_irq;

void floppy_init() {
    floppy_initialize_dma();
    flpydsk_reset();
    flpydsk_drive_data (13, 1, 0xf, 1);
    //outb(FLOPPY_FIFO, CMD_VERSION); // raboyaet
    //byte status = inb(FLOPPY_FIFO);
    //if (status != 0x90) {
    //    print_fyr("ERROR");
    //    for(;;);
    //}
    //log_massage("answer: ",inb(FLOPPY_DOR),1);
    //log_massage("", inb(FLOPPY_MSR), 1);
}

void floppy_send_command (byte cmd) {
    for (int i = 0; i < 500; i++ )
        if (inb(FLOPPY_MSR) & FLOPPY_MSR_MASK_DATAREG)
            return outb(FLOPPY_FIFO, cmd);
    log_warning("very bad", -1, 0);
}
byte floppy_read_data () {
    for (int i = 0; i < 500; i++ ) {
        if (inb(FLOPPY_MSR) & FLOPPY_MSR_MASK_DATAREG) {
            return inb(FLOPPY_FIFO);
        }
    }
    log_warning("very bad", -1, 0);
}

void floppy_print_DOR(){
    int i = inb(FLOPPY_DOR);
    log_massage("Using disk: ", i & 0b11, 1);
    log_massage("Reset/enable(0/1) controller: ", (i & 0b100) != 0, 0);
    log_massage("IRQ/DMA(0/1) mode: ", (i & 0b1000) != 0, 0);
    log_massage("Motor disk 0 enable status: ", (i & 0b10000) != 0, 0);
    log_massage("Motor disk 1 enable status: ", (i & 0b100000) != 0, 0);
    log_massage("Motor disk 2 enable status: ", (i & 0b1000000) != 0, 0);
    log_massage("Motor disk 3 enable status: ", (i & 0b10000000) != 0, 0);
}
void floppy_print_MSR(){
    int i = inb(FLOPPY_MSR);
    log_massage("FDD 0 is busy in seek mode: ", i & 1, 1);
    log_massage("FDD 1 is busy in seek mode: ", (i >> 1) & 1, 0);
    log_massage("FDD 2 is busy in seek mode: ", (i >> 2) & 1, 0);
    log_massage("FDD 3 is busy in seek mode: ", (i >> 3) & 1, 0);
    log_massage("FDC read or write command in progress: ", (i >> 4) & 1, 0);
    log_massage("FDC in Non DMA mode: ", (i >> 5) & 1, 0);
    log_massage("DIO: direction of data transfer between the FDC IC and the CPU: ", (i >> 6) & 1, 0);
    log_massage("RQM: Data register is ready for data transfer: ", (i >> 7) & 1, 0);
}

void floppy_motor_start(byte number) {
    log_massage("Start floppy_motor_start", -1, 0);
    if (number > 3) {
        log_warning("The disk does not exist", -1, 0);
        return;
    }
    byte old_cond = inb(FLOPPY_DOR);
    log_massage_cond((old_cond & 3) != number, "The wrong disk is selected", -1, 0);
    outb(FLOPPY_DOR, old_cond | 1 << (number + 4));
    for (int i = 0; i < 2000000; ++i){
        outb(0x80, 0);
    }
    log_massage("now cond FLOPPY_DOR: ", inb(FLOPPY_DOR), 0);
    log_massage("End floppy_motor_start", -1, 0);
}
void floppy_motor_end(byte number) {
    log_massage("Start floppy_motor_end", -1, 0);
    if (number > 3) {
        log_warning("The disk does not exist", -1, 0);
        return;
    }
    byte old_cond = inb(FLOPPY_DOR);
    log_massage_cond((old_cond & 3) != number, "The wrong disk is selected", -1, 0);
    //outb(FLOPPY_DOR, old_cond & (-1 ^ (1 << (number + 4))));
    log_massage("Now cond FLOPPY_DOR: ", inb(FLOPPY_DOR), 0);
    log_massage("End floppy_motor_end", -1, 0);
}

void expose__floppy_irq() {
    log_massage("expose _floppy_irq", -1, 0);
    _floppy_irq = 1;
}
void clear__floppy_irq() {
    log_massage("clear _floppy_irq", -1, 0);
    _floppy_irq = 0;
}
void floppy_wait_irq () {
    cli();
    log_massage("start wait 0x26", -1, 0);
    sti();
    while (!_floppy_irq);
    log_massage("end wait 0x26", -1, 0);
}

void floppy_initialize_dma () {
    outb (0x0a,0x06);	//mask dma channel 2
    outb (0xd8,0xff);	//reset master flip-flop
    outb (0x04, 0);     //address=0x1000
    outb (0x04, 0x10);
    outb (0xd8, 0xff);  //reset master flip-flop
    outb (0x05, 0xff);  //count to 0x23ff (number of bytes in a 3.5" floppy disk track)
    outb (0x05, 0x23);
    outb (0x80, 0);     //external page register = 0
    outb (0x0a, 0x02);  //unmask dma channel 2
}
void floppy_dma_read () {
    outb (0x0a, 0x06); //mask dma channel 2
    outb (0x0b, 0x56); //single transfer, address increment, autoinit, read, channel 2
    outb (0x0a, 0x02); //unmask dma channel 2
}
void floppy_dma_write () {
    outb (0x0a, 0x06); //mask dma channel 2
    outb (0x0b, 0x5a); //single transfer, address increment, autoinit, write, channel 2
    outb (0x0a, 0x02); //unmask dma channel 2
}

void floppy_lba_to_chs (u32 lba, u32* head, u32* track, u32* sector) {
    *head = ( lba % ( FLPY_SECTORS_PER_TRACK * 2 ) ) / ( FLPY_SECTORS_PER_TRACK );
    *track = lba / ( FLPY_SECTORS_PER_TRACK * 2 );
    *sector = lba % FLPY_SECTORS_PER_TRACK + 1;
}

/*
    Формат: МФ 0 0 0 1 1 0
    Параметры:
        xxxxx HD DR DR0
        Цилиндр
        Голова
        Номер сектора
        Размер сектора
        Длина пути
        Длина GAP3
        Длина данных
    Возвращаться:
        Возврат байта 0: ST0
        Возврат байта 1: ST1
        Возврат байта 2: ST2
        Возвращаемый байт 3: Текущий цилиндр
        Возвращаемый байт 4: Текущая глава
        Возвращаемый байт 5: Номер сектора
        Возвращаемый байт 6: Размер сектора
 */

void flpydsk_write_ccr (u32 val) {

    //! записываем управление конфигурацией
    outb(FLOPPY_CCR, val);
}
void flpydsk_check_int (u32* st0, u32* cyl) {
    floppy_send_command(FDC_CMD_CHECK_INT);
    *st0 = floppy_read_data();
    *cyl = floppy_read_data ();
}
void flpydsk_drive_data (u32 stepr, u32 loadt, u32 unloadt, byte dma ) {
    u32 data = 0;
    floppy_send_command(FDC_CMD_SPECIFY);
    data = ( (stepr & 0xf) << 4) | (unloadt & 0xf);
    floppy_send_command(data);
    data = (loadt) << 1 | (dma) ? 0 : 1;
    floppy_send_command (data);
}
int flpydsk_calibrate (u32 drive) {
    clear__floppy_irq();
    u32 st0, cyl;
    if (drive >= 4) return -2;
    floppy_motor_start(0);
    for (int i = 0; i < 10; i++) {
        floppy_send_command( FDC_CMD_CALIBRATE );
        floppy_send_command ( drive );
        floppy_wait_irq();
        flpydsk_check_int ( &st0, &cyl);
        if (!cyl) {
            floppy_motor_end(0);
            return 0;
        }
    }
    floppy_motor_end(0);
    return -1;
}
void flpydsk_reset () {
    clear__floppy_irq();
    u32 st0, cyl;

    //! reset the controller
    outb(FLOPPY_DOR, 0);
    outb(FLOPPY_DOR, FLPYDSK_DOR_MASK_RESET | FLPYDSK_DOR_MASK_DMA);
    floppy_wait_irq();
    //! send CHECK_INT/SENSE INTERRUPT command to all drives
    for (int i=0; i<4; i++)
        flpydsk_check_int (&st0,&cyl);
    //! transfer speed 500kb/s
    flpydsk_write_ccr (0);
    //! pass mechanical drive info. steprate=3ms, unload time=240ms, load time=16ms
    flpydsk_drive_data (3,16,240,TRUE);

    //! calibrate the disk
    flpydsk_calibrate (0);
}
int flpydsk_seek ( u32 cyl, u32 head ) {
    clear__floppy_irq();
    u32 st0, cyl0;

   // if (_CurrentDrive >= 4)
   //     return -1;

    for (int i = 0; i < 10; i++ ) {

        //! send the command
        floppy_send_command(FDC_CMD_SEEK);
        floppy_send_command( (head) << 2);
        floppy_send_command(cyl);

        //! wait for the results phase IRQ
        floppy_wait_irq();
        flpydsk_check_int (&st0,&cyl0);

        //! found the cylinder?
        if ( cyl0 == cyl)
            return 0;
    }

    return -1;
}

void flpydsk_read_sector_imp (byte head, byte track, byte sector) {

    u32 st0, cyl;
    clear__floppy_irq();
    //! set the DMA for read transfer
    floppy_dma_read ();

    //! read in a sector
    floppy_send_command(
            FDC_CMD_READ_SECT | FDC_CMD_EXT_MULTITRACK |
            FDC_CMD_EXT_SKIP | FDC_CMD_EXT_DENSITY);
    floppy_send_command (head << 2);
    floppy_send_command (track);
    floppy_send_command (head);
    floppy_send_command (sector);
    floppy_send_command (FLPYDSK_SECTOR_DTL_512 );
    floppy_send_command (sector + 1 >= 18 ? 18 : sector + 1 );
    floppy_send_command (27);
    floppy_send_command (0xff);

    //! wait for irq
    floppy_wait_irq();

    //! read status info
    for (int j=0; j<7; j++) floppy_read_data();

    //! let FDC know we handled interrupt
    flpydsk_check_int (&st0,&cyl);
}

byte* flpydsk_read_sector (int sectorLBA) {

    //if (_CurrentDrive >= 4)
        //return 0;

    //! convert LBA sector to CHS
    int head=0, track=0, sector=1;
    floppy_lba_to_chs(sectorLBA, &head, &track, &sector);

    //! turn motor on and seek to track
    floppy_motor_start(0);
    if (flpydsk_seek (track, head) != 0)
        return 0;

    //! read sector and turn motor off
    flpydsk_read_sector_imp (head, track, sector);
    floppy_motor_end(0);

    //! warning: this is a bit hackish
    return (byte *) 0x1000;
}