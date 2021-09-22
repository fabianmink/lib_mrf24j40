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

#include <stddef.h>
#include <stdint.h>
#include "mrf24j40_reg.h"
#include "mrf24j40.h"
#include "main.h"  //contains MRF24J40_*Address* functions

int mrf24j40_hw_init(mrf24j40_devHandle_t* dev, mrf24j40_initData_t* init)
{
	//Steps are according to Datasheet 3.2 Initialization, Page 90

	int ret = 0;

	//Step 1.
	MRF24J40_shortAddressWrite(REG_SOFTRST, 0x07);
	delay_ms(10);

	MRF24J40_shortAddressWrite(REG_SOFTRST, 0x07);
	delay_ms(10);

	MRF24J40_shortAddressWrite(REG_SOFTRST, 0x07);
	delay_ms(10);

	MRF24J40_shortAddressWrite(REG_SOFTRST, 0x07);
	uint8_t rval;
	do {
		rval = MRF24J40_shortAddressRead(REG_SOFTRST);
	} while ((rval & 0x07) != (uint8_t) 0x00);

	delay_ms(10);


	//Step 2.
	MRF24J40_shortAddressWrite(REG_PACON2, 0x98);

	//Step 3.
	MRF24J40_shortAddressWrite(REG_TXSTBL, 0x95);

	//Step 4.
	MRF24J40_longAddressWrite(REG_RFCON0, 0x03);

	//Step 5.
	MRF24J40_longAddressWrite(REG_RFCON1, 0x01);

	//Step 6.
	MRF24J40_longAddressWrite(REG_RFCON2, 0x80);

	//Step 7.
	MRF24J40_longAddressWrite(REG_RFCON6, 0x90);

	//Step 8.
	MRF24J40_longAddressWrite(REG_RFCON7, 0x80);

	//Step 9.
	MRF24J40_longAddressWrite(REG_RFCON8, 0x10);

	//Step 10.
	MRF24J40_longAddressWrite(REG_SLPCON1, 0x21);

	//Config for nonbeacon-enabled devices (nothing to do!)
	//1. Set the PANCOORD (RXMCR 0x00<3>) bit = 1 to configure as the PAN coordinator.
	//MRF24J40_shortAddressWrite(REG_RXMCR, 0x08);
	//2. Clear the SLOTTED (TXMCR 0x11<5>) bit = 0 to configure Unslotted CSMA-CA mode.
	//3. Configure BO (ORDER 0x10<7:4>) value = 0xF.
	//ALREADY DEFAULT!!
	//4. Configure SO (ORDER 0x10<3:0>) value = 0xF.
	//ALREADY DEFAULT!!

	//MRF24J40_shortAddressWrite(REG_TXMCR, 0x1C);    //TXMCR Default ()
	MRF24J40_shortAddressWrite(REG_TXMCR, 0x84);    //NOCSMA = 1, MACMINBE = 0 -> CA disabled, CSMABF default



	//Step 11.
	MRF24J40_shortAddressWrite(REG_BBREG2, 0x80);    //CCAMODE = 10  (Energy above Threshold)
	//MRF24J40_shortAddressWrite(REG_BBREG2, 0xF8);  //CCAMODE = 11  (Carrier Sense with Energy above Threshold, CCASTH = 1110 = recommended)

	//Step 12.
	//MRF24J40_shortAddressWrite(REG_CCAEDTH, 0x60); //Clear Channel Assessment (CCA) Energy Detection (ED) Mode bits, recommended (-69dBm)
	MRF24J40_shortAddressWrite(REG_CCAEDTH, 0xFF); //Clear Channel Assessment (CCA) Energy Detection (ED) Mode bits, > -40dBm

	//Step 13.
	MRF24J40_shortAddressWrite(REG_BBREG6, 0x40);

	//Step 14.
	//todo: Interrupt
	//MRF24J40_shortAddressWrite(REG_INTCON, 0xFF); //Disable all interrupt
	MRF24J40_shortAddressWrite(REG_INTCON, 0xF7); //Disable all interrupts, but RX
	//MRF24J40_shortAddressWrite(REG_INTCON, 0xFE); //Disable all interrupts, but TX

	//Step 15.
	//set channel
	//uint8_t channel = 11;  //2405 MHz
	//MRF24J40_longAddressWrite(REG_RFCON0, ((channel - 11) << 4) | 0x03);  //!maintain <3:0> = 0x03!
	//MRF24J40_shortAddressWrite(REG_RFCTL, 0x04); //Reset RF
	//MRF24J40_shortAddressWrite(REG_RFCTL, 0x00);
	//delay_ms(1);

	//Step 16.
	if(init->hasPA){
		//for MRF24J40ME.   (Module with PA / LNA)
		MRF24J40_longAddressWrite(REG_RFCON3, 0x85); //0.1dbm TX Power
		//MRF24J40_longAddressWrite(REG_RFCON3, 0x00); //NOT SPECIFIED ??Power too high??
		MRF24J40_longAddressWrite(REG_TESTMODE, 0x7); //PA / LNA control
	}
	else {
		MRF24J40_longAddressWrite(REG_RFCON3, 0x00); //0dbm  TX Power
		//MRF24J40_longAddressWrite(REG_RFCON3, 0x80); //-20dbm TX Power
	}

	//Step 17.
	MRF24J40_shortAddressWrite(REG_RFCTL, 0x04); //Reset RF
	//Step 18.
	MRF24J40_shortAddressWrite(REG_RFCTL, 0x00);

	//Step 19.
	delay_ms(1);

	//Dummy data, not used
	MRF24J40_shortAddressWrite(REG_SADRL, 0x56);
	MRF24J40_shortAddressWrite(REG_SADRH, 0x78);
	MRF24J40_shortAddressWrite(REG_PANIDL, 0x55);
	MRF24J40_shortAddressWrite(REG_PANIDH, 0x22);

	return ret;
}


