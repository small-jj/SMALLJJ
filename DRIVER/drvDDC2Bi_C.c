
///////////////////////////////////////
// DRVDDC2BI_7 VERSION: V02
////////////////////////////////////////
#include "global.h"
#if DDCCI_ENABLE_DEBUG
#include "msOSD.h"
#include "msOSDFunction.h"
#endif
//#define MaxBufLen 50						//20120625 Delete
BYTE xdata rxInputPort; // Annie 2006.7.5
BYTE idata rxComboPort; // Combo port index
BYTE xdata rxIndex = 0;
BYTE xdata rxStatus;
BYTE xdata rxLength = 0;
#if !D2B_HW_CheckSum
BYTE xdata rxChkSum = 0;
#endif
BYTE xdata txStatus;
BYTE *txBufferPtr;
BYTE xdata txLength;
//BYTE xdata sendData;


code BYTE nullMsg1[3] =
{
    0x6e, 0x80, 0xbe
};
code BYTE nullMsg[3] =
{
    0x51, 0x80, 0xbe
};

#if D2B_XShared_DDCBuffer
BYTE *DDCBuffer;
#else
BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif

#if D2B_FIFO_Mode
WORD idata txIndex;
WORD idata Previous_DDC2MCU_CUR_ADR;
WORD idata Present_DDC2MCU_CUR_ADR;
WORD idata Present_DDC2MCU_START_ADR;
BYTE idata D2BErrorFlag;
#if D2B_XDATA_DEBUG
BYTE xdata XSRAMBuffer[D2B_FIFO_XdataSize+256] _at_ XDATA_DDC_ADDR_START;
BYTE xdata IntCount;
BYTE xdata IntCountTmp;
#else
BYTE xdata XSRAMBuffer[D2B_FIFO_XdataSize] _at_ XDATA_DDC_ADDR_START;
#endif
#endif

#if D2B_FIFO_Mode
BYTE DDC2Bi_FIFOMODE_READ_CUR(BYTE InputPort)
{
    BYTE CurValue=0;

    if(InputPort==InputCombo_A0) // A0
        CurValue = msRegs[REG_3EE4];
#if DDC_Port_D0    
    else if(InputPort==InputCombo_D0) // D0
        CurValue = msRegs[REG_3EC6];
#endif
#if DDC_Port_D1
    else if(InputPort==InputCombo_D1) // D1
        CurValue = msRegs[REG_3ECC];
#endif
#if DDC_Port_D2    
    else //if(InputPort==InputCombo_D2) // D2
        CurValue = msRegs[REG_3ED2];
#endif
    return CurValue;
}

BYTE DDC2Bi_FIFOMODE_READ_START(BYTE InputComboPort)
{
    BYTE StartValue=0;

    if(InputComboPort==InputCombo_A0) // A0
        StartValue = msRegs[REG_3EE5];
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        StartValue = msRegs[REG_3EC7];
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        StartValue = msRegs[REG_3ECD];
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        StartValue = msRegs[REG_3ED3];
#endif
    return StartValue;
}

WORD DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(BYTE InputComboPort)
{
    WORD XdataAddrStart=0;

    if(InputComboPort==InputCombo_A0) // A0
        XdataAddrStart = D2B_FIFO_XdataAddressStart_A0;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        XdataAddrStart = D2B_FIFO_XdataAddressStart_D0;
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        XdataAddrStart = D2B_FIFO_XdataAddressStart_D1;
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2) // D2
        XdataAddrStart = D2B_FIFO_XdataAddressStart_D2;
#endif
    return XdataAddrStart-D2B_FIFO_XdataAddressStart;
}

void DDC2Bi_FIFOMODE_SET_RW_DONE(BYTE InputComboPort)
{
    if(InputComboPort==InputCombo_A0) // A0
        msRegs[REG_3EE6] |= (BIT3);
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        msRegs[REG_3EC8] |= (BIT3);
#endif
#if DDC_Port_D1
    else if(InputComboPort==InputCombo_D1) // D1
        msRegs[REG_3ECE] |= (BIT3);
#endif
#if DDC_Port_D2
    else //if(InputComboPort==InputCombo_D2) // D2
        msRegs[REG_3EE0] |= (BIT3);        
#endif	
}

void DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(BYTE InputComboPort)
{
    if(InputComboPort==InputCombo_A0) // A0
        msRegs[REG_3EE6] |= (BIT5|BIT4);
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        msRegs[REG_3EC8] |= (BIT5|BIT4);
#endif
#if DDC_Port_D1
    else if(InputComboPort==InputCombo_D1) // D1
        msRegs[REG_3ECE] |= (BIT5|BIT4);
#endif
#if DDC_Port_D2
    else //if(InputComboPort==InputCombo_D2) // D2
        msRegs[REG_3EE0] |= (BIT5|BIT4);        
#endif	
}

BYTE DDC2Bi_FIFOMODE_READ_FULL_FLAG(BYTE InputComboPort)
{
    BYTE FlagValue=0;

    if(InputComboPort==InputCombo_A0) // A0
        FlagValue = msRegs[REG_3EE6];
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        FlagValue = msRegs[REG_3EC8];
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        FlagValue = msRegs[REG_3ECE];
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        FlagValue = msRegs[REG_3EE0];
#endif
    return FlagValue&BIT6;
}

#if !D2B_XShared_DDCBuffer
BYTE DDC2Bi_FIFOMODE_READ_EMPTY_FLAG(BYTE InputComboPort)
{
    BYTE FlagValue=0;

    if(InputComboPort==InputCombo_A0) // A0
        FlagValue = msRegs[REG_3EE6];
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        FlagValue = msRegs[REG_3EC8];
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        FlagValue = msRegs[REG_3ECE];
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        FlagValue = msRegs[REG_3EE0];
#endif
    return FlagValue&BIT7;
}
#endif

BYTE DDC2Bi_FIFOMODE_READ_HW_CHKSUM_FLAG(BYTE InputComboPort)
{
    BYTE HWCSValue=0;

    if(InputComboPort==InputCombo_A0) // A0
        HWCSValue = msRegs[REG_3EC2]&BIT0;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        HWCSValue = msRegs[REG_3EC2]&BIT1;
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        HWCSValue = msRegs[REG_3EF0]&BIT0;
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        HWCSValue = msRegs[REG_3EF0]&BIT1;
#endif
    return HWCSValue;
}

void DDC2Bi_CLR_INT(BYTE InputComboPort, BYTE ClrBits)
{    
    if(InputComboPort==InputCombo_A0) // A0
        DDCADC_INT_CLR |= ClrBits;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        DDCDVI0_INT_CLR |= ClrBits;
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        DDCDVI1_INT_CLR |= ClrBits;
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        DDCDVI2_INT_CLR |= ClrBits;
#endif
}
#endif



void DDC2Bi_SET_RBUF(BYTE InputComboPort, BYTE RBufData)
{
    if(InputComboPort==InputCombo_A0) // A0
        ADC_RBUF_WDP = RBufData;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        DDCDVI0_RBUF_WDP = RBufData;
#endif
#if DDC_Port_D1
    else if(InputComboPort==InputCombo_D1) // D1
        DDCDVI1_RBUF_WDP = RBufData;
#endif
#if DDC_Port_D2
    else //if(InputComboPort==InputCombo_D2) // D2
        DDCDVI2_RBUF_WDP = RBufData;        
#endif	
}

void DDC2Bi_SET_WP_READY(BYTE InputComboPort)
{
    if(InputComboPort==InputCombo_A0) // A0
        DDC_ADC_WP_READY();
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        DDC_DVI0_WP_READY();
#endif
#if DDC_Port_D1
    else if(InputComboPort==InputCombo_D1) // D1
        DDC_DVI1_WP_READY();
#endif
#if DDC_Port_D2
    else //if(InputComboPort==InputCombo_D2) // D2
        DDC_DVI2_WP_READY();      
#endif	
}
BYTE DDC2Bi_Read_INT(BYTE InputComboPort)
{
    BYTE IntData=0;
    
    if(InputComboPort==InputCombo_A0) // A0
        IntData = DDCADC_INT_FLAG;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        IntData = DDCDVI0_INT_FLAG;
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        IntData = DDCDVI1_INT_FLAG;
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        IntData = DDCDVI2_INT_FLAG;
#endif
    return IntData;
}

BYTE DDC2Bi_Read_WBUF(BYTE InputComboPort)
{
    BYTE WbufData=0;
    
    if(InputComboPort==InputCombo_A0) // A0
        WbufData = ADC_WBUF_RDP;
#if DDC_Port_D0
    else if(InputComboPort==InputCombo_D0) // D0
        WbufData = DDCDVI0_WBUF_RDP;
#endif
#if DDC_Port_D1    
    else if(InputComboPort==InputCombo_D1) // D1
        WbufData = DDCDVI1_WBUF_RDP;
#endif
#if DDC_Port_D2    
    else //if(InputComboPort==InputCombo_D2)// D2
        WbufData = DDCDVI2_WBUF_RDP;
#endif
    return WbufData;
}

