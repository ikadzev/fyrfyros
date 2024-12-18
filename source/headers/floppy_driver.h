#include "_flags.h"
#include "intel8259A.h"
#include "printf.h"

#define FLPY_SECTORS_PER_TRACK 18

enum floppy_msr_mask {
    FLOPPY_MSR_MASK_DRIVE1_POS_MODE	=	0b00000001,
    FLOPPY_MSR_MASK_DRIVE2_POS_MODE	=	0b00000010,
    FLOPPY_MSR_MASK_DRIVE3_POS_MODE	=	0b00000100,
    FLOPPY_MSR_MASK_DRIVE4_POS_MODE	=	0b00001000,
    FLOPPY_MSR_MASK_BUSY			=	0b00010000,
    FLOPPY_MSR_MASK_DMA			    =	0b00100000,
    FLOPPY_MSR_MASK_DATAIO			=	0b01000000,
    FLOPPY_MSR_MASK_DATAREG		    =	0b10000000
};
// The registers of interest. There are more, but we only use these here.
enum floppy_registers {
    FLOPPY_BASE = 0x3F0, //
    FLOPPY_DOR  = 0x3F2,  // digital output register
    FLOPPY_MSR  = 0x3F4,  // master status register, read only
    FLOPPY_FIFO = 0x3F5,  // data FIFO, in DMA operation for commands
    FLOPPY_CCR  = 0x3F7   // configuration control register, write only
};
// The commands of interest. There are more, but we only use these here.
enum floppy_cmd {
    FDC_CMD_READ_TRACK	=	2,
    FDC_CMD_SPECIFY		=	3,
    FDC_CMD_CHECK_STAT	=	4,
    FDC_CMD_WRITE_SECT	=	5,
    FDC_CMD_READ_SECT	=	6,
    FDC_CMD_CALIBRATE	=	7,
    FDC_CMD_CHECK_INT	=	8,
    FDC_CMD_WRITE_DEL_S	=	9,
    FDC_CMD_READ_ID_S	=	0xa,
    FDC_CMD_READ_DEL_S	=	0xc,
    FDC_CMD_FORMAT_TRACK	=	0xd,
    FDC_CMD_SEEK		=	0xf
};
enum floppy_cmd_ext {
    FDC_CMD_EXT_SKIP	=	0x20,	//00100000
    FDC_CMD_EXT_DENSITY	=	0x40,	//01000000
    FDC_CMD_EXT_MULTITRACK	=	0x80	//10000000
};
enum FLPYDSK_SECTOR_DTL {
    FLPYDSK_SECTOR_DTL_128	=	0,
    FLPYDSK_SECTOR_DTL_256	=	1,
    FLPYDSK_SECTOR_DTL_512	=	2,
    FLPYDSK_SECTOR_DTL_1024	=	4
};
enum FLPYDSK_GAP3_LENGTH {

        FLPYDSK_GAP3_LENGTH_STD = 42,
        FLPYDSK_GAP3_LENGTH_5_14= 32,
        FLPYDSK_GAP3_LENGTH_3_5= 27
};

enum FLPYDSK_DOR_MASK {

    FLPYDSK_DOR_MASK_DRIVE0			=	0,	//00000000	= here for completeness sake
    FLPYDSK_DOR_MASK_DRIVE1			=	1,	//00000001
    FLPYDSK_DOR_MASK_DRIVE2			=	2,	//00000010
    FLPYDSK_DOR_MASK_DRIVE3			=	3,	//00000011
    FLPYDSK_DOR_MASK_RESET			=	4,	//00000100
    FLPYDSK_DOR_MASK_DMA			=	8,	//00001000
    FLPYDSK_DOR_MASK_DRIVE0_MOTOR		=	16,	//00010000
    FLPYDSK_DOR_MASK_DRIVE1_MOTOR		=	32,	//00100000
    FLPYDSK_DOR_MASK_DRIVE2_MOTOR		=	64,	//01000000
    FLPYDSK_DOR_MASK_DRIVE3_MOTOR		=	128	//10000000
};

//запускаем адову машину
void floppy_init(); //not working

//Шоб было видно, что так в них понаписанно
void floppy_print_DOR();
void floppy_print_MSR();

//работаем с Карласонном, то бишь с моторчиком дисководов
void floppy_motor_start(byte number);
void floppy_motor_end(byte number);

void expose__floppy_irq();
void clear__floppy_irq();
void floppy_wait_irq ();

//Магические функции включения передачи напрямую в память
void floppy_initialize_dma (); //no comments
void floppy_dma_read (); //no comments
void floppy_dma_write (); //no comments

//разделяем линейный адрес
void floppy_lba_to_chs (u32 lba, u32 *head, u32 *track, u32 *sector); //no comments

//Список офигительно нужных команд к этому динозавру
void flpydsk_read_sector_imp (byte head, byte track, byte sector); // not working
void flpydsk_write_ccr (u32 val);
void flpydsk_check_int (u32* st0, u32* cyl);
void flpydsk_drive_data (u32 stepr, u32 loadt, u32 unloadt, byte dma );
int flpydsk_calibrate (u32 drive);
void flpydsk_reset ();
byte* flpydsk_read_sector (int sectorLBA);