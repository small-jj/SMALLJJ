#ifndef _BD_ENE_715G6018_H_
#define _BD_ENE_715G6018_H_

#if ENE_IC_TYPE == SB358X

#define KEYNUMBER  5
#define CTM_BUTTON_MAPPING_TABLE  6, 5, 4, 1, 10
// Delta Reg. table, range= 0x054~0x07D   
#if 1//KEY_PAD == KEY_PAD_715G6018_K0A     //AOC G2 SMNT

// Delta Reg. table, range= 0x054~0x07D   
#if MainBoardType == MainBoard_6038_M0A||ModelName==AOC_A2272PWR//130628 modify for ENE FAE Request
//follow G2  petit 20141226
#if ModelName==AOC_A2272PWR
BYTE code sb358x_delta_reg_table[42] = //130627 modify for ENE FAE Request
{
//	 054,  055,  056,  057
	0x13, 0x01, 0xA0, 0x00, 
//	 058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
	0x13, 0x01, 0x13, 0x01, 0xA0, 0x00, 0xA0, 0x00,
//	 060,  061,  062,  063,  064,  065,  066,  067,
	0xA0, 0x00, 0x64, 0x00, 0x13, 0x01, 0x13, 0x01, 
//	 068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
	0xA0, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//	 070,  071,  072,  073,  074,  075,  076,  077,
	0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//	 078,  079,  07A,  07B,  07C,  07D
	0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] =  //130813 henry modify for ENE FAE Request
{
//	 080,  081,  082,  083,  084,  085,  086,  087,
	0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0xA0,
//	 088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
	0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//	 090,  091,  092,  093,  094,  095,  096,  097,
	0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//	 098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
	0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00

};
#else
BYTE code sb358x_delta_reg_table[42] = //130627 modify for ENE FAE Request
{
//   054,  055,  056,  057
    0x13, 0x01, 0xC8, 0x00, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xC8, 0x00, 0xC8, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0xC8, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xC8, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] =  //130813 henry modify for ENE FAE Request
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x80,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#endif
#elif MainBoardType == MainBoard_6223_M0A	//130808 henry for ENE FAE Request
#if (ModelName==AOC_A2272PW4T||ModelName==AOC_A2272PW4T_CMI)
BYTE code sb358x_delta_reg_table[42] =               // 20130529 Annie add,  follow PHL modify ESD issue//130711 follow ENE FAE request
{
//   054,  055,  056,  057
    0x13, 0x01, 0xC8, 0x00, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xC8, 0x00, 0xC8, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0xC8, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xC8, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};
// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] = //130711 follow ENE FAE request
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x80,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#elif (ModelName == AOC_A2472PW4T||ModelName == AOC_A2472PW4T_TPM||ModelName==AOC_A2472PW4TN)//130808 henry  for ENE FAE Request
BYTE code sb358x_delta_reg_table[42] =
{
//   054,  055,  056,  057
    0x13, 0x01, 0xBE, 0x00, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xC8, 0x00, 0xC8, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0xBE, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xBE, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] =  
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0xA0,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#else
BYTE code sb358x_delta_reg_table[42] =               // 20130529 Annie add,  follow PHL modify ESD issue//130711 follow ENE FAE request
{
//   054,  055,  056,  057
    0x13, 0x01, 0xBE, 0x00, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xBE, 0x00, 0x96, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0x96, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xDC, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F

BYTE code sb358x_scan_reg_table[32] = //130711 follow ENE FAE request
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x80,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,             //Follow TouchKey Armingle lee
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#endif
#elif (MainBoardType == MainBoard_8191_M0A)
// Delta Reg. table, range= 0x054~0x07D
BYTE code sb358x_delta_reg_table[42] =
{
//   054,  055,  056,  057
    0x13, 0x01, 0x18, 0x01,
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0x18, 0x01, 0xFA, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0xFA, 0x00, 0x64, 0x00, 0x13, 0x01, 0x13, 0x01,
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0x18, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};
// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] =
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x80,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#elif ((MainBoardType == MainBoard_7219_M0C)&&(ModelName==AOC_A2472PWRP))|| (MainBoardType == MainBoard_7414_M0A) //follow G2  petit 20141226
//AOC_A2472PWRP and  AOC_A2272PWRP  are difference,please note
BYTE code sb358x_delta_reg_table[42] =               //20141106 follow Ene Fae Armingle Request
{
//   054,  055,  056,  057
    0x13, 0x01, 0xC2, 0x01, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xC2, 0x01, 0xC2, 0x01,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0x90, 0x01, 0x64, 0x00, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xC2, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};
// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] =	 	//20141106 follow Ene Fae Armingle Request
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x70,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};