void drvDDC2Bi_Init( void )
{
    // mask all ddc interrupt
    D2B_INT_MASK_ALL(); // drvDDC2Bi_Init();

    DDC2Bi_InitRx();
    txStatus = DDC2B_CLEAR;

    txBufferPtr = &nullMsg1[0];
    txLength = sizeof( nullMsg1 );
    
    D2B_SET_ID_VGA(TRUE);
    D2B_INT_MASK_VGA();
    CLR_ADC_INT_FLAG();
    DDCADC_RBUF_WDP = *txBufferPtr++;
    DDC_ADC_WP_READY();    

#if DDC_Port_D0
    D2B_SET_ID_DVI0(TRUE);
    D2B_INT_MASK_DVI0();
    CLR_DVI0_INT_FLAG();
    DDCDVI0_RBUF_WDP = *txBufferPtr++;
    DDC_DVI0_WP_READY();    
#endif
#if DDC_Port_D1
    D2B_SET_ID_DVI1(TRUE);
    D2B_INT_MASK_DVI1();
    CLR_DVI1_INT_FLAG();
    DDCDVI1_RBUF_WDP = *txBufferPtr++;
    DDC_DVI1_WP_READY();    
#endif
#if DDC_Port_D2
    D2B_SET_ID_DVI2(TRUE);
    D2B_INT_MASK_DVI2();
    CLR_DVI2_INT_FLAG();
    DDCDVI2_RBUF_WDP = *txBufferPtr++;
    DDC_DVI2_WP_READY();    
#endif

#if ENABLE_DP_INPUT
    D2B_SET_ID_DP(TRUE);//DDCDP_DDCCI_ID=0xB7;
#endif	

#if 0//ENABLE_3D_FUNCTION && GLASSES_TYPE==GLASSES_NVIDIA
    DDCDVI_NV3D_DDCCI_ID = 0xFD;
    DDCDVI_NV3D_INTMASK_EN = BIT6 | BIT5 | BIT2 | BIT1;
    CLR_DDC_DVI_NV3D_INT_FLAG();
#endif

#if D2B_FIFO_Mode
  #if D2B_XShared_DDCBuffer
    DDCBuffer = &XSRAMBuffer[0];
  #endif
    //DDC_Port_A0
    D2B_SET_FIFOMODE_VGA(TRUE);
    D2B_SET_FIFOMODE_ENHANCE_VGA(D2B_FIFO_Enhance);
    D2B_SET_FIFOMODE_SIZE_VGA(D2B_FIFOSize_INDEX);
    D2B_SET_FIFOMODE_XDATAMAP_VGA(D2B_FIFO_XdataAddressStart_A0);    
  #if DDC_Port_D0
    D2B_SET_FIFOMODE_D0(TRUE);
    D2B_SET_FIFOMODE_ENHANCE_D0(D2B_FIFO_Enhance);
    D2B_SET_FIFOMODE_SIZE_D0(D2B_FIFOSize_INDEX);
    D2B_SET_FIFOMODE_XDATAMAP_D0(D2B_FIFO_XdataAddressStart_D0);
  #endif
  #if DDC_Port_D1
    D2B_SET_FIFOMODE_D1(TRUE);
    D2B_SET_FIFOMODE_ENHANCE_D1(D2B_FIFO_Enhance);
    D2B_SET_FIFOMODE_SIZE_D1(D2B_FIFOSize_INDEX);
    D2B_SET_FIFOMODE_XDATAMAP_D1(D2B_FIFO_XdataAddressStart_D1);
  #endif
  #if DDC_Port_D2
    D2B_SET_FIFOMODE_D2(TRUE);
    D2B_SET_FIFOMODE_ENHANCE_D2(D2B_FIFO_Enhance);
    D2B_SET_FIFOMODE_SIZE_D2(D2B_FIFOSize_INDEX);
    D2B_SET_FIFOMODE_XDATAMAP_D2(D2B_FIFO_XdataAddressStart_D2);
  #endif  
#endif
#if D2B_HW_CheckSum
    D2B_SET_D2B_HW_CheckSum(_ENABLE, DDC_Port_D2, DDC_Port_D1, DDC_Port_D0);
#endif

    INT_IRQ_D2B_ENABLE(TRUE); //enable d2b int
}

