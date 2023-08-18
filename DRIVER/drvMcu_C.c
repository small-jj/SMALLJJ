
///////////////////////////////////////
// DRVMCU_V VERSION: V02
////////////////////////////////////////
#include "global.h"
#if ENABLE_ANDROID_IR	//131008 Modify
#include "drv_ir.h"
#define IR_FREQ_FINETUNE    ((g_bMcuPMClock)?(45):(0))
#endif

void Init_WDT( BYTE bEnable )
{
    msWriteByteMask( REG_3C66, BIT2,BIT2);  //clear watchdog reset flag
    msWriteByteMask( REG_3C66, 0x00,BIT2);

    if( bEnable )
    {

#if( ENABLE_WATCH_DOG )
        // initialize the watchdog timer reset interval
        {
            WORD wdt_sel_high;
            wdt_sel_high = 65536 - ( CRYSTAL_CLOCK / 65536 ) * WATCH_DOG_RESET_TIME;
            msWriteByte( REG_3C62, LOBYTE( wdt_sel_high ) );
            msWriteByte( REG_3C63, HIBYTE( wdt_sel_high ) );
            msWriteBit(REG_2B00, FALSE, _BIT1);//MASK DISABLE // Jonson 20110713
        }
#endif  // end of #if( ENABLE_WATCH_DOG )

        msWriteByte( REG_3C60, 0xAA );
        msWriteByte( REG_3C61, 0x55 );
    }
    else
    {
        msWriteByte( REG_3C60, 0x55 );
        msWriteByte( REG_3C61, 0xAA );
        msWriteBit(REG_2B00, TRUE, _BIT1);//MASK ENABLE // Jonson 20110713
    }
}

/*
REG_0212
[0]: Enable GPIO 40, 41 as Uart-0 function
[1]: Enable GPIO 34, 35 as Uart-0 function
[2]: Enable GPIO 02, 00 as Uart-0 function
[3]: Enable GPIO 00, 01 as Uart-1 function ?
[4]: Enable GPIO 20, 21 as Uart-1 function
[5]: Enable GPIO 32, 33 as Uart-1 function
*/
#if ENABLE_DEBUG
void mcuSetUartMux( BYTE ucMuxUart0, BYTE ucMuxUart1 )
{
    msWriteByteMask(REG_0212, ucMuxUart0, BIT2|BIT1|BIT0);
    msWriteByteMask(REG_0212, ucMuxUart1, BIT5|BIT4);
}
#endif
//-------------------------------------------------------------------------------------------------
// spi clock
// SPI clock setting
//
// reg_reserved0[5:0]
//
// h0027    h0026   31  0   reg_reserved0   "Reserved.reg_reserved0[5:0]: for spi clock selectionreg_reserved0[8]: for spi new cycle"
//
//
// reg_ckg_spi[6]
//  0: Crystal clock
//  1: PLL clock
//
// reg_ckg_spi[4:2], clock selection
//
#if ENABLE_DEBUG
DWORD code g_mcuSpiFreqTable[] =
{
CLOCK_4MHZ,       // 0
CLOCK_27MHZ,      // 1
CLOCK_36MHZ,      // 2
CLOCK_43MHZ,      // 3
CLOCK_54MHZ,      // 4
CLOCK_86MHZ,      // 5
CRYSTAL_CLOCK,    // 6
};
#endif