#else
BYTE code sb358x_delta_reg_table[42] =               // 20130529 Annie add,  follow PHL modify ESD issue//130711 follow ENE FAE request
{
//   054,  055,  056,  057
    0x13, 0x01, 0xBE, 0x00, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0xBE, 0x00, 0x96, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0x96, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xDC, 0x00, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F

BYTE code sb358x_scan_reg_table[32] = //130711 follow ENE FAE request
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0x80,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x1A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,             //Follow TouchKey Armingle lee
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xF2, 0x04, 0x00, 0xF2, 0x04, 0x00
};
#endif

BYTE code sb358x_gpio_pwm_output_reg_table[6] = 
{
    0x00,             //setup MP0~MP7  GPIO data output.
    0x00,             //setup MP8~MP12 GPIO data output.    
    0x00,             //disable MP0~MP7  GPIO input.
    0x00,             //disable MP8~MP12 GPIO input.
    0x00,             //disable MP0~MP7  GPIO output.
    0x00              //disable MP8~MP12 GPIO output.
};


#elif KEY_PAD == KEY_PAD_715G5691_K0F       //BenQ BL2411PT

// Delta Reg. table, range= 0x054~0x07D   
BYTE code sb358x_delta_reg_table[42] = 
{
//   054,  055,  056,  057
    0x13, 0x01, 0x13, 0x01, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x22, 0x01,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0x13, 0x01, 0x13, 0x01, 0xDC, 0x00, 0xDC, 0x00, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0x80, 0x00, 0x22, 0x01, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] = 
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0xE0,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x0A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xE0, 0x0F, 0x00, 0xE0, 0x0F, 0x00
};

#elif KEY_PAD == KEY_PAD_715G5343_K0A       //ASUS MX299Q

// Delta Reg. table, range= 0x054~0x07D   
BYTE code sb358x_delta_reg_table[42] = 
{
//   054,  055,  056,  057
    0x13, 0x01, 0x13, 0x01, 
//   058,  059,  05A,  05B,  05C,  05D,  05E,  05F,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0xB0, 0x00,
//   060,  061,  062,  063,  064,  065,  066,  067,
    0xB0, 0x00, 0xB0, 0x00, 0xB0, 0x00, 0xB0, 0x00, 
//   068,  069,  06A,  06B,  06C,  06D,  06E,  06F,
    0xB0, 0x00, 0xB0, 0x00, 0x13, 0x01, 0x13, 0x01,
//   070,  071,  072,  073,  074,  075,  076,  077,
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01, 0x13, 0x01,
//   078,  079,  07A,  07B,  07C,  07D
    0x13, 0x01, 0x13, 0x01, 0x13, 0x01
};

// Scan Reg. table, range= 0x080~0x09F
BYTE code sb358x_scan_reg_table[32] = 
{
//   080,  081,  082,  083,  084,  085,  086,  087,
    0x00, 0x81, 0x0F, 0x01, 0x01, 0x00, 0x31, 0xA0,
//   088,  089,  08A,  08B,  08C,  08D,  08E,  08F,
    0xFF, 0x0A, 0x00, 0x7C, 0x04, 0x78, 0x08, 0x78,
//   090,  091,  092,  093,  094,  095,  096,  097,
    0x08, 0x20, 0x05, 0x15, 0x00, 0x00, 0x00, 0x00,
//   098,  099,  09A,  09B,  09C,  09D,  09E,  09F,
    0x07, 0x02, 0xE0, 0x0F, 0x00, 0xE0, 0x0F, 0x00
};

#endif

