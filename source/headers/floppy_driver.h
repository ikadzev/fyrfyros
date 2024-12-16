#include "intel8259A.h"
#include "printf.h"

static const int floppy_base = 0x03f0; // standard base address of the primary floppy controller
static const int floppy_irq = 26; // standard IRQ number for floppy controllers

// The registers of interest. There are more, but we only use these here.
enum floppy_registers {
    FLOPPY_BASE = 0x3F0,
    FLOPPY_DOR  = 0x3F2,  // digital output register
    FLOPPY_MSR  = 0x3F4,  // master status register, read only
    FLOPPY_FIFO = 0x3F5,  // data FIFO, in DMA operation for commands
    FLOPPY_CCR  = 0x3F7   // configuration control register, write only
};

// The commands of interest. There are more, but we only use these here.
enum floppy_commands {
   CMD_SPECIFY = 3,            // SPECIFY
   CMD_WRITE_DATA = 5,         // WRITE DATA
   CMD_READ_DATA = 6,          // READ DATA
   CMD_RECALIBRATE = 7,        // RECALIBRATE
   CMD_SENSE_INTERRUPT = 8,    // SENSE INTERRUPT
   CMD_SEEK = 15,              // SEEK
};

static const char * drive_types[8] = {
    "none",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",

    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "unknown type",
    "unknown type"
};

void floppy_detect_drives();
void floppy_write_cmd(char);
byte floppy_read_cmd();
void floppy_check_interrupt(int*, int*);
void floppy_calibrate();
void floppy_reset();
void floppy_motor(int);
void floppy_seek(int, unsigned, int);