// ucIndex ( PLL clock selection, whenever change, please make sure reg_ckg_spi[5]=0;)
//          1: 36   MHz pass
//          2: 43   MHz pass
//          3: 54   MHz, don't use, reserved for future
//          3: 86   MHz, don't use, reserved for future
//          4: Crystal clock
void mcuSetSpiSpeed( BYTE ucIndex )
{
    if( ucIndex == IDX_SPI_CLK_XTAL)
    {
        msWriteByteMask( REG_08E0, 0, _BIT2 );
    }
    else
    {
#if SPI_SSC_EN    
        if( ucIndex == IDX_SPI_CLK_SSC)
        {
            msWriteByte(REG_1E25, 0);
            msWriteByte(REG_1E28, 0);  
            msWrite2Byte(REG_1122, 0x0080);
            msWriteByte(REG_1133, 0); 
            msWriteByte(REG_1136, 0);           
            msSetupDDR();
            msSetupDDRSSC();
            msWriteByteMask(REG_01BA, (SPI_SSC_SOURCE<<6)|(SPI_SSC_DIVIDER<<1), 0xFE);
        }     
#endif        
        msWriteByteMask( REG_08E0, ucIndex << 3, _BIT5 | _BIT4 | _BIT3);
        msWriteByteMask( REG_08E0, _BIT2, _BIT2 );
    }
}

/*
SPI model select.
0x0: Normal mode, (SPI command is 0x03)
0x1: Enable fast read mode, (SPI command is 0x0B)
0x2: Enable address single & data dual mode, (SPI command is 0x3B)
0x3: Enable address dual & data dual mode, (SPI command is 0xBB)
0xa: Enable address single & data quad mode, (SPI command is 0x6B) (Reserved)
0xb: Enable address quad & data quad mode, (SPI command is 0xEB)
(Reserved
*/
void mcuSetSpiMode( BYTE ucMode )
{
    BYTE ucValue;

    switch( ucMode )
    {
        case SPI_MODE_FR:
            ucValue = 0x01;
            break;

        case SPI_MODE_SADD:
            ucValue = 0x02;
            break;

        case SPI_MODE_DADD:
            ucValue = 0x03;
            break;

        case SPI_MODE_SAQD:
            ucValue = 0x0A;
            msWriteByteMask( REG_0205, _BIT3, _BIT3 );
            break;

        case SPI_MODE_QAQD:
            ucValue = 0x0B;
            msWriteByteMask( REG_0205, _BIT3, _BIT3 );
            break;

        case SPI_MODE_NORMAL:
        default:
            ucValue = 0x00;
    }

    msWriteByte( REG_08E4, ucValue );
#if DEBUG_PRINTDATA
    printData( "SPI Mode = %d ", ucMode );
#endif
}