// Pending Flag Reg. table, range= 0x0A4~0x0A6
BYTE code sb358x_Pending_Flag_reg_table[3] = 
{
    0xFF, 0xFF, 0xFF
};


// Low Power Reg. table, range= 0x0A7~0x0A8
BYTE code sb358x_low_power_reg_table[2] = 
{
//   0A7,  0A8
    0x51, 0x10
};

// GPIO mode select Reg. table, range= 0x100~0101
BYTE code sb358x_gpio_mode_select_reg_table[2] = 
{
    0x00,             //setup MP7~ MP0 as GPIO
    0x00              //setup MP8~B1 as GPIO
};

// GPIO PWM Reg. table, range= 0x104~0x109

// PWM Mode config Reg. table, range= 0x10A~0x10F
BYTE code sb358x_PWM_Mode_config_table[6] =
{
    0xFF,             //set MP2~MP7 as auto PWM.
    0x3F,             //set MP8 as auto PWM. 
    0x01,             //set MP2~MP7 as open-drain mode. //Modify By ENN FAE Request 20150922
    0x10,             //set MP8 as open-drain mode.    
    0xBA,             //set PWM base clock= (1/6MHz)*0xBA= 32KHz.    
    0x20              //set PWM cycle length= FF cycles, so PWM clock= 1/[(1/32KHz)*FF]= 8KHz   
};

//mark
// Senario Related Reg. table, range= 0x110~0x147
BYTE code sb358x_senario_reg_table[56] =                                                       
{
//   110,  111,  112,  113,  114,  115,  116,  117,
    0xDF, 0x18, 0x00, 0x19, 0xDF, 0x18, 0x00, 0x19, 
//   118,  119,  11A,  11B,  11C,  11D,  11E,  11F,
    0xDF, 0x18, 0x00, 0x19, 0xDF, 0x18, 0x00, 0x19, 
//   120,  121,  122,  123,  124,  125,  126,  127,
    0xDF, 0x18, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 
//   128,  129,  12A,  12B,  12C,  12D,  12E,  12F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   130,  131,  132,  133,  134,  135,  136,  137,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   138,  139,  13A,  13B,  13C,  13D,  13E,  13F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   140,  141,  142,  143,  144,  145,  146,  147,
    0xDF, 0x18, 0x00, 0x19, 0xDF, 0x18, 0x00, 0x19 
};