void drvDDC2Bi_MessageReady( void )
{
#if JRY_Color_Tool_Functing
if(ATEModeFlag)
{
	if(ubAutoAlign==0)
		Clr_ATEModeFlag();//
  	DDCBuffer[3]= 0x50^0x6E^DDCBuffer[0]^DDCBuffer[1]^DDCBuffer[2];
}
else
#endif	
{
    DDCBuffer[0] |= DDC2Bi_CONTROL_STATUS_FLAG;
    DDCBuffer[( DDCBuffer[0] &~DDC2Bi_CONTROL_STATUS_FLAG ) + 1] = DDC2Bi_ComputeChecksum(( DDCBuffer[0] &~DDC2Bi_CONTROL_STATUS_FLAG ) + 1 );
    DDC2Bi_GetTxBuffer();//如果有效数据正在发送，延时20秒
}
    txBufferPtr = &DDCBuffer[0];
	////  通过把DDCBuffer数组的数据显示在OSD上，来判断IIC通讯是否正常，查看发送了哪些指令
#if DDCCI_ENABLE_DEBUG
    Osd_Show();
    Osd_Draw4Num( 1, 0, DDCBuffer[0] );
    Osd_Draw4Num( 1, 1, DDCBuffer[1] );
    Osd_Draw4Num( 1, 2, DDCBuffer[2] );
    Osd_Draw4Num( 1, 3, DDCBuffer[3] );
    Osd_Draw4Num( 1, 4, DDCBuffer[4] );
    Osd_Draw4Num( 1, 5, DDCBuffer[5] );
    Osd_Draw4Num( 1, 6, DDCBuffer[6] );
    Osd_Draw4Num( 1, 7, DDCBuffer[7] );
    Osd_Draw4Num( 1, 8, DDCBuffer[8] );
    Osd_Draw4Num( 1, 9, DDCBuffer[9] );
    Delay1ms( 1000 );
#endif//加上两个地址的长度
    txLength = ( DDCBuffer[0] & ( ~DDC2Bi_CONTROL_STATUS_FLAG ) ) + 2;

 if(!CURRENT_INPUT_IS_DISPLAYPORT())    //20121030
  {
#if D2B_FIFO_Mode
    if( txLength > 0 )
    {
        WORD i=0;
        BYTE WriteXdataST_Add;

#if D2B_FIFO_Enhance
        WriteXdataST_Add = DDC2Bi_FIFOMODE_READ_CUR(rxComboPort) + 1;
#else
        WriteXdataST_Add= 0;
#endif
        
        XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(rxComboPort)+(WriteXdataST_Add%D2B_FIFO_Size)] = 0x6E;
#if !D2B_XShared_DDCBuffer                
        for( i = 0; i < txLength; i++ )
        {            
            XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(rxComboPort)+(( WriteXdataST_Add+i+1 )%D2B_FIFO_Size)] = DDCBuffer[i];

            if( i==(D2B_FIFO_Size-2) )
            {
                txIndex = D2B_FIFO_Size-1;
                break;
            }
        }
#endif        
        DDC2Bi_SET_WP_READY(rxComboPort);

    }
#endif
}
}

void drvDDC2Bi_ParseCommand( void )
{
    BYTE length; //, command;
    length = DDCBuffer[LENGTH] & 0x7F;
    if( rxIndex <= 0 )
        return ;
    if( length <= 0 )
    {
        txBufferPtr = &nullMsg1[1];
        txLength = sizeof( nullMsg1 );

        DDC2Bi_SET_RBUF(rxComboPort, DDC2B_DEST_ADDRESS);//向目的地址发送数据 
    }

#if D2B_XDATA_DEBUG
    {
        BYTE ii;
        for (ii=0;ii</*16*/24;ii++)
            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+24/*32*/+ii] = DDCBuffer[ii];
    }
#endif

#if DDCCI_FILTER_FUNCTION
    if(DDCCICommandExecutable())
#endif        
    length = AlignControl();//解析数据并执行相关操作
    

    if( length <= 0 )
    {
        DDCBuffer[0] = 0x80;
        //return ;
    }
    else if( length == 0xFE || length == 0xFD )
    {
        DDCBuffer[0] = 0x80;
    }
    DDC2Bi_MessageReady();//接受准备好要返回的数据，准备发送


    DDC2Bi_SET_RBUF(rxComboPort, DDC2B_DEST_ADDRESS);//向目的地址发送数据        

}

