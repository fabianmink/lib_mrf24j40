#ifndef __MRF24J40_REG_H
#define __MRF24J40_REG_H

// Short Address Registers
#define REG_RXMCR 0x00  // Receive MAC control
#define BIT_PROMI 0
#define BIT_ERRPKT 1
#define BIT_NOACKRSP 5
#define BIT_PANCOORD 3

#define REG_PANIDL  0x01  //PAN ID Low Byte
#define REG_PANIDH  0x02  //PAN ID High Byte
#define REG_SADRL   0x03  //Short Address Low Byte
#define REG_SADRH   0x04  //Short Address High Byte
#define REG_EADR0   0x05  //64-Bit Extended Address bits
#define REG_EADR1   0x06
#define REG_EADR2   0x07
#define REG_EADR3   0x08
#define REG_EADR4   0x09
#define REG_EADR5   0x0A
#define REG_EADR6   0x0B
#define REG_EADR7   0x0C
#define REG_RXFLUSH 0x0D  //Receive FIFO Flush
#define REG_ORDER   0x10  //Beacon and Superframe Order
#define REG_TXMCR   0x11  //CSMA-CA Mode Control


#define REG_ACKTMOUT 0x12
#define REG_ESLOTG1  0x13
#define REG_SYMTICKL 0x14
#define REG_SYMTICKH 0x15
#define REG_PACON0   0x16  //Power Amplifier Control 0
#define REG_PACON1   0x17  //Power Amplifier Control 1
#define REG_PACON2   0x18  //Power Amplifier Control 2
#define REG_TXBCON0  0x1A  //Transmit Beacon FIFO Control 0
#define REG_TXNCON   0x1B  //Transmit Normal FIFO Control
#define BIT_TXNTRIG     0
#define BIT_TXNSECEN    1
#define BIT_TXNACKREQ   2

#define REG_TXG1CON  0x1C  //GTS1 FIFO Control
#define REG_TXG2CON  0x1D  //GTS2 FIFO Control
#define REG_ESLOTG23 0x1E  //End slot of GTS3 and GTS2
#define REG_ESLOTG45 0x1F
#define REG_ESLOTG67 0x20
#define REG_TXPEND   0x21  //TX Data Pending
#define REG_WAKECON  0x22  //Wake Control
#define REG_FRMOFFSET 0x23 //Superframe Counter Offset to Align Beacon
#define REG_TXSTAT   0x24  //TX MAC Status
#define REG_TXBCON1  0x25  //Transmit Beacon Control 1
#define REG_GATECLK  0x26  //Gated Clock Control
#define REG_TXTIME   0x27
#define REG_HSYMTMRL 0x28
#define REG_HSYMTMRH 0x29
#define REG_SOFTRST  0x2A  //Software Reset
#define REG_SECCON0  0x2C
#define REG_SECCON1  0x2D
#define REG_TXSTBL   0x2E
#define REG_RXSR     0x30
#define REG_INTSTAT  0x31 //Interrupt Status
#define BIT_TXNIF	    0 //TX Normal FIFO Transmission Interrupt occurred
#define BIT_RXIF	    3 //RX FIFO Reception Interrupt occurred

#define REG_INTCON   0x32 //Interrupt Control
#define BIT_TXNIE       0 //TX Normal FIFO Transmission Interrupt Enable
#define BIT_RXIE        3 //RX FIFO Reception Interrupt Enable


#define REG_GPIO     0x33  //GPIO PORT
#define REG_TRISGPIO 0x34  //GPIO PIN DIRECTION
#define REG_SLPACK   0x35  //Sleep Ack and Wake-Up counter
#define REG_RFCTL    0x36  //RF Mode Control
#define BIT_RFRST       2  //RF State Machine Reset

#define REG_SECCR2   0x37
#define REG_BBREG0   0x38 //Baseband 0
#define REG_BBREG1   0x39 //Baseband 1
#define BIT_RXDECINV    2 //RX Decode Inversion

#define REG_BBREG2   0x3A //Baseband 2
#define REG_BBREG3   0x3B
#define REG_BBREG4   0x3C
#define REG_BBREG6   0x3E
#define REG_CCAEDTH  0x3F //Energy Detection Threshold

//Long Address Registers
#define REG_TXFIFO   0x000 //Transmit FIFO