DWORD code g_mcuPLLFreqTable[] =
{
    CLOCK_4MHZ,            // 0
    CLOCK_12MHZ,           // 1
    CLOCK_MPLL_MHZ,        // 2,
    CLOCK_108MHZ,          // 3,
    CLOCK_86MHZ,           // 4,
    CLOCK_54MHZ,           // 5,   mem_clock
    CLOCK_27MHZ,           // 6,   mem_clock/2
    CLOCK_0MHZ,            // 7
    CLOCK_XTAL,            // 8
};
void mcuSetMcuSpeed( BYTE ucSpeedIdx )
{
    DWORD xdata u32Freq;
    WORD xdata u16Divider0;
    WORD xdata u16Divider1;

    u32Freq = g_mcuPLLFreqTable[ucSpeedIdx];
    u16Divider0 = 1024 - (( _SMOD * u32Freq + u32Freq ) / SERIAL_BAUD_RATE ) / 64;
    u16Divider1 = 1024 - (( u32Freq ) / SERIAL_BAUD_RATE ) / 32;
    if ( ucSpeedIdx == IDX_MCU_CLK_XTAL )
        msWriteByteMask( REG_PM_BC, 0, _BIT0 );
    else
    {
        msWriteByteMask( REG_PM_BB, ucSpeedIdx, ( _BIT2 | _BIT1 | _BIT0 ) );
        msWriteByteMask( REG_PM_BC, _BIT0, _BIT0 );
    }

    // Scaler WDT
    msWriteByte(SC0_00, 0x00);
    msWriteByte(SC0_B2, (u32Freq*4)/CRYSTAL_CLOCK);

    ES = 0;
    IEN2 &= ~ES1;

    S0RELH = HIBYTE( u16Divider0 );
    S0RELL = LOBYTE( u16Divider0 );

    // ENABLE_UART1
    S1RELH = HIBYTE( u16Divider1 );
    S1RELL = LOBYTE( u16Divider1 );
    
#if DEBUG_PRINTDATA
    ES = 1;
    printData( "MCU freq = %d MHz ", u32Freq / 1000 / 1000 );
#endif

#if ENABLE_UART1
#if ENABLE_DEBUG||ENABLE_UART_CONTROL
	IEN2 |= ES1;
#endif
#endif

#if !EXT_TIMER0_1MS
    // timer
    TR0 = 0;
    ET0 = 0;
    u32Freq = u32Freq / 1000;
    u16Divider0 = ( 65536 - ( u32Freq * INT_PERIOD + 6 ) / 12 );
    TH0 = g_ucTimer0_TH0 = HIBYTE( u16Divider0 );
    TL0 = g_ucTimer0_TL0 = LOBYTE( u16Divider0 );
    TR0 = 1;
    ET0 = 1;
#endif

#if ENABLE_ANDROID_IR	//131008 Modify
    u16Divider0 = ( 65536 - ( u32Freq * INT_PERIOD + 6 ) / 12 / 5 + 45 ); // 200uS

    Timer1_TH1 = HIBYTE( u16Divider0 );
    Timer1_TL1 = LOBYTE( u16Divider0 );
    TH1=Timer1_TH1;  //200us reload
    TL1=Timer1_TL1;  //200us reload 
    
#endif

}
//=========================================================
void mcuSetSystemSpeed(BYTE u8Mode)
{
#ifdef FPGA
    u8Mode = SPEED_XTAL_MODE;
#endif

    if (g_u8SystemSpeedMode!=u8Mode)
    { //MCU speed >= SPI speed
        switch(u8Mode)
        {
            case SPEED_4MHZ_MODE:
                mcuSetSpiSpeed(IDX_SPI_CLK_4MHZ); //spi speed down 1st
                mcuSetSpiMode( SPI_MODE_NORMAL );
                mcuSetMcuSpeed(IDX_MCU_CLK_4MHZ);
                g_bMcuPMClock = 1; // 120925 coding addition
                break;
            case SPEED_12MHZ_MODE:
                if (g_u8SystemSpeedMode>SPEED_12MHZ_MODE)
                {
                    mcuSetSpiSpeed( IDX_SPI_CLK_12MHZ );
                    mcuSetSpiMode( SPI_MODE_NORMAL );
                    mcuSetMcuSpeed( IDX_MCU_CLK_12MHZ);
                }
                else
                {
                    mcuSetMcuSpeed( IDX_MCU_CLK_12MHZ );
                    mcuSetSpiMode( SPI_MODE_NORMAL );
                    mcuSetSpiSpeed( IDX_SPI_CLK_12MHZ );
                }
                g_bMcuPMClock = 1; // 120925 coding addition
                break;
            case SPEED_XTAL_MODE:
                if (g_u8SystemSpeedMode>SPEED_XTAL_MODE)
                {
                    mcuSetSpiSpeed( IDX_SPI_CLK_XTAL );
                    mcuSetSpiMode( SPI_MODE_NORMAL );
                    mcuSetMcuSpeed( IDX_MCU_CLK_XTAL );
                }
                else
                {
                    mcuSetMcuSpeed( IDX_MCU_CLK_XTAL );
                    mcuSetSpiMode( SPI_MODE_NORMAL );
                    mcuSetSpiSpeed( IDX_SPI_CLK_XTAL );
                }
                g_bMcuPMClock = 1; // 120925 coding addition
                break;
            default: //normal
                mcuSetSpiMode( SPI_MODE );
                msWriteByte( REG_1EDC, 0x00 );
 	         ForceDelay1ms(10);
                msWriteByte( REG_1ED1, BIT2 );
                msWriteByte( REG_1ED2, 0x42 );
                ForceDelay1ms(10);
                mcuSetMcuSpeed( MCU_SPEED_INDEX );
                mcuSetSpiSpeed( SPI_SPEED_INDEX );
                g_bMcuPMClock = 0; // 120925 coding addition
              break;
        }
        g_u8SystemSpeedMode=u8Mode;
        //SetForceDelayLoop();
    }
}