//mark
// Auto PWM Reg. table, range= 0x148~0x19D
BYTE code sb358x_auto_pwm_reg_table[86] =                                                        
{
//   148,  149,  14A,  14B,  14C,  14D,  14E,  14F,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
//   150,  151,  152,  153,  154,  155,  156,  157,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,     
//   158,  159,  15A,  15B,  15C,  15D,  15E,  15F,
    0xFF, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x01, 0x18,
//   160,  161,  162,  163,  164,  165,  166,  167,
    0xFF, 0xFF, 0xFA, 0xF5, 0xF0, 0xEB, 0xE5, 0xE0,     
//   168,  169,  16A,  16B,  16C,  16D,  16E,  16F,
    0xDB, 0xD6, 0xD1, 0xCC, 0xC7, 0xC2, 0xBC, 0xB5, 
//   170,  171,  172,  173,  174,  175,  176,  177,
    0xB0, 0xAB, 0xA5, 0xA0, 0x9A, 0x95, 0x8C, 0x82,     
//   178,  179,  17A,  17B,  17C,  17D,  17E,  17F,
    0x78, 0x6E, 0x64, 0x50, 0x3C, 0x28, 0x14, 0x00, 
//   180,  181,  182,  183,  184,  185,  186,  187,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         //set MP0~MP7  as 100% PWM duty (0: means 100% duty, 128: means 50% duty, 255: means 0% duty).
//   188,  189,  18A,  18B,  18C,  18D,  18E,  18F,     
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         //set MP8~MP11 as 100% PWM duty (0: means 100% duty, 128: means 50% duty, 255: means 0% duty).
//   190,  191,  192,  193,  194,  195,  196,  197,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//   198,  199,  19A,  19B,  19C,  19D
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// GPIO MISC Reg. table, range= 0x1A0
BYTE code sb358x_gpio_misc_reg_table[1] =                         
{
    0x01
};

BYTE code sb358x_LED_level_table[11] = 
{
    0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE8, 0xD8, 0xC0, 0x80, 0x40, 0x00
};

BYTE code sb358x_TouchKeyMapping[KEYNUMBER] = {CTM_BUTTON_MAPPING_TABLE};

#else

#define KEYNUMBER  6
#define CTM_BUTTON_MAPPING_TABLE  15, 9, 10, 11, 12,14

BYTE code sb357x_LED_level_table[11] = 
{
    0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE8, 0xD8, 0xC0, 0x80, 0x40, 0x00
};
BYTE code sb357x_TouchKeyMapping[KEYNUMBER] = {CTM_BUTTON_MAPPING_TABLE};

#define MENU_LED  	BIT0
#define AUTO_LED  	BIT1
#define WHILTE_LED  	BIT2
#define AMBER_LED  	BIT3
#define PLUS_LED  	BIT4
#define MINUS_LED  	BIT5
#define ALL_LED		MENU_LED | AUTO_LED | PLUS_LED | MINUS_LED | WHILTE_LED | AMBER_LED
#define RAMP_LED		MENU_LED | AUTO_LED | PLUS_LED | MINUS_LED

#endif

#if MainBoardType == MainBoard_6038_M0A||ModelName==AOC_A2272PWR//follow G2  petit 20141226
#define TPREG_POWER                            0x4000
#define TPREG_MENU                              0x2000
#define TPREG_UP                                   0x1000
#define TPREG_DOWN                              0x0200
#define TPREG_EXIT                                0x04
#define ENABLE_KeySignal     //130813 henry
#elif (MainBoardType==MainBoard_8191_M0A)

#define TPREG_POWER                            0x4000
#define TPREG_MENU                              0x2000
#define TPREG_UP                                   0x1000
#define TPREG_DOWN                              0x0200
#define TPREG_EXIT                                0x04
#elif ((MainBoardType == MainBoard_6178_M0A)||(MainBoardType == MainBoard_6223_M0A)||((MainBoardType == MainBoard_7219_M0C)&&(ModelName==AOC_A2472PWRP)))//follow G4  petit 20141226

#if 0 //Philiphs
#define TPREG_POWER                            0x0200
#define TPREG_MENU                              0x1000
#define TPREG_UP                                   0x2000
#define TPREG_DOWN                              0x4000
#define TPREG_EXIT                                0x8000
#else 
#define TPREG_POWER                            0x4000
#define TPREG_MENU                              0x2000
#define TPREG_UP                                   0x1000
#define TPREG_DOWN                              0x0200
#define TPREG_EXIT                                0x04
#endif
#define ENABLE_KeySignal   //130809 henry

#elif (MainBoardType == MainBoard_7414_M0A)
#define TPREG_POWER                           0x24
#define TPREG_MENU                               0x21
#define TPREG_UP                                    0x28
#define TPREG_DOWN                              0x30
#define TPREG_EXIT                                 0x22
#define ENABLE_KeySignal   //130809 henry
#else
#define TPREG_POWER                            0x8000
#define TPREG_MENU                              0x1000
#define TPREG_UP                                   0x0200
#define TPREG_DOWN                              0x4000
#define TPREG_EXIT                                0x2000
#endif


#define TPREG_OSDLOCK               (TPREG_MENU|TPREG_POWER)


#define TPREG_Recovery                		( TPREG_UP | TPREG_POWER)  //0x20//0x10
#define TPREG_FACTORY                 		 (TPREG_UP|TPREG_DOWN|TPREG_POWER) //(TPREG_MENU | TPREG_EXIT | TPREG_POWER)  //0x20//0x10

#define TPREG_KEYPADMASK        ( TPREG_POWER | TPREG_MENU | TPREG_DOWN | TPREG_UP | TPREG_EXIT)//| TPREG_PIVOT)
#define AMBERLED  0x1000//0x1000
#define WhiteLED   0x0001//0x0100 //0x0100


#endif