#if D2B_FIFO_Mode
void drvDoDDCCI( BYTE Source ) // Annie 2006.7.5
{
    BYTE intFlag;
    WORD u8AddPoint;

    intFlag = DDC2Bi_Read_INT(Source);

    if( intFlag )
    {
        if(DDC_RW_SRAM_FLAG) // DDC access xdata fail
        {
            D2BErrorFlag=1;
            DDC2Bi_InitRx();

#if D2B_XDATA_DEBUG
            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = 0x33;
            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0x33;
            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EEA];
            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
            IntCount++;
#endif
            DDC_RW_SRAM_CLR;
            DDC2Bi_FIFOMODE_SET_RW_DONE(Source);
            DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source);
            if( _bit7_( DDC2Bi_Read_INT(Source)) )
                DDC2Bi_CLR_INT(Source, BIT7);
            return;            
        }
    
        switch( intFlag &( TXBI | RCBI ) )
        {
            // TX int
            case TXBI:
                //txStatus = DDC2B_MSGON;                // no characters left
                Previous_DDC2MCU_CUR_ADR = Present_DDC2MCU_CUR_ADR;           
                Present_DDC2MCU_CUR_ADR = DDC2Bi_FIFOMODE_READ_CUR(Source); // MUST
#if D2B_XDATA_DEBUG 
                if(IntCount>=32)
                {
                    IntCount=31;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+48+(IntCount%16)+(IntCount/16)*80] = IntCount|0xC0;
                }else
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+48+(IntCount%16)+(IntCount/16)*80] = IntCount|0x80;
                
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0x77;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = txIndex;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];

                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+9] = D2BErrorFlag;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+10] = (msRegs[REG_3EE6]);  
#endif

                if(txIndex) // Remaining Tx
                {
#if !D2B_XShared_DDCBuffer                                    
                    if( (DDC2Bi_FIFOMODE_READ_EMPTY_FLAG(Source)) || (D2BErrorFlag==1) ) // Buffer Read Empty
                    {
                        D2BErrorFlag=1;
                        //u8TxStatus=DDC2B_CLEAR;
#if D2B_XDATA_DEBUG
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = 0x77;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0x77;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = 0x77;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
                        IntCount++;                        
#endif
                        DDC2Bi_FIFOMODE_SET_RW_DONE(Source);
                        DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source);                                               
                        return;
                    }

                    Present_DDC2MCU_START_ADR = DDC2Bi_FIFOMODE_READ_START(Source);
               

                    if( _bit7_( DDC2Bi_Read_INT(Source)) )
                    {
                        if( Present_DDC2MCU_CUR_ADR < Present_DDC2MCU_START_ADR )
                        {
                            Present_DDC2MCU_CUR_ADR += ( BIT0 << ( D2B_FIFOSize_INDEX + 3 ) );
                        }                                               
#if D2B_XDATA_DEBUG
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR|0x80;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR|0x80;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = Previous_DDC2MCU_CUR_ADR|0x80;                  
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
#endif        
                        for( u8AddPoint = Present_DDC2MCU_START_ADR; u8AddPoint <= Present_DDC2MCU_CUR_ADR; u8AddPoint++ )
                        {
                            XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size] = DDCBuffer[txIndex++] ;
                            if( txIndex >= txLength )
                            {
                                txIndex=0;
                                Present_DDC2MCU_CUR_ADR &= (D2B_FIFO_Size-1);
                                break;
                            }
                        }
                    }
                    else
                    {
                        while( Present_DDC2MCU_CUR_ADR<Previous_DDC2MCU_CUR_ADR )
                        {
                            Present_DDC2MCU_CUR_ADR += ( BIT0 << ( D2B_FIFOSize_INDEX + 3 ) );
                        }
#if D2B_XDATA_DEBUG                        
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = Previous_DDC2MCU_CUR_ADR;  
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
#endif                    
                        for( u8AddPoint = Previous_DDC2MCU_CUR_ADR + 1; u8AddPoint <= Present_DDC2MCU_CUR_ADR; u8AddPoint++ )
                        {
                            XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size] = DDCBuffer[txIndex++] ;
                            if( txIndex >= txLength )
                            {
                                txIndex=0;
                                Present_DDC2MCU_CUR_ADR &= (D2B_FIFO_Size-1);
                                break;
                            }
                        }
                    }      

                    if(DDC2Bi_FIFOMODE_READ_EMPTY_FLAG(Source)) // Buffer Read Empty at Race condition
                    {
                        D2BErrorFlag=1;
                        //u8TxStatus=DDC2B_CLEAR;
#if D2B_XDATA_DEBUG
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = 0x66;
                        XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
#endif
                        DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source); // clear
                    }
