//
// Created by modnick on 17.12.2024.
//
#ifndef FYRFYROS_FLOPPY_DRIVER_H
#define FYRFYROS_FLOPPY_DRIVER_H

#include "macroses.h"

typedef struct DrvGeom {
    byte heads;
    byte tracks;
    byte spt;     /* sectors per track */
} DrvGeom;

// drive geometries
#define DG144_HEADS       2     // heads per drive (1.44M)
#define DG144_TRACKS     80     // number of tracks (1.44M)
#define DG144_SPT        18     // sectors per track (1.44M)
#define DG144_GAP3FMT  0x54     // gap3 while formatting (1.44M)
#define DG144_GAP3RW   0x1b     // gap3 while reading/writing (1.44M)

#define DG168_HEADS       2     // heads per drive (1.68M)
#define DG168_TRACKS     80     // number of tracks (1.68M)
#define DG168_SPT        21     // sectors per track (1.68M)
#define DG168_GAP3FMT  0x0c     // gap3 while formatting (1.68M)
#define DG168_GAP3RW   0x1c     // gap3 while reading/writing (1.68M)

// IO ports
#define FDC_DOR  (0x3f2)   // Digital Output Register
#define FDC_MSR  (0x3f4)   // Main Status Register (input)
#define FDC_DRS  (0x3f4)   // Data Rate Select Register (output)
#define FDC_DATA (0x3f5)   // Data Register
#define FDC_DIR  (0x3f7)   // Digital Input Register (input)
#define FDC_CCR  (0x3f7)   // Configuration Control Register (output)

// command bytes (these are 765 commands + options such as MFM, etc)
#define CMD_SPECIFY (0x03)  // specify drive timings
#define CMD_WRITE   (0xc5)  // write data (+ MT,MFM)
#define CMD_READ    (0xe6)  // read data (+ MT,MFM,SK)
#define CMD_RECAL   (0x07)  // recalibrate
#define CMD_SENSEI  (0x08)  // sense interrupt status
#define CMD_FORMAT  (0x4d)  // format track (+ MFM)
#define CMD_SEEK    (0x0f)  // seek track
#define CMD_VERSION (0x10)  // FDC version

void floppy_init();

void floppy_reset(void);
void floppy_motor_start(byte number);
void floppy_motor_stop(byte number);
void floppy_recalibrate(void);
byte floppy_seek(u32 track);
byte floppy_read_block(u32 block,byte *buffer, u32 count);
byte floppy_write_block(u32 block,byte *buffer, u32 count);
byte floppy_rw_interface(u32 block,byte *buffer, byte read, u32 count);

#endif //FYRFYROS_FLOPPY_DRIVER_H