#if 1//ENABLE_HK_DATA_ON_DRAM
void mcuInitXdataMapToDRAM(void)
{
    /*
    Initial XDATA on DRAM.
    Win0: MCU view 0x5000~0xEFFF(40KB)
    Win1: MCU view 0xF000~0xFFFF(4KB)
    */
    msWriteByte(REG_2BC6, WIN0_ADDR_START); // unit is K Byte
    msWriteByte(REG_2BC7, WIN0_ADDR_END);

    msWriteByte(REG_2BCA, WIN1_ADDR_START);
    msWriteByte(REG_2BCB, WIN1_ADDR_END);

    msWriteBit(REG_2BC4, _ENABLE, _BIT2);   //  enable
}

void mcu4kXdataMapToDRAM(DWORD dw4k)
{
    //printf("\r\nWin1: Access DRAM %dth 4KB", w4k);
    msWrite2Byte(REG_2BCC, dw4k);
    msWrite2Byte(REG_2BCE, (dw4k >> 16));
}

void mcu40kXdataMapToDRAM(WORD w64k)
{
    /*
    The low byte address to access xdata from MIU.
    The granularity is 64k bytes.
    The actual address[26:0] to miu would be
    {reg_sdr_xd_map[10:8],reg_sdr_xd_map[7:0],xdata_addr[15:0]},
    where xdata_addr[15:0] is mcu xdata address of 64k bytes.
    reg_sdr_xd_map[10:8]
    */
    // printf("\r\nWin0: Access DRAM %dth 64KB", w64k);
    msWrite2Byte(REG_2BC8, w64k);
}