#endif // #if !D2B_XShared_DDCBuffer                    
                }
                else
                {
                   DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source); // clear
                }
                
                DDC2Bi_FIFOMODE_SET_RW_DONE(Source); // To prevent Full_Error_flag
                if( _bit7_( DDC2Bi_Read_INT(Source)) )
                    DDC2Bi_CLR_INT(Source, BIT7);
                
                break;

            // RX int    
            case RCBI:
                Previous_DDC2MCU_CUR_ADR = Present_DDC2MCU_CUR_ADR;
                Present_DDC2MCU_CUR_ADR = DDC2Bi_FIFOMODE_READ_CUR(Source);
                Present_DDC2MCU_START_ADR = DDC2Bi_FIFOMODE_READ_START(Source);

#if D2B_XDATA_DEBUG
                if( _bit7_( DDC2Bi_Read_INT(Source)) )//( _bit7_( msRegs[REG_3E10] ) == 1 )
                    IntCount=0;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+11] = D2BErrorFlag;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+12] = (msRegs[REG_3EE6]);                
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+48+(IntCount%16)+(IntCount/16)*80] = IntCount;               
#endif

                if(DDC2Bi_FIFOMODE_READ_FULL_FLAG(Source)) // Buffer Write Overflow
                {
                    D2BErrorFlag=1;
                    DDC2Bi_InitRx();

#if D2B_XDATA_DEBUG
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = 0xFF;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0xFF;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = 0xFF;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
                    IntCount++;                    
#endif
                    DDC2Bi_FIFOMODE_SET_RW_DONE(Source);
                    DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source);
                    if( _bit7_( DDC2Bi_Read_INT(Source)) )
                        DDC2Bi_CLR_INT(Source, BIT7);

                    return;
                }
                else if( (D2BErrorFlag==1) && ( _bit7_( DDC2Bi_Read_INT(Source))==0 ) ) // Not New Command
                {
                    DDC2Bi_InitRx();

#if D2B_XDATA_DEBUG
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = 0x88;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0x88;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = 0xFF;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
                    IntCount++;                    
#endif
                    DDC2Bi_FIFOMODE_SET_RW_DONE(Source);
                    
                    return;
                }
                else
                {
                    D2BErrorFlag=0;
                }

#if D2B_XDATA_DEBUG
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+13] = Previous_DDC2MCU_CUR_ADR;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+14] = Present_DDC2MCU_CUR_ADR;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+15] = Present_DDC2MCU_START_ADR;
#endif                     

                if( _bit7_( DDC2Bi_Read_INT(Source)) )
                {
                    rxIndex = 0;
                    rxLength = 0;
#if !D2B_HW_CheckSum                    
                    rxChkSum = INITRxCK;
#endif
#if !D2B_XShared_DDCBuffer
                    if( Present_DDC2MCU_CUR_ADR < Present_DDC2MCU_START_ADR )
                    {
                        Present_DDC2MCU_CUR_ADR += ( BIT0 << ( D2B_FIFOSize_INDEX + 3 ) );
                    }
#endif

#if D2B_XDATA_DEBUG
                    {
                        BYTE xdata ii;
                        for (ii=0;ii</*16*/24;ii++)
                            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+24/*32*/+ii] = 0;

                        for (ii=0;ii<32;ii++)
                        {
                            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(ii%16)+(ii/16)*80] = 0;
                            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(ii%16)+(ii/16)*80] = 0;
                            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(ii%16)+(ii/16)*80] = 0;     
                            XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(ii%16)+(ii/16)*80] = 0;
                        }
                    }                   
#endif


#if D2B_XDATA_DEBUG
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR|0x80;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR|0x80;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = Previous_DDC2MCU_CUR_ADR|0x80;     
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];                          
#endif
#if D2B_XShared_DDCBuffer              
                    DDCBuffer = &XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+1];
#endif
                    for( u8AddPoint = Present_DDC2MCU_START_ADR + 1; u8AddPoint <= Present_DDC2MCU_CUR_ADR; u8AddPoint++ )
                    {
#if !D2B_XShared_DDCBuffer                    
                        DDCBuffer[rxIndex++] = XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size];
#else
                        rxIndex++;
#endif
#if !D2B_HW_CheckSum                              
                        rxChkSum ^= XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size];
