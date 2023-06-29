///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mapi_mhl.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPI_MHL_C_
#define _MAPI_MHL_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "board.h"
#include "types.h"
#include "ms_reg.h"
//#include "DebugMsg.h"
#include "global.h"
#if 1
void MS_MHL_MAPIDummy(void)
{
	BYTE code MS_MHL_MAPIummy[] = {0xFF};
	BYTE i = MS_MHL_MAPIummy[0];
}
#endif



#if ENABLE_MHL
#include "mdrv_mhl.h"
#include "mapi_mhl.h"

BYTE xdata MHLExtenCountFlag = 0; // 120529 coding addition for switching input port

#if ENABLE_MHL_COUNT
WORD xdata MHLActionCount = 0; // unit: 10ms 120718 coding test
#endif
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define MHL_DBG     0

#if MHL_DBG && ENABLE_DEBUG
#define MHL_DPUTSTR(str)        printMsg(str)
#define MHL_DPRINTF(str, x)     printData(str, x)
#else
#define MHL_DPUTSTR(str)
#define MHL_DPRINTF(str, x)
#endif


//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

xdata WORD g_u16MHLHandlerCnt = 0;
bit g_u16MHLHandlerCntFlag = 0;
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if !DMHL_EDID_BYPASS
code BYTE Mstar_MHL_EDID[256] =
{
	#if 0 // 120321 coding test, tpv htc edid test
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x3E, 0x93, 0x29, 0x00, 0x55, 0x31, 0x30, 0x30,
	0x1B, 0x14, 0x01, 0x03, 0x80, 0x3C, 0x22, 0x78, 0xEE, 0x2C, 0xC5, 0xA5, 0x55, 0x54, 0xA1, 0x27,
	0x0C, 0x50, 0x54, 0xA5, 0x4B, 0x00, 0x71, 0x4F, 0x81, 0x80, 0xD1, 0xC0, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
	0x45, 0x00, 0x56, 0x50, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x01, 0xFE, 0x44,
	0x73, 0x10, 0x00, 0x1F, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4F,
	0x54, 0x53, 0x20, 0x32, 0x37, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD,
	0x00, 0x38, 0x4C, 0x1E, 0x53, 0x11, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xF5,
	0x02, 0x03, 0x20, 0xF0, 0x4D, 0x90, 0x05, 0x04, 0x03, 0x02, 0x07, 0x16, 0x01, 0x14, 0x1F, 0x12,
	0x13, 0x22, 0x23, 0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x65, 0x03, 0x0C, 0x00, 0x10, 0x00,
	0x01, 0x1D, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x56, 0x50, 0x21, 0x00,
	0x00, 0x1E, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00, 0x56, 0x50,
	0x21, 0x00, 0x00, 0x9E, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28, 0x55, 0x00,
	0x56, 0x50, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E,
	0x96, 0x00, 0x56, 0x50, 0x21, 0x00, 0x00, 0x18, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40,
	0x58, 0x2C, 0x45, 0x00, 0x56, 0x50, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDE,
	#elif 0
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x36, 0x74, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x18, 0x0F, 0x01, 0x03, 0x80, 0x73, 0x41, 0x78, 0x0A, 0xCF, 0x74, 0xA3, 0x57, 0x4C, 0xB0, 0x23,
	0x09, 0x48, 0x4C, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x20, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28,
	0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20,
	0x58, 0x2C, 0x25, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4D,
	0x53, 0x74, 0x61, 0x72, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x0A, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD,
	0x00, 0x3B, 0x3C, 0x1F, 0x2D, 0x08, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x25,
	0x02, 0x03, 0x1D, 0xF2, 0x4A, 0x05, 0x84, 0x03, 0x02, 0x01, 0x12, 0x93, 0x14, 0x16, 0x07, 0x23,
	0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x65, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x8C, 0x0A, 0xD0,
	0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x8C,
	0x0A, 0xA0, 0x14, 0x51, 0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00,
	0x99, 0x01, 0x1D, 0x00, 0xBC, 0x52, 0xD0, 0x1E, 0x20, 0xB8, 0x28, 0x55, 0x40, 0xC4, 0x8E, 0x21,
	0x00, 0x00, 0x1F, 0x01, 0x1D, 0x80, 0xD0, 0x72, 0x1C, 0x16, 0x20, 0x10, 0x2C, 0x25, 0x80, 0xC4,
	0x8E, 0x21, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68,
	#else // 1080p30

	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x36, 0x74, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x18, 0x0F, 0x01, 0x03, 0x80, 0x73, 0x41, 0x78, 0x0A, 0xCF, 0x74, 0xA3, 0x57, 0x4C, 0xB0, 0x23,
	0x09, 0x48, 0x4C, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x20, 0x01, 0x1D, 0x80, 0x3E, 0x73, 0x38, 0x2D, 0x40, 0x7E, 0x2C,
	0x45, 0x80, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20,
	0x6E, 0x28, 0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4D,
	0x53, 0x74, 0x61, 0x72, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x0A, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFD,
	0x00, 0x3B, 0x3C, 0x1F, 0x2D, 0x08, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x64,
	0x02, 0x03, 0x1F, 0xF2, 0x4C, 0x05, 0x04, 0x03, 0x02, 0x01, 0x12, 0x13, 0x14, 0x16, 0x07, 0xA2,
	0xA0, 0x23, 0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x65, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x8C,
	0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00,
	0x18, 0x8C, 0x0A, 0xA0, 0x14, 0x51, 0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0xC4, 0x8E, 0x21,
	0x00, 0x00, 0x99, 0x01, 0x1D, 0x00, 0xBC, 0x52, 0xD0, 0x1E, 0x20, 0xB8, 0x28, 0x55, 0x40, 0xC4,
	0x8E, 0x21, 0x00, 0x00, 0x1F, 0x01, 0x1D, 0x80, 0xD0, 0x72, 0x1C, 0x16, 0x20, 0x10, 0x2C, 0x25,
	0x80, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
	#endif
};
#endif
//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

