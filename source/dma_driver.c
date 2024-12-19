#include "headers/dma_driver.h"
#include "headers/asm_fync.h"

/* Just helps in making things look cleaner.  :) */

/* Defines for accessing the upper and lower byte of an integer. */
#define LOW_BYTE(x)         (x & 0x00FF)
#define HI_BYTE(x)          ((x & 0xFF00) >> 8)

/* Quick-access registers and ports for each DMA channel. */
byte MaskReg[8]   = { 0x0A, 0x0A, 0x0A, 0x0A, 0xD4, 0xD4, 0xD4, 0xD4 };
byte ModeReg[8]   = { 0x0B, 0x0B, 0x0B, 0x0B, 0xD6, 0xD6, 0xD6, 0xD6 };
byte ClearReg[8]  = { 0x0C, 0x0C, 0x0C, 0x0C, 0xD8, 0xD8, 0xD8, 0xD8 };

byte PagePort[8]  = { 0x87, 0x83, 0x81, 0x82, 0x8F, 0x8B, 0x89, 0x8A };
byte AddrPort[8]  = { 0x00, 0x02, 0x04, 0x06, 0xC0, 0xC4, 0xC8, 0xCC };
byte CountPort[8] = { 0x01, 0x03, 0x05, 0x07, 0xC2, 0xC6, 0xCA, 0xCE };

void _dma_xfer(byte DMA_channel, byte page, u32 offset, u32 length, byte mode);

void dma_xfer(byte channel, u32 address, u32 length, byte read)
{
	byte page=0, mode=0;
	u32 offset = 0;
	
	if(read)
		mode = 0x48 + channel;
	else
		mode = 0x44 + channel;
		
	page = address >> 16;
	offset = address & 0xFFFF;
	length--;
	
	_dma_xfer(channel, page, offset, length, mode);	
}	
		

void _dma_xfer(byte DMA_channel, byte page, u32 offset, u32 length, byte mode)
{
    /* Don't let anyone else mess up what we're doing. */
    cli();

    /* Set up the DMA channel so we can use it.  This tells the DMA */
    /* that we're going to be using this channel.  (It's masked) */
    outb(MaskReg[DMA_channel], 0x04 | DMA_channel);

    /* Clear any data transfers that are currently executing. */
    outb(ClearReg[DMA_channel], 0x00);

    /* Send the specified mode to the DMA. */
    outb(ModeReg[DMA_channel], mode);

    /* Send the offset address.  The first byte is the low base offset, the */
    /* second byte is the high offset. */
    outb(AddrPort[DMA_channel], LOW_BYTE(offset));
    outb(AddrPort[DMA_channel], HI_BYTE(offset));

    /* Send the physical page that the data lies on. */
    outb(PagePort[DMA_channel], page);

    /* Send the length of the data.  Again, low byte first. */
    outb(CountPort[DMA_channel], LOW_BYTE(length));
    outb(CountPort[DMA_channel], HI_BYTE(length));

    /* Ok, we're done.  Enable the DMA channel (clear the mask). */
    outb(MaskReg[DMA_channel], DMA_channel);

    /* Re-enable interrupts before we leave. */
    sti();
}