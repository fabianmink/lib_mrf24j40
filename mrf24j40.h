/*
  Copyright (c) 2021 Fabian Mink <fabian.mink@gmx.de>
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __MRF24J40_H
#define __MRF24J40_H

#include <stdint.h>
#include <stdbool.h>

#include "mrf24j40_reg.h"


#define MRF24J40_CHANNEL11   0
#define MRF24J40_CHANNEL12   1

#define MRF24J40_FREQ2405MHZ   0


#define IEEE802154_FRAME_TYPE_BEACON 0x00
#define IEEE802154_FRAME_TYPE_DATA   0x01
#define IEEE802154_FRAME_TYPE_ACK    0x02
#define IEEE802154_FRAME_TYPE_MAC    0x03


//Device handle typedef
typedef struct {
	//spi_device *spi;  //todo: Keep for later usage, pointers to read/write register functions
	uint8_t seq_no;
} mrf24j40_devHandle_t;

typedef struct {
	uint8_t hasPA : 1;
} mrf24j40_initData_t;


typedef struct {
	struct 	{
		uint8_t frameType   : 2;
		uint8_t framePend   : 1;
		uint8_t ackReq      : 1;
		uint8_t panIdCmpr   : 1;
		uint8_t destMode    : 2;
		uint8_t srcMode     : 2;
	} flags;

	uint16_t destPanId;
	uint16_t destAddress; // short address (16bit)
	uint16_t srcPanId;
	uint16_t srcAddress;  // short address (16bit)
} macHeader_t;


extern int mrf24j40_hw_init(mrf24j40_devHandle_t* dev, mrf24j40_initData_t* init);
extern int mrf24j40_setRxModeNormal(mrf24j40_devHandle_t* dev);
extern int mrf24j40_setRxModePromiscuous(mrf24j40_devHandle_t* dev);

extern int mrf24j40_prepareTransmit(mrf24j40_devHandle_t* dev, macHeader_t* header, uint8_t *payload, uint8_t lPayload);
extern int mrf24j40_doTransmit(mrf24j40_devHandle_t* dev);

extern int mrf24j40_transmit(mrf24j40_devHandle_t* dev, macHeader_t* header, uint8_t *payload, uint8_t lPayload);

extern int mrf24j40_dumpSaMem(mrf24j40_devHandle_t *dev, mrf24j40_saReg_t *map);

#endif //__MRF24J40_REG_H