#define REG_RFCON0   0x200 //RF Control
#define REG_RFCON1   0x201
#define REG_RFCON2   0x202
#define REG_RFCON3   0x203
#define REG_RFCON5   0x205
#define REG_RFCON6   0x206
#define REG_RFCON7   0x207
#define REG_RFCON8   0x208
#define REG_SLPCAL0  0x209 //Sleep Calibration
#define REG_SLPCAL1  0x20A
#define REG_SLPCAL2  0x20B
#define REG_RFSTATE  0x20F //RF State
#define REG_RSSI     0x210 //Averaged RSSI Value
#define REG_SLPCON0  0x211  //Sleep Clock Control
#define REG_SLPCON1  0x220
#define REG_WAKETIMEL 0x222  //Wake-up Time Match Value Low
#define REG_WAKETIMEH 0x223  //Wake-up Time Match Value High
#define REG_REMCNTL   0x224
#define REG_REMCNTH   0x225
#define REG_MAINCNT0  0x226
#define REG_MAINCNT1  0x227
#define REG_MAINCNT2  0x228
#define REG_MAINCNT3  0x229
#define REG_TESTMODE  0x22F
#define REG_ASSOEAR0  0x230
#define REG_ASSOEAR1  0x231
#define REG_ASSOEAR2  0x232
#define REG_ASSOEAR3  0x233
#define REG_ASSOEAR4  0x234
#define REG_ASSOEAR5  0x235
#define REG_ASSOEAR6  0x236
#define REG_ASSOEAR7  0x237
#define REG_ASSOSAR0  0x238
#define REG_ASSOSAR1  0x239
#define REG_UNONCE0   0x240
#define REG_UNONCE1   0x241
#define REG_UNONCE2   0x242
#define REG_UNONCE3   0x243
#define REG_UNONCE4   0x244
#define REG_UNONCE5   0x245
#define REG_UNONCE6   0x246
#define REG_UNONCE7   0x247
#define REG_UNONCE8   0x248
#define REG_UNONCE9   0x249
#define REG_UNONCE10  0x24A
#define REG_UNONCE11  0x24B
#define REG_UNONCE12  0x24C
#define REG_RXFIFO    0x300 //Receive FIFO

typedef union{
	uint8_t regblock[64];
	struct {
		uint8_t	regRXMCR;
		uint8_t regPANIDL;
		uint8_t regPANIDH;
		uint8_t regSADRL;
		uint8_t regSADRH;
		uint8_t regEADR0;
		uint8_t regEADR1;
		uint8_t regEADR2;
		uint8_t regEADR3;
		uint8_t regEADR4;
		uint8_t regEADR5;
		uint8_t regEADR6;
		uint8_t regEADR7;
		uint8_t regRXFLUSH;
		uint8_t regRes0;
		uint8_t regRes1;

		uint8_t regORDER;
		uint8_t regTXMCR;
		uint8_t regACKTMOUT;
		uint8_t regESLOTG1;
		uint8_t regSYMTICKL;
		uint8_t regSYMTICKH;
		uint8_t regPACON0;
		uint8_t regPACON1;
		uint8_t regPACON2;
		uint8_t regRes2;
		uint8_t regTXBCON0;
		uint8_t regTXNCON;
		uint8_t regTXG1CON;
		uint8_t regTXG2CON;
		uint8_t regESLOTG23;
		uint8_t regESLOTG45;

		uint8_t regESLOTG67;
		uint8_t regTXPEND;
		uint8_t regWAKECON;
		uint8_t regFRMOFFSET;
		uint8_t regTXSTAT;
		uint8_t regTXBCON1;
		uint8_t regGATECLK;
		uint8_t regTXTIME;
		uint8_t regHSYMTMRL;
		uint8_t regHSYMTMRH;
		uint8_t regSOFTRST;
		uint8_t regRes3;
		uint8_t regSECCON0;
		uint8_t regSECCON1;
		uint8_t regTXSTBL;
		uint8_t regRes4;

		uint8_t regRXSR;
		uint8_t regINTSTAT;
		uint8_t regINTCON;
		uint8_t regGPIO;
		uint8_t regTRISGPIO;
		uint8_t regSLPACK;
		uint8_t regRFCTL;
		uint8_t regSECCR2;
		uint8_t regBBREG0;
		uint8_t regBBREG1;
		uint8_t regBBREG2;
		uint8_t regBBREG3;
		uint8_t regBBREG4;
		uint8_t regRes5;
		uint8_t regBBREG6;
		uint8_t regCCAEDTH;
	} regname;
} mrf24j40_saReg_t;

#endif //__MRF24J40_REG_H
