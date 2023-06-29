// ****************************************************************************
// IT7230_SettingTable.c
// Create date  :   20120220
// Modifications:   20120220
// Version      :   IT7230_0004
// Definitions  :
// Copyright (c) 2009 ITE Tech. Inc. All Rights Reserved.
// ****************************************************************************
#include "IT7230_TouchKey.h"

//This initial table depends on each PCB board,Please make this table form ITE.
//PCB model name:XXX-XXX-XXX
const sInitCapSReg code asInitCapSReg[] =
{
	#if MainBoardType == MainBoard_5276_M0A		//121122 Modify
	//715G5883_K0A
	#if((ModelName==AOC_E2471FW)||(ModelName==AOC_M2471F))//20130427 petit update
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x007F},
	{ PAGE_1,  CAPS_CTR, 0x003F},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00B0},     //0x00A0
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0x8007},
	{ PAGE_1,  CAPS_S1CR, 0x8017},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0x8033},
	{ PAGE_1,  CAPS_S4CR, 0x8099},
	{ PAGE_1,  CAPS_S5CR, 0x80BB},
	{ PAGE_1,  CAPS_C0COR, 0x68B7},
	{ PAGE_1,  CAPS_C1COR, 0x68C0},
	{ PAGE_1,  CAPS_C2COR, 0x1380},
	{ PAGE_1,  CAPS_C3COR, 0x71C0},
	{ PAGE_1,  CAPS_C7COR, 0x68C0},
	{ PAGE_1,  CAPS_C9COR, 0x6EC0},
	{ PAGE_1,  CAPS_C11COR, 0x6DC0},
	{ PAGE_1,  CAPS_ICR0, 0xBFFF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR2, 0x0FFF},
	{ PAGE_1,  CAPS_LEDCMR3, 0x0FFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001F},
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3, 0x0333},
	{ PAGE_1,  CAPS_GPIOMSR, 0x6003}, //0x0003
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR, 0x0240}, //0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCF8F},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR, 0x0240}, //0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCF8F},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCF8F},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR, 0x0240}, //0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCF8F},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR, 0x0240}, //0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCF8F},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR, 0x0240}, //0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCF8F},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x0000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_CFER, 0xC000},
	{ PAGE_1,  CAPS_PCR, 0x5406}
	#elif ModelName==AOC_E2771F//petit 20130425 from TP EE.
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x007F},
	{ PAGE_1,  CAPS_CTR, 0x003F},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00B0},     //0x00A0
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0x8007},
	{ PAGE_1,  CAPS_S1CR, 0x8017},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0x8033},
	{ PAGE_1,  CAPS_S4CR, 0x8099},
	{ PAGE_1,  CAPS_S5CR, 0x80BB},
	{ PAGE_1,  CAPS_C0COR, 0x68B7},
	{ PAGE_1,  CAPS_C1COR, 0x68C0},
	{ PAGE_1,  CAPS_C2COR, 0x1380},
	{ PAGE_1,  CAPS_C3COR, 0x71C0},
	{ PAGE_1,  CAPS_C7COR, 0x68C0},
	{ PAGE_1,  CAPS_C9COR, 0x6EC0},
	{ PAGE_1,  CAPS_C11COR, 0x6DC0},
	{ PAGE_1,  CAPS_ICR0, 0xBFFF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR2, 0x0FFF},
	{ PAGE_1,  CAPS_LEDCMR3, 0x0FFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001F},
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3, 0x0333},
	{ PAGE_1,  CAPS_GPIOMSR, 0x6003}, //0x0003
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	//{ PAGE_0,  CAPS_S0OHCR  ,0x0240},//0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S0OHCR, 0x02a0}, // 20130503 Stam Modify-for E2771F
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCF8F},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	//{ PAGE_0,  CAPS_S1OHCR  ,0x0240},//0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S1OHCR, 0x0210}, // 20130424 Stam Modify
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCF8F},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCF8F},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	//{ PAGE_0,  CAPS_S3OHCR  ,0x0240},//0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S3OHCR, 0x02b0}, // 20130424 Stam Modify
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCF8F},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	//{ PAGE_0,  CAPS_S4OHCR  ,0x0240},//0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S4OHCR, 0x02A0}, // 20130424 Stam Modify
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCF8F},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	//{ PAGE_0,  CAPS_S5OHCR  ,0x0240},//0x0400,0x0340,M2471FW,E2471FW
	{ PAGE_0,  CAPS_S5OHCR, 0x0250}, // 20130424 Stam Modify
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCF8F},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x0000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_CFER, 0xC000},
	{ PAGE_1,  CAPS_PCR, 0x5406}
	#else
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x007F},
	{ PAGE_1,  CAPS_CTR, 0x003F},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00B0},     //0x00A0
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0x8007},
	{ PAGE_1,  CAPS_S1CR, 0x8017},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0x8033},
	{ PAGE_1,  CAPS_S4CR, 0x8099},
	{ PAGE_1,  CAPS_S5CR, 0x80BB},
	{ PAGE_1,  CAPS_C0COR, 0x68B7},
	{ PAGE_1,  CAPS_C1COR, 0x68C0},
	{ PAGE_1,  CAPS_C2COR, 0x1380},
	{ PAGE_1,  CAPS_C3COR, 0x71C0},
	{ PAGE_1,  CAPS_C7COR, 0x68C0},
	{ PAGE_1,  CAPS_C9COR, 0x6EC0},
	{ PAGE_1,  CAPS_C11COR, 0x6DC0},
	{ PAGE_1,  CAPS_ICR0, 0xBFFF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF},
	{ PAGE_1,  CAPS_LEDCMR2, 0x0FFF},
	{ PAGE_1,  CAPS_LEDCMR3, 0x0FFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001F},
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3, 0x0333},
	{ PAGE_1,  CAPS_GPIOMSR, 0x6003}, //0x0003
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR, 0x0280}, //0x0400,0x0340
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCF8F},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR, 0x0280}, //0x0400,0x03A0
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCF8F},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCF8F},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR, 0x0280}, //0x0400,0x03A0
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCF8F},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR, 0x0280}, //0x0400,0x03A0
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCF8F},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR, 0x0280}, //0x0400,0x03A0
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCF8F},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x0000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_CFER, 0xC000},
	{ PAGE_1,  CAPS_PCR, 0x5406}
	#endif
	#elif MainBoardType == MainBoard_6194_M0A  //Key PAD 6125//20130522
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x003F},
	{ PAGE_1,  CAPS_CTR, 0x000F},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x0200},
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0x8003},
	{ PAGE_1,  CAPS_S1CR, 0x8093},
	{ PAGE_1,  CAPS_S2CR, 0x80B3},
	{ PAGE_1,  CAPS_S3CR, 0x8073},
	{ PAGE_1,  CAPS_S4CR, 0x8013},
	{ PAGE_1,  CAPS_C0COR, 0x68DB},
	{ PAGE_1,  CAPS_C1COR, 0x68DC},
	{ PAGE_1,  CAPS_C3COR, 0x68C0},
	{ PAGE_1,  CAPS_C7COR, 0x68DD},
	{ PAGE_1,  CAPS_C9COR, 0x68DC},
	{ PAGE_1,  CAPS_C11COR, 0x68D3},
	{ PAGE_1,  CAPS_ICR0, 0xFFBF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0000},
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF },   //130529 Nick Change to FW control LED
	{ PAGE_1,  CAPS_LEDCMR1, 0xDDDD},
	{ PAGE_1,  CAPS_LEDCMR2, 0xDDDD},
	{ PAGE_1,  CAPS_LEDCMR3, 0x0DDD},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001F},
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3333},
	{ PAGE_1,  CAPS_LEDPR2, 0x3333},
	{ PAGE_1,  CAPS_LEDPR3, 0x0333},
	{ PAGE_1,  CAPS_GPIOMSR, 0x6003},
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	//{ PAGE_0,  CAPS_S0OHCR  ,0x01C0},
	{ PAGE_0,  CAPS_S0OHCR, 0x0220}, //petit frome TPEE request 20131017
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCF8F},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	//{ PAGE_0,  CAPS_S1OHCR  ,0x01D0},
	{ PAGE_0,  CAPS_S1OHCR, 0x0250}, //petit frome TPEE request 20131017
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCF8F},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	//{ PAGE_0,  CAPS_S2OHCR  ,0x02F0},
	{ PAGE_0,  CAPS_S2OHCR, 0x0290}, //petit frome TPEE request 20131017
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCF8F},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	//{ PAGE_0,  CAPS_S3OHCR  ,0x01D0},
	{ PAGE_0,  CAPS_S3OHCR, 0x02C0}, //petit frome TPEE request 20131017
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCF8F},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	//{ PAGE_0,  CAPS_S4OHCR  ,0x01F0},
	{ PAGE_0,  CAPS_S4OHCR, 0x02C0}, //petit frome TPEE request 20131017
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCF8F},
	{ PAGE_0,  CAPS_SXCHAIER, 0x001F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x001F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x001F},
	{ PAGE_0,  CAPS_SXCLRIER, 0x001F},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_CFER, 0xC000},
	{ PAGE_1,  CAPS_PCR, 0x4C06}
	#elif MainBoardType == MainBoard_7452_M0A
	{ PAGE_1,  CAPS_PCR 	, 0x0001},
	{ PAGE_1,  CAPS_PSR 	, 0x0001},
	{ PAGE_1,  CAPS_PMR 	, 0x0000},
	{ PAGE_1,  CAPS_RTR 	, 0x005F},
	{ PAGE_1,  CAPS_CTR 	, 0x001F},
	{ PAGE_1,  CAPS_CFER	, 0x4000},
	{ PAGE_1,  CAPS_CRMR	, 0x0020},
	{ PAGE_1,  CAPS_PDR 	, 0x00C0},
	{ PAGE_1,  CAPS_DR 	, 0x0050},
	{ PAGE_1,  CAPS_S0CR	, 0xC003},
	{ PAGE_1,  CAPS_S1CR	, 0xC013},
	{ PAGE_1,  CAPS_S2CR	, 0x8022},
	{ PAGE_1,  CAPS_S3CR	, 0xC073},
	{ PAGE_1,  CAPS_S4CR	, 0xC093},
	{ PAGE_1,  CAPS_S5CR	, 0xC0B3},
	{ PAGE_1,  CAPS_C0COR	, 0x68D8},
	{ PAGE_1,  CAPS_C1COR	, 0x68CE},
	{ PAGE_1,  CAPS_C2COR	, 0x63DB},
	{ PAGE_1,  CAPS_C3COR	, 0x68C0},
	{ PAGE_1,  CAPS_C7COR	, 0x68D2},
	{ PAGE_1,  CAPS_C9COR	, 0x68CF},
	{ PAGE_1,  CAPS_C11COR	, 0x68DC},
	{ PAGE_1,  CAPS_ICR0	, 0xFFBF},
	{ PAGE_1,  CAPS_ICR1	, 0x0FFF},
	{ PAGE_1,  CAPS_COER0	, 0xFFFF},
	{ PAGE_1,  CAPS_COER1	, 0x03FF},
	{ PAGE_1,  CAPS_CGCR	, 0x0001},
	{ PAGE_1,  CAPS_LEDBR	, 0x0000},
	{ PAGE_1,  CAPS_GPIODR	, 0x0003},	// set GPIO 0 & 1 output
	{ PAGE_1,  CAPS_GPIOOR	, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR	, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR	, 0x0003},
	{ PAGE_1,  CAPS_GPIOER	, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF}, //0x50DD
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF}, //0x3DD4
	{ PAGE_1,  CAPS_LEDCMR2, 0xFFFF}, //0x1D2D
	{ PAGE_1,  CAPS_LEDCMR3, 0xFFFF},
	{ PAGE_1,  CAPS_LEDRPR	, 0x3030},
	{ PAGE_1,  CAPS_LEDBR	, 0x001A},	 //120607 Modify for ITE Request LED current 5mA
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0	, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1	, 0x3443},
	{ PAGE_1,  CAPS_LEDPR2	, 0x3434},
	{ PAGE_1,  CAPS_LEDPR3	, 0x0444},
	{ PAGE_1,  CAPS_GPIOMSR, 0x0003},	// set GPIO 0 & 1
	{ PAGE_0,  CAPS_S0DLR	, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR	, 0x02A0}, //20150505  kenny
	{ PAGE_0,  CAPS_S0OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S0SR	, 0xCC88},
	{ PAGE_0,  CAPS_S1DLR	, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR	, 0x0300}, //20150505  kenny
	{ PAGE_0,  CAPS_S1OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S1SR	, 0xCC88},
	{ PAGE_0,  CAPS_S2DLR	, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR	, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S2SR	, 0xCC88},
	{ PAGE_0,  CAPS_S3DLR	, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR	, 0x02A0}, //20150505  kenny
	{ PAGE_0,  CAPS_S3OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S3SR	, 0xCC88},
	{ PAGE_0,  CAPS_S4DLR	, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR	, 0x02A0}, //20150505  kenny
	{ PAGE_0,  CAPS_S4OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S4SR	, 0xCC88},
	{ PAGE_0,  CAPS_S5DLR	, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR	, 0x0250}, //20150505  kenny
	{ PAGE_0,  CAPS_S5OLCR	, 0x7000},
	{ PAGE_0,  CAPS_S5SR	, 0xCC88},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x00000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR	, 0x1FFF},
	{ PAGE_1,  CAPS_PCR 	, 0x5406}//0x5C06

	#else
	{ PAGE_1,  CAPS_PCR, 0x0001},
	{ PAGE_1,  CAPS_PSR, 0x0001},
	{ PAGE_1,  CAPS_PMR, 0x0000},
	{ PAGE_1,  CAPS_RTR, 0x005F},
	{ PAGE_1,  CAPS_CTR, 0x001F},
	{ PAGE_1,  CAPS_CFER, 0x4000},
	{ PAGE_1,  CAPS_CRMR, 0x0020},
	{ PAGE_1,  CAPS_PDR, 0x00C0},
	{ PAGE_1,  CAPS_DR, 0x0050},
	{ PAGE_1,  CAPS_S0CR, 0xC003},
	{ PAGE_1,  CAPS_S1CR, 0xC013},
	{ PAGE_1,  CAPS_S2CR, 0x8022},
	{ PAGE_1,  CAPS_S3CR, 0xC073},
	{ PAGE_1,  CAPS_S4CR, 0xC093},
	{ PAGE_1,  CAPS_S5CR, 0xC0B3},
	{ PAGE_1,  CAPS_C0COR, 0x68D8},
	{ PAGE_1,  CAPS_C1COR, 0x68CE},
	{ PAGE_1,  CAPS_C2COR, 0x63DB},
	{ PAGE_1,  CAPS_C3COR, 0x68C0},
	{ PAGE_1,  CAPS_C7COR, 0x68D2},
	{ PAGE_1,  CAPS_C9COR, 0x68CF},
	{ PAGE_1,  CAPS_C11COR, 0x68DC},
	{ PAGE_1,  CAPS_ICR0, 0xFFBF},
	{ PAGE_1,  CAPS_ICR1, 0x0FFF},
	{ PAGE_1,  CAPS_COER0, 0xFFFF},
	{ PAGE_1,  CAPS_COER1, 0x03FF},
	{ PAGE_1,  CAPS_CGCR, 0x0001},
	{ PAGE_1,  CAPS_LEDBR, 0x0000},
	{ PAGE_1,  CAPS_GPIODR, 0x0003},    // set GPIO 0 & 1 output
	{ PAGE_1,  CAPS_GPIOOR, 0x0000},
	{ PAGE_1,  CAPS_GPIOMR, 0x0000},
	{ PAGE_1,  CAPS_GPIOLR, 0x0003},
	{ PAGE_1,  CAPS_GPIOER, 0x0000},
	{ PAGE_1,  CAPS_LEDCMR0, 0xFFFF}, //0x50DD
	{ PAGE_1,  CAPS_LEDCMR1, 0xFFFF}, //0x3DD4
	{ PAGE_1,  CAPS_LEDCMR2, 0xFFFF}, //0x1D2D
	{ PAGE_1,  CAPS_LEDCMR3, 0xFFFF},
	{ PAGE_1,  CAPS_LEDRPR, 0x3030},
	{ PAGE_1,  CAPS_LEDBR, 0x001A},	//120607 Modify for ITE Request LED current 5mA
	{ PAGE_1,  CAPS_LEDCGCR, 0x0000},
	{ PAGE_1,  CAPS_LEDPR0, 0x3333},
	{ PAGE_1,  CAPS_LEDPR1, 0x3443},
	{ PAGE_1,  CAPS_LEDPR2, 0x3434},
	{ PAGE_1,  CAPS_LEDPR3, 0x0444},
	{ PAGE_1,  CAPS_GPIOMSR, 0x0003},   // set GPIO 0 & 1
	{ PAGE_0,  CAPS_S0DLR, 0x8000},
	{ PAGE_0,  CAPS_S0OHCR, 0x0280},  //0x0280
	{ PAGE_0,  CAPS_S0OLCR, 0x7000},
	{ PAGE_0,  CAPS_S0SR, 0xCC88},
	{ PAGE_0,  CAPS_S1DLR, 0x8000},
	{ PAGE_0,  CAPS_S1OHCR, 0x0400},  //0x0400
	{ PAGE_0,  CAPS_S1OLCR, 0x7000},
	{ PAGE_0,  CAPS_S1SR, 0xCC88},
	{ PAGE_0,  CAPS_S2DLR, 0x8000},
	{ PAGE_0,  CAPS_S2OHCR, 0x7000},
	{ PAGE_0,  CAPS_S2OLCR, 0x7000},
	{ PAGE_0,  CAPS_S2SR, 0xCC88},
	{ PAGE_0,  CAPS_S3DLR, 0x8000},
	{ PAGE_0,  CAPS_S3OHCR, 0x0240}, //0x0240
	{ PAGE_0,  CAPS_S3OLCR, 0x7000},
	{ PAGE_0,  CAPS_S3SR, 0xCC88},
	{ PAGE_0,  CAPS_S4DLR, 0x8000},
	{ PAGE_0,  CAPS_S4OHCR, 0x0400}, //0x0400
	{ PAGE_0,  CAPS_S4OLCR, 0x7000},
	{ PAGE_0,  CAPS_S4SR, 0xCC88},
	{ PAGE_0,  CAPS_S5DLR, 0x8000},
	{ PAGE_0,  CAPS_S5OHCR, 0x0280}, //0x0280
	{ PAGE_0,  CAPS_S5OLCR, 0x7000},
	{ PAGE_0,  CAPS_S5SR, 0xCC88},
	{ PAGE_0,  CAPS_SXCHAIER, 0x003F},
	{ PAGE_0,  CAPS_SXCHRIER, 0x003F},
	{ PAGE_0,  CAPS_SXCLAIER, 0x00000},
	{ PAGE_0,  CAPS_SXCLRIER, 0x0000},
	{ PAGE_1,  CAPS_GPIONPCR, 0x1FFF},
	{ PAGE_1,  CAPS_PCR, 0x5406}     //0x5C06
	#endif
};


//