int mrf24j40_setRxModeNormal(mrf24j40_devHandle_t* dev){
	//todo
	//MRF24J40_shortAddressWrite(REG_RXMCR, 0x00);
	return 0;
}

int mrf24j40_setRxModePromiscuous(mrf24j40_devHandle_t* dev){
	//todo: Read rest of register and only modify bits
	MRF24J40_shortAddressWrite(REG_RXMCR, 0x01);
	return 0;
}


int mrf24j40_prepareTransmit(mrf24j40_devHandle_t* dev, macHeader_t* header, uint8_t *payload, uint8_t lPayload){

	uint8_t headerLength;
	uint8_t pTxFifo = REG_TXFIFO;
	uint8_t frameControl;

	if(header->flags.panIdCmpr){
		frameControl = 0x41; //Frame type "Data", No security, No frame pending, No Ack. Reqest, PAN ID Compression (only destination PAN ID)
		headerLength = 9;
	}
	else {
		frameControl = 0x01; //Frame type "Data", No security, No frame pending, No Ack. Reqest, No PAN ID Compression
		headerLength = 11;
	}


	// set header length
	MRF24J40_longAddressWrite(pTxFifo++, headerLength);
	// set packet length
	MRF24J40_longAddressWrite(pTxFifo++, headerLength + lPayload);

	// Frame Control Field (FCF) byte 1
	MRF24J40_longAddressWrite(pTxFifo++, frameControl);
	// Frame Control Field (FCF) byte 2
	MRF24J40_longAddressWrite(pTxFifo++, 0x88); //Address field contains short Address for Dest. + Source, IEEE 802.15.4-2003 compatible Frame.

	// Squence Number (SN)
	MRF24J40_longAddressWrite(pTxFifo++, (dev->seq_no)++);

	//Dest. PAN ID (here: Broadcast)
	//MRF24J40_longAddressWrite(pTxFifo++, 0xFF);
	//MRF24J40_longAddressWrite(pTxFifo++, 0xFF);

	//Dest. PAN ID
	MRF24J40_longAddressWrite(pTxFifo++, (header->destPanId & 0x00FF));
	MRF24J40_longAddressWrite(pTxFifo++, ((header->destPanId>>8) & 0x00FF));

	//Dest. Addr.
	MRF24J40_longAddressWrite(pTxFifo++, (header->destAddress & 0x00FF));
	MRF24J40_longAddressWrite(pTxFifo++, ((header->destAddress>>8) & 0x00FF));

	//Source PAN ID
	if(!(header->flags.panIdCmpr)){
		MRF24J40_longAddressWrite(pTxFifo++, (header->srcPanId & 0x00FF));
		MRF24J40_longAddressWrite(pTxFifo++, ((header->srcPanId>>8) & 0x00FF));
	}

	//Source Addr.
	MRF24J40_longAddressWrite(pTxFifo++, (header->srcAddress & 0x00FF));
	MRF24J40_longAddressWrite(pTxFifo++, ((header->srcAddress>>8) & 0x00FF));

	//following is Data Payload
	for (int i = 0; i < lPayload; i++){
		MRF24J40_longAddressWrite(pTxFifo++, payload[i]);
	}

	//2 bytes FCS will be automatically generated by MRF24J40

	return true;
}


int mrf24j40_doTransmit(mrf24j40_devHandle_t* dev){
	// now trigger the transmission (!!MIGHT DEPEND ON TYPE of packet, ack request etc.)
	MRF24J40_shortAddressWrite(REG_TXNCON, 0x01);
	return 0;
}


int mrf24j40_transmit(mrf24j40_devHandle_t* dev, macHeader_t* header, uint8_t *payload, uint8_t lPayload){
	int ret = mrf24j40_prepareTransmit(dev, header, payload, lPayload);
	if(ret) return(ret);

	ret = mrf24j40_doTransmit(dev);
	return ret;
}

int mrf24j40_dumpSaMem(mrf24j40_devHandle_t *dev, mrf24j40_saReg_t *map){
	int i;
	for(i=0;i<64;i++){
		map->regblock[i] = MRF24J40_shortAddressRead(i);
	}
	return(0);
}

