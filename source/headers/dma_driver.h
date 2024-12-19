//
// Created by modnick on 18.12.2024.
//
#ifndef FYRFYROS_DMA_DRIVER_H
#define FYRFYROS_DMA_DRIVER_H

#include "macroses.h"

void dma_xfer(byte channel, u32 address, u32 length, byte read);

#endif //FYRFYROS_DMA_DRIVER_H