void mcuXdataMapToDRAM(DWORD dwADDR)
{
    xdata WORD Nth64k;
    xdata WORD Nth4k;

    Nth64k = dwADDR >> 16; //unit is 64K Byte
    Nth4k  = (dwADDR + ((DWORD)WIN1_ADDR_START<<10)) >> 12;

    mcu40kXdataMapToDRAM(Nth64k);
    mcu4kXdataMapToDRAM(Nth4k);  // let win0 & win1 start from the same address
}
#endif
#if (ENABLE_HK_CODE_ON_DRAM )
void mcuDMADownloadCode(DWORD dwSourceAddr, DWORD dwDestinAddr, DWORD dwByteCount)
{
#if 0//CHIP_ID == MST8556T
    msWriteByte(REG_1401, 0x01);
    msWriteByte(REG_1400, 0x53);

    msWriteByte(REG_1402, (BYTE)(dwSourceAddr));
    msWriteByte(REG_1403, (BYTE)(dwSourceAddr>>8));
    msWriteByte(REG_1404, (BYTE)(dwSourceAddr>>16));
    msWriteByte(REG_1405, (BYTE)(dwSourceAddr>>24));

    msWriteByte(REG_1406, (BYTE)(dwDestinAddr));
    msWriteByte(REG_1407, (BYTE)(dwDestinAddr>>8));
    msWriteByte(REG_1408, (BYTE)(dwDestinAddr>>16));
    msWriteByte(REG_1409, (BYTE)(dwDestinAddr>>24));

    msWriteByte(REG_140A, (BYTE)(dwByteCount));
    msWriteByte(REG_140B, (BYTE)(dwByteCount>>8));
    msWriteByte(REG_140C, (BYTE)(dwByteCount>>16));
    msWriteByte(REG_140D, (BYTE)(dwByteCount>>24));

    msWriteByte(REG_140E, 0x01);

    while(!_bit0_(msReadByte(REG_1410)));   // wait DMA finish
    msWriteByte(REG_1412, 0x01); //clear flag
    msWriteByte(REG_1412, 0x00);
    msWriteBit(REG_1018, 1, _BIT3);
    msWrite2Byte(REG_2B80, (dwDestinAddr>>16));
#elif CHIP_ID == CHIP_TSUM2
    XDATA BYTE uc_ID;

    msWriteByteMask(REG_1246,0,_BIT4|_BIT3|_BIT2);
    msWriteByte(REG_3304,0x25);
    msWriteByte(REG_3305,0x20);

    msWriteByte(REG_3308, (BYTE)(dwSourceAddr));
    msWriteByte(REG_3309, (BYTE)(dwSourceAddr>>8));
    msWriteByte(REG_330A, (BYTE)(dwSourceAddr>>16));
    msWriteByte(REG_330B, (BYTE)(dwSourceAddr>>24));

    msWriteByte(REG_330C, (BYTE)(dwDestinAddr));
    msWriteByte(REG_330D, (BYTE)(dwDestinAddr>>8));
    msWriteByte(REG_330E, (BYTE)(dwDestinAddr>>16));
    msWriteByte(REG_330F, (BYTE)(dwDestinAddr>>24));

    msWriteByte(REG_3310, (BYTE)(dwByteCount));
    msWriteByte(REG_3311, (BYTE)(dwByteCount>>8));
    msWriteByte(REG_3312, (BYTE)(dwByteCount>>16));
    msWriteByte(REG_3313, (BYTE)(dwByteCount>>24));

    uc_ID = MIU_ID_MIU_R2_CPU_I | MIU_ID_MIU_R2_CPU_D | MIU_ID_MIU_BDMA;
    msMiuProtectCtrl(MIU_PROTECT_0,_ENABLE,uc_ID, MCU_ON_DRAM_START_ADDR, MCU_CODE_SIZE );

    msWriteByte(REG_2080,0x00);

#if 0
    msWriteByteMask(REG_2B1A,0,BIT0);  // enable bdma int
    msWriteByteMask(REG_3306,BIT1,BIT1); //enable bdma int
    msWriteBit(REG_3300,1,_BIT0);
#else
    msWriteByteMask(REG_2B1A,0,BIT0);  // disable bdma int
    msWriteByteMask(REG_3306,0,BIT1); //disable bdma int
    msWriteBit(REG_3300,1,_BIT0);
    while(!(msReadByte(REG_3302)&BIT3));
    msWriteByte(REG_12C4,0x00);
    msWrite2Byte(REG_1246,0x0000);
    msWriteByte(REG_2080,0x27);
#endif

#endif

}
#if (ENABLE_HK_CODE_ON_DRAM)
void mcuArrangeCodeAddr(BYTE ucType, DWORD dwAddrStart, DWORD dwAddrEnd)
{
    BYTE ucTemp;
    if (ucType==_SPI)
        ucTemp = 8;
    else
        ucTemp = 0;

    msWriteByte(0x100C+ucTemp, (BYTE)(dwAddrStart)); // 0x1014
    msWriteByte(0x100D+ucTemp, (BYTE)(dwAddrStart>>8)); // 0x1015
    msWriteByte(0x1008+ucTemp, (BYTE)(dwAddrStart>>16)); // 0x1010
    msWriteByte(0x1009+ucTemp, (BYTE)(dwAddrStart>>24)); // 0x1011

    msWriteByte(0x100E+ucTemp, (BYTE)(dwAddrEnd)); // 0x1016
    msWriteByte(0x100F+ucTemp, (BYTE)(dwAddrEnd>>8)); // 0x1017
    msWriteByte(0x100A+ucTemp, (BYTE)(dwAddrEnd>>16)); // 0x1012
    msWriteByte(0x100B+ucTemp, (BYTE)(dwAddrEnd>>24)); // 0x1013

    if (ucType==_SPI)
        ucTemp = _BIT1;
    else
        ucTemp = _BIT2;

    if (dwAddrStart < dwAddrEnd)
        msWriteBit(REG_1018, _ENABLE, ucTemp);
    else
        msWriteBit(REG_1018, _DISABLE, ucTemp);

}
#endif
#endif