#endif
                    }
                }
                else
                {
#if D2B_XDATA_DEBUG
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = Previous_DDC2MCU_CUR_ADR; 
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
#endif
#if !D2B_XShared_DDCBuffer
                    while( Present_DDC2MCU_CUR_ADR<=Previous_DDC2MCU_CUR_ADR )
                    {
                        Present_DDC2MCU_CUR_ADR += ( BIT0 << ( D2B_FIFOSize_INDEX + 3 ) );
                    }
#endif                    
                
                    for( u8AddPoint = Previous_DDC2MCU_CUR_ADR + 1; u8AddPoint <= Present_DDC2MCU_CUR_ADR; u8AddPoint++ )
                    {
#if !D2B_XShared_DDCBuffer                                        
                        DDCBuffer[rxIndex++] = XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size];
#else
                        rxIndex++;
#endif
#if !D2B_HW_CheckSum                          
                        rxChkSum ^= XSRAMBuffer[DDC2Bi_FIFOMODE_XDATA_ADDR_OFFSET(Source)+u8AddPoint%D2B_FIFO_Size];
#endif
                    }
                }

                // CheckSum
                if(rxIndex>0 && rxLength==0)
                    rxLength = DDCBuffer[0] & ~DDC2Bi_CONTROL_STATUS_FLAG;

#if D2B_HW_CheckSum
                if( ( (rxLength+ 2) == rxIndex ) && ( rxLength != 0 ) && ( DDC2Bi_FIFOMODE_READ_HW_CHKSUM_FLAG(Source)==0 ) )
#else
                if(( rxChkSum == 0x00 && rxIndex>0 ) )
#endif
                {
                    Set_RxBusyFlag();
                    rxStatus = DDC2B_COMPLETED;
#if !D2B_XShared_DDCBuffer
                    Present_DDC2MCU_CUR_ADR &= (D2B_FIFO_Size-1);
#endif
                    rxInputPort = D2B_FIFOMODE_DDCPORT2INPUT(Source);
                    rxComboPort = Source;
                }
                else
                {
                    rxStatus = DDC2B_CLEAR;
                    Clr_RxBusyFlag();
#if D2B_XDATA_DEBUG              
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+48+(IntCount%16)+(IntCount/16)*80] |= 0x40;
#endif                    
                }


                if(DDC2Bi_FIFOMODE_READ_FULL_FLAG(Source)) // Buffer Write Overflow at Race condition
                {
                    D2BErrorFlag=1;
                    DDC2Bi_InitRx();

#if D2B_XDATA_DEBUG
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_START_ADR;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = Present_DDC2MCU_CUR_ADR;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = 0x55;
                    XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+112+(IntCount%16)+(IntCount/16)*80] = msRegs[REG_3EE6];
#endif

                    DDC2Bi_FIFOMODE_CLR_EMPTYFULL_FLAG(Source); // clear
                }
                
                DDC2Bi_FIFOMODE_SET_RW_DONE(Source);
                if( _bit7_( DDC2Bi_Read_INT(Source)) )
                    DDC2Bi_CLR_INT(Source, BIT7);

                break;
                
            // Default
            default:
#if D2B_XDATA_DEBUG
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+3] = 0x44;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+64+(IntCount%16)+(IntCount/16)*80] = 0x44;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+80+(IntCount%16)+(IntCount/16)*80] = 0x44;
                XSRAMBuffer[FIFODBGOFFSET+D2B_FIFO_Size+96+(IntCount%16)+(IntCount/16)*80] = intFlag; 
#endif                
                DDC2Bi_SET_RBUF(Source, DDC2Bi_Read_WBUF(Source));
                txStatus = DDC2B_CLEAR;
                DDC2Bi_InitRx();
                break;

        }
    }

#if D2B_XDATA_DEBUG    
    IntCount++;
    if(rxStatus == DDC2B_COMPLETED)
        IntCountTmp = IntCount;