BYTE _msapi_mhl_CbusRcpProcess (BYTE rcpCode);
BYTE _msapi_mhl_CbusRapProcess (BYTE rapCode);


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_init()
//  [Description]
//                  MHL init
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mapi_mhl_init(void)
{
	#if DMHL_EDID_BYPASS
	BYTE i;
	if(mdrv_mhl_init(&i) == FALSE)
	#else
	if(mdrv_mhl_init(&Mstar_MHL_EDID) == FALSE)
	#endif
	{
		MHL_DPUTSTR("mapi_mhl_init() FAIL");
		return FALSE;
	}
	MHL_DPUTSTR("mapi_mhl_init() PASS");
	return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  _msapi_mhl_CbusRcpProcess (BYTE rcpCode)
//  [Description]
//                  MHL Cbus process MSC RCP sub-command
//  [Arguments]:
//                  rapCode: RCP sub-command code
//  [Return]:
//
//**************************************************************************
BYTE _msapi_mhl_CbusRcpProcess (BYTE rcpCode)
{
	BYTE statusCode = MSC_RCP_NO_ERROR;
	switch (rcpCode)
	{
			#if 0//DMHL_CTS & ENABLE_DEBUG
		case RCP_KEYID_SELECT:
			VKeyPad = VK_SOURCE;
			break;
		case RCP_KEYID_UP:
			VKeyPad = VK_UP;
			break;
		case RCP_KEYID_DOWN:
			VKeyPad = VK_DOWN;
			break;
		case RCP_KEYID_ROOT_MENU:
			VKeyPad = VK_MENU;
			break;
		case RCP_KEYID_EXIT:
			VKeyPad = VK_MENU;
			break;
			#endif
		default:
			statusCode = MSC_RCP_INEFFECTIVE_KEY_CODE;
			break;
	}
	if(statusCode == MSC_RCP_INEFFECTIVE_KEY_CODE )
	{
		//MHL_DPUTSTR("KeyCode not supported" );
	}
	return (statusCode);
}

//**************************************************************************
//  [Function Name]:
//                  _msapi_mhl_CbusRapProcess (BYTE rapCode)
//  [Description]
//                  MHL Cbus process MSC RAP sub-command
//  [Arguments]:
//                  rapCode: RAP sub-command code
//  [Return]:
//
//**************************************************************************
BYTE _msapi_mhl_CbusRapProcess (BYTE rapCode)
{
	BYTE statusCode  = MSC_RAP_NO_ERROR;
	switch (rapCode)
	{
		case MSC_RAP_POLL:
			break;
		case MSC_RAP_CONTENT_ON:
			mdrv_mhl_SetTMDSTxOnOff(TRUE);
			break;
		case MSC_RAP_CONTENT_OFF:
			mdrv_mhl_SetTMDSTxOnOff(FALSE);
			break;
		default:
			statusCode = MSC_RAP_UNRECOGNIZED_ACTION_CODE;
			break;
	}
	return( statusCode );
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusProcessMSCSubCmd()
//  [Description]
//                  MHL Cbus process MSC sub-command
//  [Arguments]:
//                  subcmd: MSC sub-command
//                  subdata: MSC sub-data
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusProcessMSCSubCmd (BYTE subcmd, BYTE subdata)
{
	BYTE status;
	switch(subcmd)
	{
		case MSC_MSG_RCP:
			status = _msapi_mhl_CbusRcpProcess(subdata);
			mdrv_mhl_CbusRcpReply(status, subdata);
			break;
		case MSC_MSG_RCPK:
		case MSC_MSG_RCPE:
			break;
		case MSC_MSG_RAP:
			#if 0
			// report busy when active standby
			if(MSrv_Control::GetInstance()->IsActiveStanbyMode())
			{
				mdrv_mhl_CbusRcpReply(MSC_RAP_RESPONDER_BUSY);
				break;
			}
			if(gMHLInfo.MhlCbusInfo.request[gMHLInfo.MhlCbusInfo.curIdx].msgData[1] == MSC_RAP_CONTENT_ON)
			{
				//for MHL auto input switch
				if(MSrv_Control::GetInstance()->GetCurrentInputSource() != MAPI_INPUT_SOURCE_HDMI)
				{
					MS_USER_MHL_SETTING stMHLSetting;
					MSrv_Control::GetMSrvSystemDatabase()->GetMHLSetting(&stMHLSetting);
					if(stMHLSetting.AutoInputSwitch != 0) //check auto input enable
					{
						MSrv_Control::GetInstance()->SetInputSource(MAPI_INPUT_SOURCE_HDMI);
					}
					else //report busy when auto input disable
					{
						mdrv_mhl_CbusRcpReply(MSC_RAP_RESPONDER_BUSY );
						break;
					}
				}
			}
			#endif
			status = _msapi_mhl_CbusRapProcess(subdata);
			mdrv_mhl_CbusRapReply(status);
			break;
		case MSC_MSG_RAPK:
			break;
		default: // MSGE
			//MHL_DPUTSTR("Respond with MSC_MSGE");
			break;
	}
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_RxHandler()
//  [Description]
//                  MHL handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_RxHandler(void)
{
	BYTE ucCmd = 0;
	BYTE ucData = 0;
	if(mdrv_mhl_CbusRxHandler(&ucCmd, &ucData))
	{
		mapi_mhl_CbusProcessMSCSubCmd(ucCmd, ucData);
	}
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_TxHandler()
//  [Description]
//                  MHL handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_TxHandler(void)
{
	Bool bindex = FALSE;
	if(mdrv_mhl_CbusStatus())
	{
		if(mdrv_mhl_CbusTxHandler())
		{
			INC_MHL_HANDLER_TIMER();
			bindex = TRUE;
		}
	}
	if(!bindex)
	{
		mdrv_mhl_CDRModeMonitor();
		if(mdrv_mhl_CbusConnectionCheck())
		{
			INC_MHL_HANDLER_TIMER();
		}
	}
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_handler()
//  [Description]
//                  MHL handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_handler(void)
{
	if(mdrv_mhl_CableDetect())
	{
		#if 0
//#if !DMHL_INT_ENABLE
		mdrv_mhl_CbusIntCB();
//#endif // #if !DMHL_INT_ENABLE
		mdrv_mhl_CbusIntHandler();
		mdrv_mhl_CbusHandler();
		#else
		do
		{
			if(GET_MHL_CBUS_CONNECT())
			{
				//#if !DMHL_INT_ENABLE
				mdrv_mhl_CbusIntCB();
				//#endif // #if !DMHL_INT_ENABLE
				mdrv_mhl_CbusIntHandler();
				mapi_mhl_RxHandler();
				if(GET_MHL_CABLE_PLUGGED() && (!GET_MHL_HPD_SET_FLAG()))
				{
					//MHL_DPUTSTR("$$MHL while\r\n");
					SET_MHL_HANDLER_TIMER(2000);    // 2sec
				}
			}
			mapi_mhl_TxHandler();
			if(GET_CBUS_LINK_FINISH())
			{
				if(mdrv_mhl_CheckDEStable())
				{
					//MHL_DPRINTF("$$MHL Handler Cnt = %d\r\n", g_u16MHLHandlerCnt);
					SET_MHL_HANDLER_TIMER(0);
					break;
				}
			}
		}
		while(GET_MHL_CABLE_PLUGGED() && GET_MHL_CBUS_CONNECT() && GET_MHL_HANDLER_TIMER());
		#endif
	}
}

//**************************************************************************
//  [Function Name]:
//                  mapi_mhl_CbusIsolate
//  [Description]
//                  MHL Cbus isolate
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_mhl_CbusIsolate(void)
{
	CLR_MHL_PORT_ON_FLAG();
	mdrv_mhl_CbusIsolate(TRUE);
}

// config HPD in combo(MHL/HDMI) port A
void mapi_mhl_SetHPD(Bool bflag)
{
	mdrv_mhl_SetHPD(bflag);
}

// MHL power control
void mapi_mhl_PowerCtrl(BYTE pctrl)
{
	if(pctrl != gMHLInfo.MhlPowerStatus)
		mdrv_mhl_PowerCtrl(pctrl);
}

#if 0//DMHL_CTS
extern BYTE xdata g_u8MenuPageIndex;
void mapi_mhl_CbusSendRcp (BYTE kcode)
{
	BYTE rcpcode;
	switch(kcode)
	{
			#if 0//ENABLE_DEBUG
		case KEY_TICK:
			if(g_u8MenuPageIndex != MENU_ROOT)
				rcpcode = RCP_KEYID_SELECT;
			else
				rcpcode = RCP_KEYID_RESERVED;
			break;
		case KEY_MENU:
			if(g_u8MenuPageIndex == MENU_ROOT)
				rcpcode = RCP_KEYID_ROOT_MENU;
			else
				rcpcode = RCP_KEYID_EXIT;
			break;
		case KEY_PLUS:
			if(g_u8MenuPageIndex != MENU_ROOT)
				rcpcode = RCP_KEYID_UP;
			else
				rcpcode = RCP_KEYID_RESERVED;
			break;
		case KEY_MINUS:
			if(g_u8MenuPageIndex != MENU_ROOT)
				rcpcode = RCP_KEYID_DOWN;
			else
				rcpcode = RCP_KEYID_RESERVED;
			break;
			#endif
		default:
			rcpcode = RCP_KEYID_RESERVED;
			break;
	}
	if(rcpcode != RCP_KEYID_RESERVED)
		mdrv_mhl_CbusMscMsgSubCmdSend(MSC_MSG_RCP, rcpcode);
}
#endif

#if 1
Bool mapi_mhl_WakeupDetect(void)
{
	return mdrv_mhl_WakeupDetect();
}
#endif

#endif // #if ENABLE_MHL

#endif // _MAPI_MHL_C_