#endif
}
#else
void drvDoDDCCI( BYTE Source ) // Annie 2006.7.5
{
    BYTE xdata intFlag, rxByte;

    intFlag = DDC2Bi_Read_INT(Source);//读取当前端口的中断状态

    if( intFlag )//如果有中断
    {
        switch( intFlag &( TXBI | RCBI ) )//判断接受还是发送
        {
            case TXBI:      //发送数据，将DDCBuffer中的数据发出（txBufferPtr指向DDCBuffer首地址）
                txStatus = DDC2B_MSGON;                // no characters left
                if( !( txLength ) )//如果发送长度是0
                {
                    // clear the transmit status
                    txStatus = DDC2B_CLEAR;//清楚发送标志

                    DDC2Bi_SET_RBUF(Source, 0);//清空Buffer
                    DDC2Bi_SET_WP_READY(Source);//拉起写保护
                    
                    return ;
                }
                // send out the current byte
                DDC2Bi_SET_RBUF(Source, *txBufferPtr++);//发送当前字节的数据
                txLength--;
                break;
                
            case RCBI://接收数据，将数据存到DDCBuffer中，读取完毕后rxStatus=DDC2B_COMPLETED
                // read the received byte
                rxByte = DDC2Bi_Read_WBUF(Source);//读取接收到的数据

                // depending of the message status
                switch( rxStatus )
                {
                        // in case there is nothing received yet
                    case DDC2B_CLEAR:
                        if( rxByte == DDC2B_SRC_ADDRESS )//判断是否等于源地址0x51
                        {
                            rxStatus++; // = DDC2B_SRCADDRESS=1;
                            rxChkSum = INITRxCK;////校验 DDC2B_SRC_ADDRESS ^ DDC2B_DEST_ADDRESS   0x51^0x6e=3f
                        }
                        else
                        {
                            DDC2Bi_InitRx();////重新初始化rxStatus = DDC2B_CLEAR=0;  rxIndex = 0
                        }
                        break;
                        //第一次进入if,因为接收的第一个数据是目标地址0x6e，所以会走else
                        //第二次进入，收到的数据是0x51，走if更新接收标志的状态
                        //并将两个地址异或，赋值给chksum
                    case DDC2B_SRCADDRESS:
                        // get the length
                        rxLength = rxByte &~DDC2Bi_CONTROL_STATUS_FLAG;//获取接受到字节长度
                        // put the received byte in DDCBuffer
                        DDCBuffer[rxIndex++] = rxByte;//将接受到的字节放入DDCBuffer
                        rxChkSum ^= rxByte;//将接受的数据异或rxChkSum = 0011 111
                        // set the receive body state
                        rxStatus++; // = DDC2B_COMMAND;//更新当前的接收状态
                        //if it is a NULL message
                        if (rxLength == 0)//如果接受长度是0
                        {
                            rxStatus= DDC2B_COMPLETED;    //接收状态完成                        
                            Set_RxBusyFlag();//置起接受忙碌标志位
                        }
                        else if (rxLength >= DDC_BUFFER_LENGTH)//如果接受长度大于等于Buffer长度
                        {
                            DDC2Bi_InitRx();//重新初始化Rx  rxStatus = DDC2B_CLEAR;  rxIndex = 0
                        }
                        break;
                        // get the command
                    case DDC2B_COMMAND:
                        // save the commandbyte
                        rxStatus++; // = DDC2B_RECBODY;
                        // get the message body
                    case DDC2B_RECBODY:
                        DDCBuffer[rxIndex++] = rxByte;//将接受到的字节放入DDCBuffer
                        rxChkSum ^= rxByte;//将接受的数据异或（校验）
                        rxLength--;//接受的字节数减少
                        // the last byte in the message body
                        if( rxLength == 0 )//如果接受长度是0
                        {
                            rxStatus++; // = DDC2B_WAITFORCK;//更新状态
                        }
                        break;
                        // ...here we are waiting for CheckSum...
                    case DDC2B_WAITFORCK:
                        // if CheckSum match
                        if( rxChkSum == rxByte )//将计算出来的chksum和接受到的chksum对比
                        {
                            rxInputPort = D2B_FIFOMODE_DDCPORT2INPUT(Source);//选择输出端口
                            rxComboPort = Source;//端口
                            rxStatus = DDC2B_COMPLETED;//接收状态完成
                            Set_RxBusyFlag();//置起接受忙碌标志位
                        }
                        // elsechecksum error
                        else
                        {
                            // if CheckSum error re-initialize the receive buffer
                            DDC2Bi_InitRx();//重新初始化Rx  rxStatus = DDC2B_CLEAR;  rxIndex = 0
                        }
                        break;
                    default:
                        // clear the rxState and the current buffer for a new message
                        if( !RxBusyFlag )//为新消息清除rxSate和当前缓冲区
                            DDC2Bi_InitRx();
                        break;
                }
                break;

            default:
                DDC2Bi_SET_RBUF(Source, DDC2Bi_Read_WBUF(Source));//将读到的字节发送回去
                txStatus = DDC2B_CLEAR;//清除发送状态
                DDC2Bi_InitRx();//重新初始化Rx  rxStatus = DDC2B_CLEAR;  rxIndex = 0
                break;

        }
    }
}
#endif

