#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "board.h"
#include "global.h"
#include "debug.h" //change position eshin
#include "keypaddef.h"
#include "menudef.h"
#include "keypad.h"
#include "ms_rwreg.h"
#include "drvosd.h"
#include "msosd.h"
#include "msosdfunction.h"
#include "menufunc.h"
#include "menustr.h"
#include "menutbl.h"
#include "ms_reg.h"
#include "misc.h"
#include "nvram.h"
#include "adjust.h"
#include "userpref.h"
#include "power.h"
#include "msdlc.h"
#include "detect.h"
#include "PropFont.h"
#include "Panel.h"
#include "GPIO_DEF.h"
#include "CommonLoadCPnCompressFont.h"
#include "FactoryString.h"

#if	1//def ReduceDDC
#include "ddc.h"
#endif

#if HotInputSelect
#include "mStar.h"
#endif


#if ((DEBUG_FLASHADDR&&USEFLASH))
#include "msflash.h"
#endif

#if MWEFunction
#include "MsACE.h"
#include "msdlc.h"
#endif

#include "Msflash.h"

extern WORD code tHomeMainMenu_2ColorFont[];
extern BYTE code tBackGroundLT_4ColorFont[];
extern BYTE code tBackGroundTOP02_4ColorFont[];
extern BYTE code tBackGroundTOP03_4ColorFont[];
extern BYTE code tBackGroundTOP06_4ColorFont[];
extern BYTE code tBackGroundTOP09_4ColorFont[];
extern BYTE code tBackGroundTOP10_4ColorFont[];
extern BYTE code tBackGroundTOP13_4ColorFont[];
extern BYTE code tBackGround_LD_4ColorFont[];
extern BYTE code tBackGround_RD_4ColorFont[];
extern BYTE code tbuttom1_4ColorFont[];
extern BYTE code tbuttom2_4ColorFont[];
extern BYTE code tbuttom3_4ColorFont[];
extern BYTE code tBackGround_SXL_4ColorFont[];
extern BYTE code tBackGround_FBL_4ColorFont[];

extern BYTE code PalLT[1][3];
extern BYTE code PalRT[1][3];
extern BYTE code PalLD[3][6];
extern BYTE code PalRD[3][6];

extern BYTE code PalTOP02[1][3];
extern BYTE code PalTOP03[1][3];
extern BYTE code PalTOP06[1][2];
extern BYTE code PalTOP09[1][3];
extern BYTE code PalTOP10[1][3];
extern BYTE code PalTOP13[1][3];

extern BYTE code Palbu1[1][2];
extern BYTE code Palbu2[1][6];
extern BYTE code Palbu3[1][2];
extern BYTE code PalSXL[2][3];
extern BYTE code PalFBL[2][3];

#if Hot_Corss_ColorSelect||Hot_Corss_FY_ColorSelect||Hot_Corss_FND_Select
extern void DynamicLoadHotCorssIcon( BYTE Mode );
#endif


extern void DynamicLoadHotIconFont( void );
void DrawOsdSubMenu( BYTE menupage );

extern void printData(char *str, WORD value);
extern void printMsg(char *str);
extern void msAccOnOff(BYTE on);
#if HotInputSelect
extern Bool CheckSourceKeyStatus(void);
#endif
#if Enable_Gamma
extern void mStar_SetupGamma(BYTE GamaMode);
#endif


#if OsdHelpKeyType ==	 OsdHelpKey_Under ||OsdHelpKeyType ==	 OsdHelpKey_Right
void	UpdataHelyKeyShowInMenu(void);
#endif


extern void DrawNum(BYTE xPos, BYTE yPos, char len, WORD value);		//110316 Modify
#define CurrentMenu     tblMenus[MenuPageIndex]
#define PrevMenuPage        CurrentMenu.PrevPage
#define CurrentMenuItems    CurrentMenu.MenuItems
#define MenuItemCount       CurrentMenu.ItemCount
#define CurrentMenuItem     CurrentMenu.MenuItems[MenuItemIndex]
#define NextMenuPage        CurrentMenuItem.NextPage
#define CurrentMenuItemFunc CurrentMenuItem.KeyFunction
#define KeyEvent        CurrentMenuItem.KeyEvents[KeypadButton]

/*
#define WAIT_V_OUTPUT_BLANKING_START()   { if(!SyncLossState()&&PanelOnFlag){SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)==0)&&bTimeOutCounterFlag);\
                                        SetTimOutConter(30);while(((msReadByte(SC0_E0)&BIT0)!=0)&&bTimeOutCounterFlag);}}//20130227 modify for DC OFF issue
*/
//========================================================================
//========================================================================
//BYTE  MenuPageIndex = 0;
//BYTE  MenuItemIndex = 0;
BYTE xdata PrevMenuItemIndex = 0;
BYTE xdata TurboKeyCounter = 0;
BYTE xdata PrevPage = 0;
BYTE xdata moveX = 50;
BYTE xdata moveY = 50;

//========================================================================
extern  BYTE GetMenuItemIndex(BYTE menuPageIndex);
BYTE GetPrevItem(MenuItemType *menuItem);
BYTE GetNextItem(MenuItemType *menuItem);


Bool ExecuteKeyEvent(MenuItemActionType menuAction);
void DrawOsdMenu(void);
void DrawOsdMenuItem(BYTE drawIndex, MenuItemType *menuItem);
void DrawOsdMenuItemText(BYTE itemIndex, MenuItemType *menuItem);
void DrawOsdMenuItemValue(BYTE itemIndex, DrawValueType *valueItem);
void DrawOsdMenuItemNumber(BYTE itemIndex, DrawNumberType *numberItem);
void DrawOsdMenuItemGuage(BYTE itemIndex, DrawGuageType *guageItem);
void DrawOsdMenuItemRadioGroup(BYTE itemIndex, DrawRadioGroupType *RadioItem);
//Bool DrawTimingInfo(void);
// 2006/11/10 10:0PM by KK move to userpref.c void SaveFactorySetting( BYTE itemIndex );
#if (DisplayLogo!=NoBrand)//130306 Modify
extern void DrawLogo(void);
#endif
void DrawOsdBackGround(void);
Bool DrawTimingInfo(void);

#if 0
extern   Bool SetSR_DEMOSize(BYTE ucSize, WORD DEMO_Hsize);
#endif




#if ENABLE_OVER_SCAN
extern void DynamicLoadFont_RatioStatus(void);
#endif


//=========================================================================
void Menu_InitVariable(void)
{
	MenuPageIndex = RootMenu;
	MenuItemIndex = 0;
	OsdCounter = 0;
	HotKeyCounter = 0;
	#if 0
	HotKeyMinusCounter = 0;
	#endif
	#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
	HotKeyPlusCounter = 0;
	#endif
	if (!PowerOnFlag)
	{
		MenuPageIndex = PowerOffMenu;
	}
}

void Menu_InitAction(void)
{
	#if DisplayPowerOnLogo
	if(UserPrefLogoON == 0)	//120420 Modify
	{
		Clr_DisplayLogoFlag();
	}
	#endif
	MenuItemIndex = 0;
	#if DisplayPowerOnLogo
	if (DisplayLogoFlag)
	{
		#if MWEFunction //nick add for U type IC can't turn off MEW function
		#if (CHIP_ID==CHIP_TSUMU)
		msAccSetup( 0, 0, 0, 0 );
		#endif
		#endif
		if (MenuPageIndex == LogoMenu)
		{
			return ;
		}
		MenuPageIndex = LogoMenu;
		#if Enable_Rotate180Func
		mStar_SetupPath();
		mStar_SetupFreeRunMode();
		#endif
	}
	else
	#endif
	{
		if (UnsupportedModeFlag)
		{
			MenuPageIndex = UnsupportedModeMenu;
			moveX = 50;	//111223 Modify
			moveY = 50;	//111223 Modify
		}
		else if (SyncLossState())
		{
			if (CableNotConnectedFlag)
			{
				if (DoBurninModeFlag)
				{
					#if FactoryLedFlicker_Enable
					#else
					Power_TurnOnAmberLed();
					#endif
					MenuPageIndex = BurninMenu;
				}
				else
				{
					#if Dual
					if ((UserPrefInputSelectType != INPUT_PRIORITY_AUTO) )
					{
						MenuPageIndex = InputInfoMenu;
						ExecuteKeyEvent(MIA_RedrawMenu);
						Delay1ms(2000);
						Osd_Hide();
						Delay1ms(50);
					}
					MenuPageIndex = StandbyMenu;
					#else
					#if INPUT_TYPE==INPUT_1A   //071225 for Cable not connectd if analog only
					MenuPageIndex = CableNotConnectedMenu;//
					OsdCounter = 60;
					moveX = UserPrefOsdHStart;
					moveY = UserPrefOsdVStart;
					#else
					MenuPageIndex = StandbyMenu; //CableNotConnectedMenu;//later will check if cancel CableNotConnectedMenu or not
					#endif
					#endif
				}
			}
			else
			{
				#if Dual
				if ((UserPrefInputSelectType != INPUT_PRIORITY_AUTO) )
				{
					MenuPageIndex = InputInfoMenu;
					ExecuteKeyEvent(MIA_RedrawMenu);
					Delay1ms(2000);
					Osd_Hide();
					Delay1ms(50);
				}
				#endif
				#if ENABLE_DEBUG
				printMsg("55555555555555");
				#endif
				MenuPageIndex = StandbyMenu;
			}
		}
		//  else if (UnsupportedModeFlag)
		//      MenuPageIndex=UnsupportedModeMenu;
		/******For PE Request*********
		else if (FactoryModeFlag)
		{
		    MenuPageIndex = AutoColorMenu;
		}
		****************************/
		#if ((ModelName==JRY_L58VHN_GV3)||(ModelName==JRY_L58CDT9_GV3)||(ModelName==JRY_L58CDT9_EV1)||(ModelName==JRY_L58CDT9_PV1))
		else if (UserPrefAutoTimes == 0 && SrcInputType < Input_Digital)
		#else
		else if (UserPrefAutoTimes == 0 && SrcInputType < Input_Digital && (!FactoryModeFlag))
		#endif
		{
			MenuPageIndex = AutoMenu;
		}
		else
		{
			if (ShowInputInfoFlag)//)//071226
			{
				Clr_ShowInputInfoFlag();
				{
					MenuPageIndex = InputInfoMenu;
					OsdCounter = 3;
				}
			}
			else
				MenuPageIndex = RootMenu;
		}
	}
	//OsdCounter = 0; // 071221
	if (SrcInputType != UserPrefInputType && !SyncLossState())
	{
		#if !USEFLASH
		NVRam_WriteByte(nvrMonitorAddr(InputType), SrcInputType);
		#else
		UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
		#endif
		UserPrefInputType = SrcInputType;
	}
	if(InputTimingChangeFlag)	//110311 Modify
	{
		#if DisplayPowerOnLogo
		if(!DisplayLogoFlag)
		#endif
		{
			MenuPageIndex = RootMenu;
			OsdCounter = 0;
			Clr_OsdTimeoutFlag();
			return;
		}
	}
	#if 0//DEBUG_HOTSWITCH
	printData("Menu_InitActionB4:%d", MenuPageIndex);
	#endif
	ExecuteKeyEvent(MIA_RedrawMenu);
	#if 0//DEBUG_HOTSWITCH
	printData("Menu_InitActionB4:%d", MenuPageIndex);
	#endif
	if (UnsupportedModeFlag)
	{
		if (!FreeRunModeFlag && SrcInputType < Input_Digital)
		{
			if (UserPrefAutoTimes == 0)
			{
				AutoConfig();
			}
		}
	}
}

BYTE MenuActionProcess(BYTE value)
{
	BYTE xdata menuAction = value;
// power and menu use same key,so the action must check again!
	if(PowerKeyFlag && PowerOnFlag)
	{
		if(PowerOffFlag) //set flag while 3 sec
		{
			menuAction = MIA_Power;
		}
		else // less 3 sec
		{
			if(MainOSDFlag) // show osd menu while release key
			{
				if (MenuPageIndex < RootMenu || MenuPageIndex == LogoMenu)
				{
					menuAction = MIA_Nothing;
				}
				else
				{
					menuAction = MIA_GotoNext;
				}
				Clr_MainOSDFlag();
				Clr_PowerKeyFlag();
				Clr_DoKeyCountFlag();
			}
			else
				menuAction = MIA_Nothing;
		}
	}
	#if DISABLE_VGA_OR_DVI_OSD_HotKeyVolume && ENABLE_OSD_HotKeyVolume
	if( MenuPageIndex == RootMenu )
	{
		if( (CURRENT_INPUT_IS_VGA() || CURRENT_INPUT_IS_DVI()) && menuAction == MIA_VOL )
		{
			menuAction = MIA_Expansion;
		}
	}
	#endif
	if (menuAction)
	{
		if (!InputTimingStableFlag)
			// prevent osd action while mode changing
		{
			if (menuAction != MIA_Power)
			{
				menuAction = MIA_Nothing;
			}
		}
		#if DEBUG_HOTSWITCH
		printData("MenuActionProcessB4:%d", MenuPageIndex);
		#endif
		if (ExecuteKeyEvent(menuAction))
		{
			#if DEBUG_HOTSWITCH
			printData("MenuActionProcess:%d", MenuPageIndex);
			#endif
			if (MenuPageIndex > RootMenu)
			{
				ResetOsdTimer();
			}
			Clr_OsdTimeoutFlag();
		}
		if (menuAction == MIA_IncValue || menuAction == MIA_DecValue || menuAction == MIA_Auto)
		{
			if (TurboKeyCounter < 100)
			{
				TurboKeyCounter++;
			}
		}
		#if ECO
		else if ((menuAction == MIA_Exit) || (menuAction == MIA_GotoECO))
		#else
		else if (menuAction == MIA_Exit)
		#endif
		{
			Delay1ms(150);
			KeypadButton = BTN_Repeat;
		}
	}
	else
	{
		TurboKeyCounter = 0;
	}
	return menuAction;
}


void Menu_OsdHandler(void)
{
	BYTE xdata menuAction;
	if( !TPDebunceCounter )
	{
		TPDebunceCounter = SKPollingInterval;
		Key_ScanKeypad();
		#if DEBUG_VIRTUAL_KEY
		if(KeyDebug == KEY_EXIT)
			KeypadButton = BTN_Exit;
		else if(KeyDebug == KEY_MINUS)
			KeypadButton = BTN_Minus;
		else if(KeyDebug == KEY_MENU)
			KeypadButton = BTN_Menu;
		else if(KeyDebug == KEY_PLUS)
			KeypadButton = BTN_Plus;
		else if(KeyDebug == KEY_POWER)
			KeypadButton = BTN_Power;
		#endif
		#if Enable_ButtonKeyLongPressFunction
		#if Enable_Exit_LongPressKeyFunction
		if (KeypadButton == BTN_ExitPressKey)
		{
			menuAction = MIA_Auto;
		}
		else
		#endif
		#endif
			if (KeypadButton >= BTN_EndBTN)
			{
				menuAction = MIA_Nothing;
			}
			else if (CurrentMenuItem.KeyEvents)
			{
				menuAction = *((CurrentMenuItem.KeyEvents) + KeypadButton);
			}
		#if DEBUG_VIRTUAL_KEY
		KeyDebug = KEY_NOTHING;
		KeypadButton = k;
		#endif
		menuAction = MenuActionProcess(menuAction);
	}
	#ifdef OffPower
	if((!PowerSavingFlag) && ShowOffPowerWarningFlag)
	{
		ShowOffPowerWarningFlag = 0;
		MenuPageIndex = OffPowerWarningMenu;
		MenuItemIndex = 0;
		ExecuteKeyEvent( MIA_RedrawMenu );
		OsdCounter = 10;
		Clr_OsdTimeoutFlag();
	}
	#endif
	if (OsdTimeoutFlag)
	{
		#if DEBUG_HOTSWITCH
		printData("OsdTimeoutFlag:%d", MenuPageIndex);
		#endif
		//   if (CurrentMenuItemFunc.ExecFunction)
		// CurrentMenuItemFunc.ExecFunction();
		if (SaveSettingFlag)//To Save The Monitor Setting When OSD Time Out
		{
			Clr_SaveSettingFlag();
			SaveUserPref();
		}
		Clr_OsdTimeoutFlag();
		if (DisplayLogoFlag)
		{
			Clr_DisplayLogoFlag();
			Power_TurnOffPanel();
			drvOSD_FrameColorEnable(FALSE);
			LoadCommonFont();
		}
		if( BackToUnsupportFlag && UnsupportedModeFlag)	//111223 Modify
		{
			MenuPageIndex = UnsupportedModeMenu;
			moveX = 50;
			moveY = 50;
			Osd_Hide();
			Clr_BackToUnsupportFlag();
			Clr_BackToStandbyFlag();
		}
		else if( BackToStandbyFlag )	//111223 Modify
		{
			#if DEBUG_HOTSWITCH
			printData("BackToStandbyFlag:%d", MenuPageIndex);
//				printData("HotInputSelectMenu:%d", MessageAndroidOnMenu);
			#endif
#message "OSD Hide and do its function disable"
			#if 0//HotInputSelect	//111223 Modify
			if (MenuPageIndex == HotInputSelectMenu)	//120413 Modify
			{
				#if ENABLE_VGA_INPUT
				if ((MenuItemIndex == INPUT_PRIORITY_VGA) && (SrcInputType != Input_VGA))
				{
					ChangeSourceToAnalog();
					MenuPageIndex = RootMenu;
				}
				else
				#endif
				#if ENABLE_DVI_INPUT
					if ((MenuItemIndex == INPUT_PRIORITY_DVI) && (SrcInputType != Input_Digital))
					{
						ChangeSourceToDigital();
						MenuPageIndex = RootMenu;
					}
					else
				#endif
					#if ENABLE_HDMI_INPUT
						if ((MenuItemIndex == INPUT_PRIORITY_HDMI) && (SrcInputType != Input_Digital))
						{
							ChangeSourceToHDMI();
							MenuPageIndex = RootMenu;
						}
						else
						#if ENABLE_HDMI2ND_INPUT
							if ((MenuItemIndex == INPUT_PRIORITY_HDMI2ND) && (SrcInputType != Input_Digital))
							{
								ChangeSourceToHDMI();
								MenuPageIndex = RootMenu;
							}
							else
						#endif
					#endif
							#if ENABLE_DP_INPUT
								if ((MenuItemIndex == INPUT_PRIORITY_DP) && (SrcInputType != Input_Displayport))
								{
									ChangeSourceToDP();
									MenuPageIndex = RootMenu;
								}
								else
							#endif
									MenuPageIndex = StandbyMenu;
			}
			else
			#endif
			{
				MenuPageIndex = StandbyMenu;
			}
			Osd_Hide(); //110224 for OSD garbage
			Clr_BackToStandbyFlag();
		}
#message "OSD Hide and do its function disable"
		#if 0// HotInputSelect	//111223 Modify
		else if (MenuPageIndex == HotInputSelectMenu)
		{
			#if ENABLE_VGA_INPUT
			if ((MenuItemIndex == INPUT_PRIORITY_VGA) && (SrcInputType != Input_VGA))
			{
				ChangeSourceToAnalog();
			}
			else
			#endif
			#if ENABLE_DVI_INPUT
				if ((MenuItemIndex == INPUT_PRIORITY_DVI) && (SrcInputType != Input_Digital))
				{
					ChangeSourceToDigital();
				}
				else
			#endif
				#if ENABLE_HDMI_INPUT
					if ((MenuItemIndex == INPUT_PRIORITY_HDMI) && (SrcInputType != Input_Digital))
					{
						ChangeSourceToHDMI();
					}
					else
					#if ENABLE_HDMI2ND_INPUT
						if ((MenuItemIndex == INPUT_PRIORITY_HDMI2ND) && (SrcInputType != Input_Digital))
						{
							ChangeSourceToHDMI();
						}
						else
					#endif
				#endif
						#if ENABLE_DP_INPUT
							if ((MenuItemIndex == INPUT_PRIORITY_DP) && (SrcInputType != Input_Displayport))
							{
								ChangeSourceToDP();
							}
							else
						#endif
								Delay1ms(10);
			MenuPageIndex = RootMenu;
		}
		#endif
		#if INPUT_TYPE==INPUT_1A    //071225 show "no sync" after show "CableNotConnected"
		else if((MenuPageIndex == CableNotConnectedMenu) && SyncLossState() && !InputTimingChangeFlag && InputTimingStableFlag)
		{
			Osd_Hide();
			Delay1ms(200);
			MenuPageIndex = StandbyMenu;
			ExecuteKeyEvent(MIA_RedrawMenu);
		}
		#endif
#message "OSD Hide and do its function disable"
		#if 0//(INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)		//120322 Modify
		#if ENABLE_AutoDetech
		else if (MenuPageIndex == InputSelectMenu)
		{
			if (MenuItemIndex == 0)
				SetInputToAuto();
			#if  INPUT_TYPE == INPUT_2H||INPUT_TYPE == INPUT_1D1H1DP
			else if (MenuItemIndex == 1)
				SetInputToDigital();
			#else
			else if (MenuItemIndex == 1)
				SetInputToAnalog();
			#endif
			#if INPUT_TYPE == INPUT_1A1D||INPUT_TYPE == INPUT_1A2D|| INPUT_TYPE == INPUT_1A2H1DP||INPUT_TYPE == INPUT_1A1D1H||INPUT_TYPE == INPUT_1A1D1DP ||INPUT_TYPE == INPUT_1A1H1DP ||INPUT_TYPE == INPUT_1A1D1H1DP	//131113 fay
			else if (MenuItemIndex == 2)
				SetInputToDigital();
			#endif
			#if ENABLE_HDMI
			#if INPUT_TYPE == INPUT_1A1H||INPUT_TYPE == INPUT_1D1H1DP
			else if (MenuItemIndex == 2)
				SetInputToHDMI();
			#elif INPUT_TYPE == INPUT_1A2D||INPUT_TYPE == INPUT_1A1D1H	//131113 fay
			else if (MenuItemIndex == 3)
				SetInputToHDMI();
			#elif (INPUT_TYPE == INPUT_1A1D1H1DP||INPUT_TYPE == INPUT_1A2H1DP)
			else if (MenuItemIndex == 3)
				SetInputToHDMI();
			#elif INPUT_TYPE == INPUT_2H
			else if (MenuItemIndex == 2)
				SetInputToHDMI();
			#endif
			#endif
			#if ENABLE_DP_INPUT
			#if (INPUT_TYPE == INPUT_1A1D1H1DP||INPUT_TYPE == INPUT_1A2H1DP)
			else if (MenuItemIndex == 4)
				SetInputToDP();
			#elif INPUT_TYPE == INPUT_1A1D1DP	//130924 xiandi
			else if (MenuItemIndex == 3)
				SetInputToDP();
			#elif INPUT_TYPE == INPUT_1A1H1DP||INPUT_TYPE == INPUT_1D1H1DP	//130924 xiandi
			else if (MenuItemIndex == 3)
				SetInputToDP();
			#elif INPUT_TYPE == INPUT_1A1DP	//20151126 alpha
			else if (MenuItemIndex == 2)
				SetInputToDP();
			#endif
			#endif
			MenuPageIndex = RootMenu;
		}
		#endif
		#endif
		else if (MenuPageIndex > RootMenu)
		{
			MenuPageIndex = RootMenu;
		}
		MenuItemIndex = 0;
		ExecuteKeyEvent(MIA_RedrawMenu);
	}
	if (!DisplayLogoFlag)
		// 2006/10/18 9:17PM by Emily for AC on but do burnin
	{
		if (DoBurninModeFlag && ChangePatternFlag)
			// for burnin mode
		{
			Clr_ChangePatternFlag();
			PatternNo = (PatternNo + 1) % 5;
			mStar_AdjustBackgoundColor(PatternNo);
		}
	}
	if (ms500Flag)
		// for moving osd position
	{
		Clr_ms500Flag();
		if (CurrentMenu.Flags & mpbMoving && !PowerSavingFlag)
			// && FreeRunModeFlag) // for led flash
		{
			if (ReverseXFlag)
			{
				if (moveX == 0)
				{
					Clr_ReverseXFlag();
				}
				else if(moveX < 0)
				{
					moveX = 0;
				}
				else if(moveX > 100)
				{
					moveX = 100;
				}
				else
				{
					moveX -= 1;
				}
			}
			else
			{
				moveX++;
			}
			if (moveX >= 100)
			{
				Set_ReverseXFlag();
			}
			if (ReverseYFlag)
			{
				if (moveY == 0)
				{
					Clr_ReverseYFlag();
				}
				else if(moveY < 0)
				{
					moveY = 0;
				}
				else if(moveY > 100)
				{
					moveY = 100;
				}
				else
				{
					moveY -= 2;
				}
			}
			else
			{
				moveY += 2;
			}
			if (moveY >= 100)
			{
				Set_ReverseYFlag();
			}
			//printData("--->osd X:%d",moveX);
			//printData("--->osd Y:%d",moveY);
			Osd_SetPosition(moveX, moveY);
		}
	}
	#if F_ShowVsync_Enable
	if (MenuPageIndex == FactoryMenu && FreeSyncFlag)
	{
		Clr_FreeSyncFlag();
		Osd_Set256TextColor( CP_WhiteColor << 4 | CP_BlueColor, Color_2);
		DrawNum ( 17, 25, 3, GetVsyncValue());
	}
	#endif
	#if ColorTool_Clear_Time
	if (PowerOnFlag)
	{
		if(DDCCIAutoColorFlag)
		{
			#if ((ModelName==JRY_L58VHN_GV3)||(ModelName==JRY_L58CDT9_GV3)||(ModelName==JRY_L58CDT9_EV1)||(ModelName==JRY_L58CDT9_PV1))
			Set_FactoryModeFlag();
			MenuPageIndex = FactoryMenu;
			MenuItemIndex = 0;
			DrawOsdMenu();
			Clr_DDCCIAutoColorFlag();
			AutoColor();
			Delay1ms(2000);
			Clr_FactoryModeFlag();
			menuAction = MIA_RedrawMenu;
			MenuPageIndex = RootMenu;
			MenuItemIndex = 0;
			Osd_Hide();
			#else
			Clr_DDCCIAutoColorFlag();
			AutoColor();
			#endif
		}
		if(DDCCResetTimeFlag)
		{
			//if(DisplayLogoFlag) return;
			Clr_DDCCResetTimeFlag();
			Clr_FactoryModeFlag();
			Clr_DoBurninModeFlag();
			ResetAllSetting();
			#if Show_BackLightTimeValue
			BlacklitTime_S = 0;
			BlacklitTime_M = 0;
			BlacklitTime_H = 0;
			MonitorBackLightTime_S = BlacklitTime_S;
			MonitorBackLightTime_M = BlacklitTime_M;
			MonitorBackLightTime_H = BlacklitTime_H;
			SaveMonitorSetting2();
			#endif
			PowerOffSystem();
		}
	}
	#endif
}




Bool ExecuteKeyEvent(MenuItemActionType menuAction)
{
	Bool processEvent = TRUE;
	BYTE xdata tempValue;
	while (processEvent)
	{
		processEvent = FALSE;
		switch (menuAction)
		{
			case MIA_IncValue:
			case MIA_DecValue:
				if (CurrentMenuItemFunc.AdjustFunction)
				{
					if((TurboKeyCounter > 0) && !(CurrentMenuItem.DisplayValue.DrawNumber) //071225 adjust value once if not release key
					        && !(CurrentMenuItem.DisplayValue.DrawGuage))
					{
						Delay1ms(100);
						break;
					}
					#if  HotKey_ECO_DCR
					if (MenuPageIndex == HotKeyECOMenu && UserPrefECOMode == (ECO_Nums - 1) && menuAction == MIA_IncValue
					        || MenuPageIndex == HotKeyECOMenu && UserPrefECOMode == ECO_Standard && menuAction == MIA_DecValue)
					{
						UserPrefDcrMode = FALSE;
						MenuPageIndex = HotKeyDCRMenu;
						MenuItemIndex = 0;
					}
					else if(MenuPageIndex == HotKeyDCRMenu && menuAction == MIA_IncValue)
					{
						UserPrefECOMode = (ECO_Nums - 1);
						MenuPageIndex = HotKeyECOMenu;
						MenuItemIndex = 0;
					}
					else if(MenuPageIndex == HotKeyDCRMenu && menuAction == MIA_DecValue)
					{
						UserPrefECOMode = ECO_Standard;
						MenuPageIndex = HotKeyECOMenu;
						MenuItemIndex = 0;
					}
					#endif
					if (CurrentMenuItemFunc.AdjustFunction(menuAction))
					{
						if(CurrentMenu.Flags & mpbClrGroup)
						{
							// clear status Text
							Osd_Set256TextColor( CPC_Background << 4 | CPC_Background, Color_2);
							//Osd_DrawContinuesChar(CurrentMenuItem.XPos + CENTER_ALIGN_STARTPOS + 1, CurrentMenuItem.YPos, SpaceFont, 11);
						}
						if( MenuPageIndex == ECOMenu
						        || MenuPageIndex == DCRMenu )
						{
							Osd_Set256TextColor( BLACK_COLOR, Color_2);
							Osd_DrawContinuesChar(SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + BriContrast_ECO_ITEM * IconShift ), SpaceFont, 15);
							Osd_DrawContinuesChar(GaugeXPosition, ( SUB_TEXT_YPOS + BriContrast_ECO_ITEM * IconShift ), SpaceFont, 15);
							Osd_DrawContinuesChar(SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + BriContrast_DCR_ITEM * IconShift ), SpaceFont, 15);
							Osd_DrawContinuesChar(GaugeXPosition, ( SUB_TEXT_YPOS + BriContrast_DCR_ITEM * IconShift ), SpaceFont, 15);
							DrawOsdSubMenu( OSD_BriContrastMenu );
						}
						#if LowBlueLightType == LowBlueLight_SharpFunc
						else if( MenuPageIndex == ColorTempMenu )
						{
							if(UserPrefColorTemp != CTEMP_LowBlue)
							{
								gTempLowBlueMode = LOW_BLUE_LIGHT_OFF;
								Osd_DrawContinuesChar(CurrentMenuItem.XPos + CENTER_ALIGN_STARTPOS + 1, 12, SpaceFont, 11);
							}
							DrawOsdSubMenu( RGBColorMenu );
						}
						else if( MenuPageIndex == LowBlueLightMenu )
						{
							DrawOsdSubMenu( RGBColorMenu );
						}
						#else
						else if( MenuPageIndex == ColorTempMenu
					         #if ( LowBlueLightType==LowBlueLight_ColorTemp)
						         || MenuPageIndex == LowBlueLightMenu
					         #endif
						       )
						{
							DrawOsdSubMenu( RGBColorMenu );
						}
						#endif
						#if AdjustLanguageFunction
						else if( MenuPageIndex == LanguageMenu )
						{
							//重画空格---空格作用：覆盖前面的内容---可以通过调整坐标位置或者空格的长度，来解决切换语言时出现覆盖不到位的问题--------------					√
							Osd_Set256TextColor( F_BLACK_B_BLACK, Color_2);
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_LANGUAGE_ITEM * IconShift ), SpaceFont, 15 );	
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_HPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_VPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_TIMEOUT_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_TRANSPARENCE_ITEM * IconShift ), SpaceFont, 15 );

							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_LANGUAGE_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_HPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_VPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_TIMEOUT_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_TRANSPARENCE_ITEM * IconShift ), SpaceFont, 15 );
							//重画二级菜单------------------------------						√
							DrawOsdSubMenu( LanguageMenu );
							DrawOsdSubMenu( OsdMenu );
							LoadLanguageStatusPropfont();
							MenuPageIndex = LanguageMenu;
							MenuItemIndex = 0 ;
						}
						else if( MenuPageIndex == OsdHPositionMenu )
						{
							Osd_Set256TextColor( BLACK_COLOR, Color_2);
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_HPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_HPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							DrawOsdSubMenu( OsdHPositionMenu );
							LoadLanguageStatusPropfont();
							MenuPageIndex = OsdHPositionMenu;
							MenuItemIndex = 0 ;
						}
						else if( MenuPageIndex == OsdVPositionMenu )
						{
							Osd_Set256TextColor( BLACK_COLOR, Color_2);
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_VPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_VPOSITION_ITEM * IconShift ), SpaceFont, 15 );
							DrawOsdSubMenu( OsdVPositionMenu );
							LoadLanguageStatusPropfont();
							MenuPageIndex = OsdVPositionMenu;
							MenuItemIndex = 0 ;
						}
						else if( MenuPageIndex == OsdTimeOutMenu )
						{
							Osd_Set256TextColor( BLACK_COLOR, Color_2);
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_TIMEOUT_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_TIMEOUT_ITEM * IconShift ), SpaceFont, 15 );
							DrawOsdSubMenu( OsdTimeOutMenu );
							LoadLanguageStatusPropfont();
							MenuPageIndex = OsdTimeOutMenu;
							MenuItemIndex = 0 ;
						}
						else if( MenuPageIndex == TransparenceMenu )
						{
							Osd_Set256TextColor( BLACK_COLOR, Color_2);
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, ( SUB_TEXT_YPOS + OSD_TRANSPARENCE_ITEM * IconShift ), SpaceFont, 15 );
							Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_TRANSPARENCE_ITEM * IconShift ), SpaceFont, 15 );
							DrawOsdSubMenu( TransparenceMenu );
							LoadLanguageStatusPropfont();
							MenuPageIndex = TransparenceMenu;
							MenuItemIndex = 0 ;
						}
						#endif
						#if (LowBlueLightType==LowBlueLight_Misc_Guage)||(LowBlueLightType==LowBlueLight_Misc_Group)
						if (MenuPageIndex == LowBlueLightMenu)
						{
							Osd_Set256TextColor(F_BLACK_B_BLACK, Color_2);
							Osd_DrawContinuesChar( GaugeXPosition+1, ( SUB_TEXT_YPOS + Misc_LowBlueLigth_Item * IconShift ), MonoSpace, 11);
							//MenuPageIndex == OSD_MiscMenu;
							
						}
						#endif
						#if FreeSyncMenu_Enable
						else if(MenuPageIndex == FreeSyncMenu)
						{
							processEvent = TRUE;
							menuAction = MIA_Exit;
						}
						#endif
						if ( MenuPageIndex == HotKeyECOMenu
					        #if Hotkey_DCR_Enable
						        || MenuPageIndex == HotKeyDCRMenu
					        #endif
					        #if HotExpansionAdjust
						        || MenuPageIndex == HotExpansionMenu
					        #endif
						   )
						{
							mStar_WaitForDataBlanking();
							DynamicLoadHotIconFont();
							#if ENABLE_OVER_SCAN&& AudioFunc
							if (MenuPageIndex == HotExpansionMenu)
							{
								DrawOsdMenuItemText(MenuItemIndex, &CurrentMenuItems[MenuItemIndex]);
							}
							#endif
							#if Hotkey_ECO_Text_Enable
							if (MenuPageIndex == HotKeyECOMenu)
							{
								//DrawOsdMenuItemText(MenuItemIndex, &CurrentMenuItems[MenuItemIndex]);
								Osd_DrawContinuesChar( 8, 3, SpaceFont, 8);
								DrawOsdMenuItemValue( MenuItemIndex, &CurrentMenuItem.DisplayValue );
							}
							#endif
						}
						#if AudioFunc
						if((MenuPageIndex == VolumeMenu) && (CurrentMenuItemFunc.AdjustFunction == AdjustVolume))
						{
							DrawOsdSubMenu( MuteMenu );
						}
						#endif
						#if AudioFunc && ENABLE_OSD_HotKeyVolume
						if(MenuPageIndex == HotKeyVolMenu)
							Osd_Set256TextColor( CP_UnselectItem, Color_2 );
						else
						#endif
						#if Hotkey_BriCon_Enable
							if(MenuPageIndex == HotKeyBriMenu || MenuPageIndex == HotKeyConMenu)
								Osd_Set256TextColor( CP_UnselectItem, Color_2 );
							else
						#endif
							#if Hotkey_Bri_Enable
								if(MenuPageIndex == HotKeyBriMenu)
									Osd_Set256TextColor( CP_UnselectItem, Color_2 );
								else
							#endif
								#if Hotkey_Con_Enable
									if(MenuPageIndex == HotKeyConMenu)
										Osd_Set256TextColor( CP_UnselectItem, Color_2 );
									else
								#endif
										if(MenuPageIndex == FactoryMenu)
											Osd_SetTextMonoColor( DRAK_RED_COLOR, BLACK_RED_COLOR );
										else
											Osd_Set256TextColor( F_DRAKRED_B_BLACKRED, Color_2 );
						DrawOsdMenuItemText(MenuItemIndex, &CurrentMenuItems[MenuItemIndex]);
						DrawOsdMenuItemValue( MenuItemIndex, &CurrentMenuItem.DisplayValue );
						Set_SaveSettingFlag();
						if (TurboKeyCounter < 7)
						{
							Delay1ms(200);
						}
					}
				}
				break;
			case MIA_NextItem:
			case MIA_PrevItem:
				PrevMenuItemIndex = MenuItemIndex;
				tempValue = MenuItemIndex;
				if (menuAction == MIA_NextItem)
				{
					MenuItemIndex = GetNextItem(CurrentMenuItems);
				}
				else if(menuAction == MIA_PrevItem)
				{
					MenuItemIndex = GetPrevItem(CurrentMenuItems);
				}
				#if DEBUG_PRINTDATA
				printData("MenuItem Index %d", MenuItemIndex);
				#endif
				if (tempValue != MenuItemIndex)
				{
					#if 1
					BYTE xdata TempIndex = 0;	//111223 Modify
					#endif
					/*if( MenuPageIndex == MainMenu )
					{
						Osd_SetTextMonoColor(0x00, 0x06);
						Osd_DrawContinuesChar( 6, 1, SpaceFont, 0x20);
						Osd_SetTextMonoColor(0x00, 0x07);
						for(tempValue = SUB_TEXT_YPOS; tempValue < 0x0F; tempValue += 2)
						{
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, tempValue, SpaceFont, 0x27 - SUB_TEXT_XPOS);
						}
						tempValue = PrevMenuItemIndex;
					}*/
					#if Hot_Corss_FY_ColorSelect
					if(MenuPageIndex == HotCorssMenu)
					{
						Osd_Hide();
						Delay1ms(100);
						DynamicLoadHotCorssIcon(MenuItemIndex / 2);
					}
					#elif Hot_Corss_FND_Select
					if(MenuPageIndex == HotCorssMenu)
					{
						Osd_Hide();
						Delay1ms(100);
						DynamicLoadHotCorssIcon(MenuItemIndex);
					}
					#endif
					if (CurrentMenuItem.Fonts)
					{
						DynamicLoadFont(CurrentMenuItem.Fonts);
					}
					#if WaitForDataBlanking
					mStar_WaitForDataBlanking();
					#endif
					DrawOsdMenuItem(tempValue, &CurrentMenuItems[tempValue]);
					#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
					if (MenuPageIndex == InputSelectMenu)
					{
						// clear status Text
						Osd_Set256TextColor( F_BLACK_B_BLACK, Color_2);
						Osd_DrawContinuesChar( GaugeXPosition, ( SUB_TEXT_YPOS + OSD_LANGUAGE_ITEM * IconShift ), MonoSpace, 11);
					}
					
					#endif
					DrawOsdMenuItem(MenuItemIndex, &CurrentMenuItem);
					//if( MenuPageIndex == MainMenu )
					//{
						//DrawOsdSubMenu( NextMenuPage );		//二级菜单
						//if( MenuItemIndex == MAIN_Misc_ITEM)
							//DrawTimingInfo();		//分辨率
					//}
					#if Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
					if(MenuPageIndex == HotCorssMenu)
					{
						Osd_Show();               
					}
					#endif
					if (MenuPageIndex == FactoryMenu)
					{
						if ((MenuItemIndex == Item_9300R && tempValue < Item_Rever) || (MenuItemIndex == Item_9300B && tempValue > Item_adj9300B))
						{
							SetFactoryColorTempCool1();
						}
						else if ((MenuItemIndex == Item_6500R && tempValue < Item_6500R) || (MenuItemIndex == Item_6500B && tempValue > Item_adj6500B))
						{
							SetFactoryColorTempWarm1();
						}
						#if CT_7500K_ENABLE
						else if ((MenuItemIndex == Item_7500R && tempValue < Item_7500R) || (MenuItemIndex == Item_7500B && tempValue > Item_adj7500B))
						{
							SetFactoryColorTempNormal();
						}
						#endif
						#if CT_sRGB_ENABLE
						else if ((MenuItemIndex == 31 && tempValue < 31) || (MenuItemIndex == 35 && tempValue > 36))
						{
							SetFactoryColorTempSRGB();
						}
						#endif
						#if 1 //2006-08-03 Andy Due To Color Setting Not Complete
						if (SaveSettingFlag)
						{
							//121108 Modify
							SaveFactorySetting();//UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
							if ((tempValue >= 53 + Enable_ProductModeAdjust * 2 + ENABLE_FACTORY_SSCADJ * 5 + (PanelminiLVDS || PANEL_VCOM_ADJUST) * 2) && //Burn In Flag	//120830 Modify
							        (tempValue <= 58 + Enable_ProductModeAdjust * 2 + 0 * 4 + ENABLE_FACTORY_SSCADJ * 5 + (PanelminiLVDS || PANEL_VCOM_ADJUST) * 2) //Addr	//120830 Modify
							   )
								SaveMonitorSetting();//UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
							Clr_SaveSettingFlag();
						}
						#endif
					}
					Delay1ms(200);
				}
				break;
			case MIA_JumpAdjustItem:	//工厂菜单
			case MIA_JumpNaviItem:		//工厂菜单
				tempValue = MenuItemIndex;
				MenuItemIndex += ((menuAction == MIA_JumpAdjustItem) ? (1) : ( - 1));
				#if 1
				if (MenuPageIndex == FactoryMenu)
					// for factory mode
				{
					if ((MenuItemIndex == Item_9300R && tempValue < Item_9300R) || (MenuItemIndex == Item_9300B && tempValue > Item_adj9300B))
					{
						SetFactoryColorTempCool1();
					}
					else if ((MenuItemIndex == Item_6500R && tempValue < Item_6500R) || (MenuItemIndex == Item_6500B && tempValue > Item_adj6500B))
					{
						SetFactoryColorTempWarm1();
					}
					#if CT_7500K_ENABLE
					else if ((MenuItemIndex == Item_7500R && tempValue < Item_7500R) || (MenuItemIndex == Item_7500B && tempValue > Item_adj7500B))
					{
						SetFactoryColorTempNormal();
					}
					#endif
					#if CT_sRGB_ENABLE
					else if ((MenuItemIndex == 31 && tempValue < 31) || (MenuItemIndex == 35 && tempValue > 36))
					{
						SetFactoryColorTempSRGB();
					}
					#endif
					#if 1 //2006-08-03 Andy Due To Color Setting Not Complete
					if (SaveSettingFlag)
					{
						//121108 Modify
						SaveFactorySetting();//UserPref_EnableFlashSaveBit(bFlashSaveFactoryBit);
						if ((tempValue >= 53 + Enable_ProductModeAdjust * 2 + ENABLE_FACTORY_SSCADJ * 5 + (PanelminiLVDS || PANEL_VCOM_ADJUST) * 2) && //Burn In Flag	//120830 Modify
						        (tempValue <= 58 + Enable_ProductModeAdjust * 2 + 0 * 4 + ENABLE_FACTORY_SSCADJ * 5 + (PanelminiLVDS || PANEL_VCOM_ADJUST) * 2) //Addr	//120830 Modify
						   )
							SaveMonitorSetting();//UserPref_EnableFlashSaveBit(bFlashSaveMonitorBit);
						Clr_SaveSettingFlag();
					}
					#endif
				}
				#endif
				//printData("MenuItem Index %d",MenuItemIndex);
				DrawOsdMenuItem(tempValue, &CurrentMenuItems[tempValue]);
				DrawOsdMenuItem(MenuItemIndex, &CurrentMenuItem);
				Delay1ms(200);
				break;
			case MIA_GotoNext:
			case MIA_GotoPrev:
				PrevMenuItemIndex = MenuItemIndex;
				PrevPage = MenuPageIndex;
				UserPrefInputType = SrcInputType; //For OSD Input Type Display Error When Time out            Zhifeng.Wu 20071128
				MenuPageIndex = (menuAction == MIA_GotoNext) ? (NextMenuPage) : (PrevMenuPage);
				#if PresetMode_Enable && Enable_Gamma
				if(UserPrefECOMode == ECO_Preset && MenuPageIndex == DCRMenu )
					MenuPageIndex = GammaMenu;
				#endif
				if ((PrevPage == RootMenu && MenuPageIndex == MainMenu))
				{
					#if Enable_DDCCI_OSDEnable_EN
					if(DDCOSDDisEnableFlag)
					{
						MenuPageIndex = RootMenu;
						break;
					}
					#endif
					if( FactoryModeFlag )// while enter factory, then stay in Lum.
					{
						#if HowShowFMenu
						MenuPageIndex = FactoryMenu;
						MenuItemIndex = 0;
						#else
						MenuItemIndex = MAIN_MAX_ITEM;
						#endif
					}
					else
						MenuItemIndex = 0;
				}
				#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
				else if (PrevPage == InputSelectMenu && MenuPageIndex == OSD_MiscMenu)
				{
					// clear status Text
					Osd_Set256TextColor( F_DRAKRED_B_BLACKRED, Color_2);
					//Osd_DrawContinuesChar( 0x19, 0x04, MonoSpace, 10);		//注释后可解决退出三级菜单出现白框的问题
					MenuItemIndex = GetMenuItemIndex(PrevPage);
				}
				#endif
				else
				{
					MenuItemIndex = GetMenuItemIndex(PrevPage);
				}
				if( menuAction == MIA_GotoPrev && BackToUnsupportFlag && UnsupportedModeFlag ) //20130517 add
				{
					MenuPageIndex = UnsupportedModeMenu;
					moveX = 50;	//111223 Modify
					moveY = 50;	//111223 Modify
					Osd_Hide();	//111223 Modify
					Clr_BackToUnsupportFlag();
					Clr_BackToStandbyFlag();
				}
				else if( menuAction == MIA_GotoPrev && BackToStandbyFlag )
				{
					#if DEBUG_HOTSWITCH
					printMsg("menuAction == MIA_GotoPrev && BackToStandbyFlag");
					#endif
					MenuPageIndex = StandbyMenu;
					Osd_Hide();	//111223 Modify
					Clr_BackToStandbyFlag();
				}
				Clr_PressExitFlag();
				Clr_EnableShowDDCFlag();
				Clr_PressMenuFlag();
				Clr_MuteFlag();
				#if 0
				Clr_PressMinusFlag();
				#endif
				#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
				Clr_PressPlusFlag();
				Clr_EnableExpansionMenuFlag();
				#endif
			case MIA_RedrawMenu:	//进入到菜单重画函数----	DrawOsdMenu()、DrawOsdMenuItem(MenuItemIndex,&CurrentMenuItem)、DrawOsdSubMenu(MenuPageIndex)
				#if ENABLE_DEBUG
				printData("MenuPageIndex==AA===>>>>%d", MenuPageIndex);
				printData("FactoryMenu==AA===>>>>%d", FactoryMenu);
				#endif
				#if DDCCI_ENABLE && DDCCCIMenu_Enable
				if (MenuPageIndex == DdcciInfoMenu)
					CurrentMenu.ExecFunction();
				#endif
				DrawOsdMenu();
				if( MenuPageIndex == MainMenu )
					DrawOsdSubMenu( NextMenuPage );
				#if DDCCI_ENABLE && DDCCCIMenu_Enable
				if (MenuPageIndex == DdcciInfoMenu)
					Delay1ms(200);
				//Benz 2007.4.24   21:45:31  so bad solution but no time cover it
				#endif
				#if DDCCI_ENABLE && DDCCCIMenu_Enable
				if (CurrentMenu.ExecFunction && MenuPageIndex != DdcciInfoMenu)
				#else
				if (CurrentMenu.ExecFunction)
				#endif
				{
					tempValue = CurrentMenu.ExecFunction();
					#if AboutDSUBFunc_Enable
					if (CurrentMenu.ExecFunction == AutoColor && MenuPageIndex == FactoryMenu)
					{
						Osd_SetTextColor(0, 6);
						if (tempValue)
						{
							Osd_DrawRealStr_F(10, 3, PassText());
						}
						else
						{
							Osd_DrawRealStr_F(10, 3, FailText());
						}
						Delay1ms(200);
					}
					#endif
				}
				if (!(CurrentMenu.Flags & mpbStay))
				{
					processEvent = TRUE;
					menuAction = MIA_GotoPrev;
				}
				if (SaveSettingFlag)
				{
					SaveUserPrefSetting(PrevPage);
				}
				break;
			case MIA_ExecFunc:		//执行功能函数----- CurrentMenuItemFunc.ExecFunction	//运行MenuItem参数的ExecFunction()功能函数
				if (CurrentMenuItemFunc.ExecFunction)
				{
					if (CurrentMenuItemFunc.ExecFunction == AutoColor)
					{
						Osd_SetTextColor(CP_WhiteColor, CP_BlueColor);
					}
					else if(CurrentMenuItemFunc.ExecFunction == ResetAllSetting)
					{
						Osd_Hide();
					}
					processEvent = CurrentMenuItemFunc.ExecFunction();
					#if AboutDSUBFunc_Enable
					if (CurrentMenuItemFunc.ExecFunction == AutoColor && MenuPageIndex == FactoryMenu)
					{
						Osd_SetTextMonoColor(/*CP_RedColor*/0x0F, CP_BlueColor);
						if (processEvent)
						{
							Osd_DrawRealStr_F(12, 2, PassText());
						}
						else
						{
							Osd_DrawRealStr_F(12, 2, FailText());
						}
						#if 1 //2006-08-03 Andy
						DrawOsdMenuItemNumber(0, DrawGainRNumber);
						DrawOsdMenuItemNumber(0, DrawGainGNumber);
						DrawOsdMenuItemNumber(0, DrawGainBNumber);
						#ifdef TSUMXXT		//110316 Modify
						Osd_SetTextMonoColor(CP_GrayColor, CP_BlueColor);
						#endif
						DrawOsdMenuItemNumber(0, DrawOffsetRNumber);
						DrawOsdMenuItemNumber(0, DrawOffsetGNumber);
						DrawOsdMenuItemNumber(0, DrawOffsetBNumber);
						#endif
					}
					#endif
					#if !AdjustLanguageFunction
					else if(CurrentMenuItemFunc.ExecFunction == AdjustLanguage && MenuPageIndex == LanguageMenu)
					{
						for(tempValue = SUB_TEXT_YPOS; tempValue < 0x0F; tempValue += 2)
							Osd_DrawContinuesChar( SUB_TEXT_XPOS, tempValue, SpaceFont, 0x27 - SUB_TEXT_XPOS);
						LoadLanguageStatusPropfont();
						MenuPageIndex = MainMenu;
						Osd_SetTextMonoColor(0x00, 0x06);
						Osd_DrawContinuesChar( 2, 1, SpaceFont, 0x27);
						MenuItemIndex = MAIN_Osd_ITEM;
						DrawOsdMenuItemRadioGroup(MAIN_Osd_ITEM, CurrentMenuItems[MAIN_Osd_ITEM].DisplayValue.DrawRadioGroup);
						MenuPageIndex = OsdMenu;
						MenuItemIndex = GetMenuItemIndex(MenuPageIndex);
						menuAction = MIA_RedrawMenu;
						processEvent = TRUE;
						break;
					}
					#endif
					else if(CurrentMenuItemFunc.ExecFunction == ResetAllSetting)
					{
						if(UserPrefLanguage != DefLanguage)
						{
							UserPrefLanguage = DefLanguage;
							#if 1
							LoadLanguageStatusPropfont();
							#else
							for(tempValue = SUB_TEXT_YPOS; tempValue < 0x0F; tempValue += 2)
								Osd_DrawContinuesChar( SUB_TEXT_XPOS, tempValue, SpaceFont, 0x27 - SUB_TEXT_XPOS);
							LoadLanguageStatusPropfont();
							MenuPageIndex = MainMenu;
							Osd_SetTextMonoColor(0x00, 0x06);
							Osd_DrawContinuesChar( 2, 1, SpaceFont, 0x27);
							MenuItemIndex = MAIN_Setting_ITEM;
							DrawOsdMenuItemRadioGroup(MAIN_Setting_ITEM, CurrentMenuItems[MAIN_Setting_ITEM].DisplayValue.DrawRadioGroup);
							DrawOsdSubMenu(SettingMenu);
							MenuPageIndex = SettingMenu;
							MenuItemIndex = Setting_RESTR_ITEM;
							DrawOsdMenuItem(MenuItemIndex, &CurrentMenuItem);
							#endif
						}
						if(SrcInputType < Input_Digital)
							MenuPageIndex = AutoMenu;
						else
							MenuPageIndex = RootMenu;
						MenuItemIndex = 0;
						menuAction = MIA_RedrawMenu;
						processEvent = TRUE;
						break;
					}
					#if (!USEFLASH) // 130829 larry
					if (CurrentMenuItemFunc.ExecFunction == EraseAllEEPROMCell)
					{
						if (processEvent)
						{
							Osd_SetTextMonoColor(CP_RedColor, CP_BlueColor);
							Osd_DrawRealStr_F(15, 30, PassText());
						}
						else
						{
							Osd_SetTextMonoColor(CP_GrayColor, CP_BlueColor);
							Osd_DrawRealStr_F(15, 30, FailText());
						}
					}
					#endif
					#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
					if(( MenuPageIndex == InputSelectMenu
				        #if HotInputSelect
					        || MenuPageIndex == HotInputSelectMenu
				        #endif
					   ) && processEvent == FALSE )
					{
						menuAction = MIA_GotoPrev;
						MenuItemIndex = 0;
						processEvent = TRUE;
					}
					else
					#endif
					#if HotInputSelect
						if ((MenuPageIndex == InputSelectMenu || MenuPageIndex == HotInputSelectMenu) && processEvent == TRUE) //20151103 alpha for MHL
						{
							MenuPageIndex = RootMenu;
							MenuItemIndex = 0;
							processEvent = FALSE;
						}
						else
					#endif
							processEvent = FALSE;	//110424 Modify
				}
				break;
			case MIA_Exit:		//退出菜单事件
				if (SaveSettingFlag)
				{
					Clr_SaveSettingFlag();
					SaveUserPref();
				}
				menuAction = MIA_RedrawMenu;
				PrevPage = MenuPageIndex; //WMZ 050816
				MenuPageIndex = RootMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				Clr_PressExitFlag();
				Clr_EnableShowDDCFlag();
				Clr_PressMenuFlag();
				Clr_MuteFlag();
				#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
				Clr_PressPlusFlag();
				Clr_EnableExpansionMenuFlag();
				#endif
				break;
				#if Hotkey_ECO_Enable
			case MIA_ECO:
				if (FreeRunModeFlag || UnsupportedModeFlag)
				{
					break;
				}
				#if  !HotKey_ECO_DCR
				if (UserPrefDcrMode)
				{
					break;
				}
				#endif
				mStar_WaitForDataBlanking();
				Osd_Hide();
				#if CT_sRGB_ENABLE
				if( UserPrefColorTemp == CTEMP_SRGB)	//120204 Modify
					UserPrefECOMode = ECO_Standard;
				#endif
				menuAction = MIA_RedrawMenu;
				#if  HotKey_ECO_DCR
				if(UserPrefDcrMode)
				{
					MenuPageIndex = HotKeyDCRMenu;
				}
				else
				#endif
				{
					MenuPageIndex = HotKeyECOMenu;
				}
				MenuItemIndex = 0;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat; // 071218 addition to prevent hot key event execute twince
				break;
				#endif
				#if AudioFunc &&  ENABLE_OSD_HotKeyVolume
			case MIA_VOL:
				if (FreeRunModeFlag || UnsupportedModeFlag || (SrcInputType == Input_VGA))
				{
					break;
				}
				Osd_Hide();
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = HotKeyVolMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat; // 071218 addition to prevent hot key event execute twince
				break;
				#endif
				#if Hotkey_BriCon_Enable
			case MIA_Brite:
			case MIA_Cont:
				#if CT_sRGB_ENABLE
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefColorTemp == CTEMP_SRGB || UserPrefDcrMode || UnsupportedModeFlag)
				#else
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefDcrMode || UnsupportedModeFlag)
				#endif
				{
					break;
				}
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = HotKeyBriMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat;
				break;
				#endif
				#if Hotkey_Bri_Enable
			case MIA_Brite:
				#if CT_sRGB_ENABLE
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefColorTemp == CTEMP_SRGB || UserPrefDcrMode || UnsupportedModeFlag)
				#else
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefDcrMode || UnsupportedModeFlag)
				#endif
				{
					break;
				}
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = HotKeyBriMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat;
				break;
				#endif
				#if Hotkey_Con_Enable
			case MIA_Cont:
				#if CT_sRGB_ENABLE
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefColorTemp == CTEMP_SRGB || UserPrefDcrMode || UnsupportedModeFlag)
				#else
				if (FreeRunModeFlag || UserPrefECOMode != ECO_Standard || UserPrefDcrMode || UnsupportedModeFlag)
				#endif
				{
					break;
				}
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = HotKeyBriMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat;
				break;
				#endif
				#if Hot_Corss_ColorSelect||Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
			case MIA_HotCorssMenu:
				DynamicLoadHotCorssIcon(0);
				MenuPageIndex = HotCorssMenu;
				MenuItemIndex = 0;
				KeypadButton = BTN_Repeat;
				menuAction = MIA_RedrawMenu;
				processEvent = TRUE;
				break;
				#endif
				#if DDCCI_ENABLE && DDCCCIMenu_Enable&&0
			case MIA_DDC:
				if (FreeRunModeFlag )
				{
					break;
				}
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = DdcciInfoMenu;
				DynamicLoadFont(CurrentMenu.Fonts);
				MenuItemIndex = 0;
				processEvent = TRUE;
				Clr_PressExitFlag();
				Clr_EnableShowDDCFlag();
				#if 0
				Clr_PressMinusFlag();
				#endif
				#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
				Clr_PressPlusFlag();
				Clr_EnableExpansionMenuFlag();
				#endif
				break;
				#endif
			case MIA_Auto:
				#if CHIP_ID>=CHIP_TSUMC
				if (FreeRunModeFlag || SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3 )  //121128 Modify
				#else
				if (FreeRunModeFlag || SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport )   //121128 Modify
				#endif
				{
					Clr_PressMenuFlag();
					Clr_PressExitFlag();
					break;
				}
				#ifdef DCRClearBacklight//When user press eco hotkey,turn on backlight.
				if(!BackLightActiveFlag)
					hw_SetBlacklit();
				#endif
				TurboKeyCounter = 0;
				// printMsg( "draw auto menu" );
				Set_DoAutoConfigFlag(); // 2007/9/14  by KK for match osd
				menuAction = MIA_RedrawMenu;
				MenuPageIndex = AutoMenu;
				MenuItemIndex = 0;
				processEvent = TRUE;
				break;
				//2006-02-22
				#if HotInputSelect
			case MIA_ShowHotInput:
				if (!PowerOnFlag)
					break;
				mStar_PowerUp();
				mStar_SetupFreeRunMode();
				//SwitchPortCntr = 0;
				#if AudioFunc 	//120502 Modify
				hw_ClrAudio_SD();
				#endif
				Power_TurnOnGreenLed();
				if( MenuPageIndex == StandbyMenu )	//111223 Modify
				{
					Set_BackToStandbyFlag();
					#if DEBUG_HOTSWITCH
					printMsg("Set_BackToStandbyFlag");
					#endif
				}
				if (PowerDownCounter)
				{
					PowerDownCounter = 0;
				}
				{
					MenuPageIndex = HotInputSelectMenu;
					if(UserPrefInputSelectType == INPUT_PRIORITY_AUTO)
						MenuItemIndex = SrcInputType;
					else
						MenuItemIndex = UserPrefInputSelectType;
				}
				PrevPage = RootMenu;
				Osd_Hide();
				menuAction = MIA_RedrawMenu;
				processEvent = TRUE;
				break;
				#endif
				#if HotInputSelect
			case MIA_SourceSel:
				if ((!PowerOnFlag) )//|| (PowerSavingFlag))
				{
					break;
				}
				if(CheckSourceKeyStatus())
					break;
				if( MenuPageIndex == UnsupportedModeMenu)	//111223 Modify
				{
					Set_BackToUnsupportFlag();
				}
				Osd_Hide();///20130503 avoid Unsupport mode OSD garbage
				//mStar_WaitForDataBlanking();
				//ForceDelay1ms(10);  //avoid Unsupport mode OSD garbage  20130416
				#if MS_PM
				#if ENABLE_AutoDetech
				if( PowerSavingFlag )
				{
					Osd_Hide();
					//Power_PowerOnSystem();
					Clr_InputTimingChangeFlag();
					Set_BackToStandbyFlag();	//120521 Modify
					mStar_SetupFreeRunMode();
					mStar_AdjustBrightness( 0xFF );
					Power_TurnOnGreenLed();	//120523 Modify
					#if AudioFunc	//121128 Modify
					hw_ClrAudio_SD();
					#endif
				}
				#endif
				#endif
				//printMsg("MIA_SourceSel");
				menuAction = MIA_RedrawMenu;
				{
					{
						MenuPageIndex = HotInputSelectMenu;
						#if 1	//120521 Modify for TPV Request
						MenuItemIndex = UserPrefInputType;
						#else
						MenuItemIndex = SrcInputType;
						#endif
					}
				}
				processEvent = TRUE;
				Clr_PressExitFlag();
				break;
				#endif
				#if  Hotkey_DCR_Enable
			case MIA_DCR:
				if (FreeRunModeFlag || UnsupportedModeFlag)
				{
					break;
				}
				#if CT_sRGB_ENABLE
				if (UserPrefColorTemp == CTEMP_SRGB)
					UserPrefColorTemp = CTEMP_Warm1;
				#endif
				#if UnifyHotDcrEco
				UserPrefDcrMode = 0;
				AdjustDcrMode(0);
				#endif
				MenuPageIndex = HotKeyDCRMenu;
				MenuItemIndex = 0;
				menuAction = MIA_RedrawMenu;
				processEvent = TRUE;
				break;
				#endif
				#if HotExpansionAdjust
			case MIA_Expansion:
				if (FreeRunModeFlag || UnsupportedModeFlag)
				{
					#if ENABLE_OVER_SCAN && AudioFunc	//121211 Modify
					Clr_PressPlusFlag();
					Clr_EnableExpansionMenuFlag();
					#endif
					break;
				}
				mStar_WaitForDataBlanking();
				Osd_Hide();
				MenuPageIndex = HotExpansionMenu;
				MenuItemIndex = 0;
				menuAction = MIA_RedrawMenu;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat;
				break;
				#endif
			case MIA_Power:		//电源按键事件
				if (MenuPageIndex == OSD_MiscMenu && MenuItemIndex == 0 )
				{
					Clr_SaveSettingFlag();
					ReadMonitorSetting();
				}
				if (PowerOnFlag)
				{
					MenuPageIndex = PowerOffMenu;
				}
				else
				{
					MenuPageIndex = PowerOnMenu;
				}
				MenuItemIndex = 0;
				menuAction = MIA_RedrawMenu;
				processEvent = TRUE;
				KeypadButton = BTN_Repeat; // 090517 coding
				break;
			default:
				return FALSE;
				break;
		}
	}
	return TRUE;
}
//=========================================================================

#if 0
#if 0
#if CHIP_ID >=CHIP_TSUM2
extern void OSDSetMask0(BYTE item, BYTE v);
extern void OSDGDCurveSelectionForWindow(BYTE gi, BYTE wi, BYTE ci);
extern void OSDConfGDCurveH(BYTE ci, BYTE pixel_init, BYTE delta_init,
                            BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                            BYTE hv_sign, BYTE overflow_en, BYTE md);
extern void OSDConfGDCurveV(BYTE ci, BYTE pixel_init, BYTE delta_init,
                            BYTE step, BYTE data_sign, BYTE delta_sign, BYTE delta, WORD length0, WORD length1,
                            BYTE overflow_en, BYTE md);
void ClrGradualColor()
{
	OSDSetMask0(0x01, 0); //GD Palette must Mask to 1
	OSDSetMask0(0x09, 0); //GD Palette must Mask to 1
	OSDSetMask0(0x81, 0); //GD Palette must Mask to 1
	OSDGDCurveSelectionForWindow(OSD_GD_EG4, OSD_MAIN_WND, 1);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 1,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 1,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,            0,   0 );
	OSDSetMask0(0x0F, 0); //GD Palette must Mask to 1
	OSDGDCurveSelectionForWindow(OSD_GD_EG3, OSD_CURSOR_WND, 0);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 0,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 0,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,            0,   0 );
}
void SetGradualColor_MAIN_WND(void)
{
	OSDSetMask0(0x01, 1); //GD Palette must Mask to 1
	OSDSetMask0(0x09, 1); //GD Palette must Mask to 1
	OSDSetMask0(0x81, 1); //GD Palette must Mask to 1
	OSDGDCurveSelectionForWindow(OSD_GD_EG4, OSD_MAIN_WND, 1);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 1,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 1,        0xFF,        0x03,     0,          1,           0,      0,       90,   216 - 90,            0,   0 );
}
void SetGradualColor_CURSOR_WND(void)
{
	OSDSetMask0(0x0F, 1); //GD Palette must Mask to 1
	OSDGDCurveSelectionForWindow(OSD_GD_EG3, OSD_CURSOR_WND, 0);
//OSDConfGDCurveH( ci, Hpixel_init, Hdelta_init, Hstep, Hdata_sign, Hdelta_sign, Hdelta, Hlength0, Hlength1, hv_sign, Hoverflow_en, Hmd );
	OSDConfGDCurveH( 0,        0x00,        0x00,     0,          0,           0,      0,   0xffff,   0xffff,       0,            0,   0 );
//OSDConfGDCurveV( ci, Vpixel_init, Vdelta_init, Vstep, Vdata_sign, Vdelta_sign, Vdelta, Vlength0, Vlength1, Voverflow_en, Vmd );
	OSDConfGDCurveV( 0,        0xFF,        0x0F,     0,          1,           0,      0,       18,        0,            0,   0 );
}

#else
void ClrGradualColor()
{
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_G(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_B(OSD_COLOR_FIX)),
	                  OWC2MASK_ALL);
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_G(OSD_COLOR_FIX) |
	                   OWC2_GD_COLOR_B(OSD_COLOR_FIX)),
	                  OWC2MASK_ALL);
}
void SetGradualColor_MAIN_WND(void)
{
	BYTE u8Bank = msReadByte(OSD1_00);
	msWriteByte(OSD1_00, 0x01); //sunbank 1
	if (msReadByte(OSD1_A3) != 0x80)
	{
		msWrite2ByteMask(OSD1_9E, 0, 0x3FF); //(5*18) //gd4 vlength
		msWriteByte(OSD1_A0, 0xFF); //gd4 V init
		msWriteByte(OSD1_A1, 0x03); //gd4 V delta init
		msWriteByte(OSD1_A2, 0x01); //gd4 V step
		msWriteByte(OSD1_A3, 0x80); //gd4 V delta bit7 sign
	}
	msWriteByte(OSD1_00, u8Bank);
	drvOSD_SetWndCtrl(OSD_MAIN_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_GD_EG4) |
	                   OWC2_GD_COLOR_G(OSD_GD_EG4) |
	                   OWC2_GD_COLOR_B(OSD_GD_EG4)),
	                  OWC2MASK_ALL);
}
void SetGradualColor_CURSOR_WND(void)
{
	BYTE u8Bank = msReadByte(OSD1_00);
	msWriteByte(OSD1_00, 0x01); //sunbank 1
	if (msReadByte(OSD1_97) != 0x80)
	{
		msWrite2ByteMask(OSD1_92, 0, 0x3FF); //(1*18) //gd3 vlength
		msWriteByte(OSD1_94, 0xFF); //gd3 V init
		msWriteByte(OSD1_95, 0x0F); //gd3 V delta init
		msWriteByte(OSD1_96, 0x01); //gd3 V step
		msWriteByte(OSD1_97, 0x80); //gd3 V delta bit7 sign
	}
	msWriteByte(OSD1_00, u8Bank);
	drvOSD_SetWndCtrl(OSD_CURSOR_WND, OSD_WND_CTRL2,
	                  (OWC2_GD_COLOR_R(OSD_GD_EG3) |
	                   OWC2_GD_COLOR_G(OSD_GD_EG3) |
	                   OWC2_GD_COLOR_B(OSD_GD_EG3)),
	                  OWC2MASK_ALL);
}
#endif

#define MoveSpeed 40
#define IS_OVER_XYRATIO(nY, mY, nX, mX, pX)((3*abs(nY-mY)*abs(mX-pX))>=(2*abs(nX-pX)))
void SelectItem(BYTE ucXPos, BYTE ucYPos, BYTE ucColor)
{
	#if 1
	WORD xdata ucNowXPos = ucXPos;
	WORD xdata ucNowYPos = ucYPos;
	BYTE xdata ucMoveXPos = 0;
	BYTE xdata ucMoveYPos = 0;
	//printData("ucPreYPos[%d]", ucPreYPos);
	//printData("ucNowYPos[%d]", ucNowYPos);
	//first time or select/exec change
	if ( ucPreYPos == 0)
	{
		//printData("---SetOSDWindosw", 0);
		mStar_WaitForDataBlanking();
		SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucYPos, ucYPos, ucColor);
	}
	else
	{
		mStar_WaitForDataBlanking();
		if (ucNowYPos > ucPreYPos && ucNowXPos == ucPreXPos)
		{
			bMoveCURSORFlag = 1;
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucPreYPos, ucPreYPos, ucColor);
			Delay1ms(MoveSpeed);
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucPreYPos + 1, ucPreYPos + 1, ucColor);
			Delay1ms(MoveSpeed);
			bMoveCURSORFlag = 0;
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucNowYPos, ucNowYPos, ucColor);
		}
		else if (ucNowYPos < ucPreYPos && ucNowXPos == ucPreXPos)
		{
			bMoveCURSORFlag = 1;
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucPreYPos, ucPreYPos, ucColor);
			Delay1ms(MoveSpeed);
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucPreYPos - 1, ucPreYPos - 1, ucColor);
			Delay1ms(MoveSpeed);
			bMoveCURSORFlag = 0;
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucNowYPos, ucNowYPos, ucColor);
		}
		else if (ucNowYPos != ucPreYPos || ucNowXPos != ucPreXPos)
		{
			ucMoveYPos = ucPreYPos;
			ucMoveXPos = ucPreXPos;
			do
			{
				Delay1ms(3 * abs(ucNowXPos - ucMoveXPos) / 2 + 1);
				if(IS_OVER_XYRATIO(ucNowYPos, ucMoveYPos, ucNowXPos, ucMoveXPos, ucPreXPos))
				{
					if(ucMoveYPos != ucNowYPos)
					{
						if(ucPreYPos < ucNowYPos)
						{
							ucMoveYPos++;
						}
						else
						{
							ucMoveYPos--;
						}
					}
				}
				if(ucMoveXPos != ucNowXPos)
				{
					if(ucPreXPos < ucNowXPos)
						ucMoveXPos = ucMoveXPos + ((ucNowXPos - ucMoveXPos + 3) / 4);
					else
						ucMoveXPos = ucMoveXPos - ((ucMoveXPos - ucNowXPos + 3) / 4);
				}
				if (ucMoveYPos == ucNowYPos && ucMoveXPos == ucNowXPos)
					bMoveCURSORFlag = 0;
				else
					bMoveCURSORFlag = 1;
				SetOSDWindosw(OSD_CURSOR_WND, ucMoveXPos - 1, ucMoveXPos + 26, ucMoveYPos, ucMoveYPos, ucColor);
			}
			while(!(ucMoveYPos == ucNowYPos && ucMoveXPos == ucNowXPos));
		}
		else
			SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucYPos, ucYPos, ucColor);
	}
	ucPreXPos = ucXPos;
	ucPreYPos = ucYPos;
	#else
	//mStar_WaitForDataBlanking();
	SetOSDWindosw(OSD_CURSOR_WND, ucXPos - 1, ucXPos + 26, ucYPos, ucYPos, ucColor);
	//SetOSDWindosw(OSD_ICON_WND,0,113,0,4, ucColor);
	#endif
}
#endif
#endif


void DrawOsdMenu(void)
{
	Bool redrawFlags;
	//解决刷新二级菜单时，将整个背景刷新导致闪屏的问题
	if(PrevPage == MainMenu && (MenuPageIndex >= OSD_BriContrastMenu && MenuPageIndex <= OSD_MiscMenu))
	{
		DrawOsdBackGround();
	}
	//======================显示当前整个OSD界面======================
	if((MenuPageIndex >= MainMenu && MenuPageIndex < ExitMenu) || MenuPageIndex == HotInputSelectMenu)
	{
		int i;
		for(i=0; i<MenuItemCount; i++)
		{
			DrawOsdMenuItem(i, &CurrentMenu.MenuItems[i]);
		}
	}
	//===============================================================
	#if ENABLE_DEBUG
	printData("MenuPageIndex       %d", MenuPageIndex);
	#endif
	Clr_JustShowValueFlag();
//20171226
	if(LoadOSDDataFlag)//eshin
	{
		Clr_LoadOSDDataFlag();
		Osd_Hide();
		LoadCommonFont();
		DynamicLoadFont(CurrentMenu.Fonts);
	}
	#if DEBUG_PRINTDATA
//    printData("FontEndAddr[0x%]",FontEndAddr);
	printData("MenuPageIndex=%d", MenuPageIndex);
	printData("MenuItemIndex=%d", MenuItemIndex);
	#endif
	if (CurrentMenu.Flags & mpbInvisible)
	{
		Osd_Hide();
	}
	else
	{
		BYTE xdata i;
		redrawFlags = FALSE;
		//Set_FactoryModeFlag();
		if (CurrentMenu.Fonts && (MenuPageIndex != LanguageMenu) && (PrevPage != LanguageMenu) )
		{
			DynamicLoadFont(CurrentMenu.Fonts);
		}
		else if (CurrentMenuItem.Fonts)
		{
			DynamicLoadFont(CurrentMenuItem.Fonts);
		}
		if(( CurrentMenu.XSize != OsdWindowWidth || CurrentMenu.YSize != OsdWindowHeight || CurrentMenu.Flags & mpbRedraw )
		        && !( MenuPageIndex == MainMenu && PrevPage != RootMenu && PrevPage != LanguageMenu))
		{
			redrawFlags = TRUE;
		}
		if (redrawFlags)
		{
			Osd_Hide();
			Osd_SetWindowSize(CurrentMenu.XSize, CurrentMenu.YSize);
			//   Delay1ms(200);
			if ((MenuPageIndex == MainMenu) && PrevPage == RootMenu && !(FactoryModeFlag))
				Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
			else if (MenuPageIndex == InputInfoMenu)
			{
				Osd_SetPosition(98, 98);
			}
			#if HotInputSelect
			else if(MenuPageIndex == HotInputSelectMenu)
			{
				#if EN_HotInputSelect_ShowCenter
				Osd_SetPosition(50, 50);
				#else
				Osd_SetPosition(98, 98);
				#endif
			}
			#endif
			else
			{
				if (CurrentMenu.Flags & mpbCenter)
				{
					Osd_SetPosition(50, 50);
				}
				else if ((FactoryModeFlag) || MenuPageIndex == FactoryMenu)
				{
					Osd_SetPosition(5, 97);
				}
				else if (!(CurrentMenu.Flags & mpbMoving))
				{
					Osd_SetPosition(UserPrefOsdHStart, UserPrefOsdVStart);
				}
			}
			//       Delay1ms(200);
			if (MenuPageIndex == LogoMenu)
			{
				// printMsg("draw logo");
				Osd_SetPosition(50, 50);
				moveX = 50;
				moveY = 50;
				#if (DisplayLogo!=NoBrand)
				DrawLogo();
				#endif
			}
			else if (MenuPageIndex == FactoryMenu
		         #if EN_ShowInfoUnderBurinInMenu
			         || MenuPageIndex == BurninMenu
		         #endif
			        )
			{
				Osd_Hide();
				Delay1ms(80);
				Osd_LoadFacoryFontCP();
				Set_LoadOSDDataFlag();
				Osd_Set256TextColor( CP_BlueColor << 4 | CP_BlueColor, Color_2);
				for (i = 0; i <= OsdWindowHeight - 1; i++)
				{
					Osd_DrawContinuesChar( 0, i, SpaceFont, OsdWindowWidth);
				}
			}
			else
			{
				DrawOsdBackGround();
			}
			#if Hot_Corss_ColorSelect 	|| Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
			if(MenuPageIndex == HotCorssMenu)
				DrawOsdMenuItem(0, &CurrentMenu.MenuItems[0]);
			else
			#endif
				for (i = 0; i < MenuItemCount; i++)
				{
					DrawOsdMenuItem(i, &CurrentMenu.MenuItems[i]);
				}
			if(MenuPageIndex == LogoMenu)
				Osd_SetTransparence(0);
			else
				Osd_SetTransparence(UserPrefOsdTrans);
			Osd_Show();
		} // end redraw
		else
		{
			#if !AdjustLanguageFunction
			if(MenuPageIndex == LanguageMenu || (MenuPageIndex == OsdMenu && PrevPage == LanguageMenu))
			{
				Osd_SetTextMonoColor(0x00, 0x07);
				for(i = SUB_TEXT_YPOS; i < 0x0F; i += 2)
				{
					Osd_DrawContinuesChar( SUB_TEXT_XPOS, i, SpaceFont, 0x27 - SUB_TEXT_XPOS);
				}
				DynamicLoadFont(CurrentMenu.Fonts);
				for (i = 0; i < MenuItemCount; i++)
				{
					if(i != MenuItemIndex)
					{
						DrawOsdMenuItem(i, &CurrentMenu.MenuItems[i]);
					}
				}
			}
			#endif
			DrawOsdMenuItem( MenuItemIndex, &CurrentMenu.MenuItems[MenuItemIndex] );
			#if OsdHelpKeyType == OsdHelpKey_Under || OsdHelpKeyType ==	 OsdHelpKey_Right
			UpdataHelyKeyShowInMenu();
			#endif
		}
		#if  0//Show_BackLightTimeValue
		if (MenuPageIndex == FactoryMenu)
		{
			Osd_DrawNum(12, 25, BlacklitTime_H);
			Osd_DrawNum(17, 25, BlacklitTime_M);
		}
		#endif
	}
	PrevPage = MenuPageIndex;
	#if DEBUG_PRINTDATA
	printMsg("End of Draw Menu...");
	#endif
	//printMsg("End of Draw Menu...");
}



//=========================================================================
// draw menu item  画Item，判断是否被选中
void DrawOsdMenuItem(BYTE itemIndex, MenuItemType *menuItem)
{
	if( menuItem->Flags & mibFactoryItem && !FactoryModeFlag )
	{
		return ;
	}
	if( &CurrentMenuItem == menuItem && menuItem->Flags & mibSelectable )
	{
	}
	if( menuItem->Flags & mibSelectable && itemIndex == MenuItemIndex )
	{
		if( MenuPageIndex == FactoryMenu
	        #if EN_ShowInfoUnderBurinInMenu
		        || MenuPageIndex == BurninMenu
	        #endif
		  )
		{
			Osd_SetTextMonoColor( menuItem->SelForeColor, menuItem->SelBackColor );
		}
		else
		{
			Osd_Set256TextColor( menuItem->SelForeColor, menuItem->SelBackColor );
		}
	}
	else
	{
		if( MenuPageIndex == FactoryMenu )
		{
			Osd_SetTextMonoColor( menuItem->ForeColor, menuItem->BackColor );
		}
		else
		{
			Osd_Set256TextColor( menuItem->ForeColor, menuItem->BackColor );
		}
	}
	DrawOsdMenuItemText( itemIndex, menuItem );
	if( MenuPageIndex == MainMenu && itemIndex == MenuItemIndex )
	{
		DrawOsdMenuItemValue( itemIndex, &( menuItem->DisplayValue ) );
	}
	else if( MenuPageIndex > MainMenu && MenuPageIndex < ExitMenu)
	{
		if(PrevPage == MainMenu)
			//return;
		{
			Osd_Set256TextColor( menuItem->ForeColor, menuItem->BackColor );
			DrawOsdMenuItemValue( itemIndex, &( menuItem->DisplayValue ) );
		}
		else
		{
			Osd_Set256TextColor( menuItem->ForeColor, menuItem->BackColor );
			DrawOsdMenuItemValue( itemIndex, &( menuItem->DisplayValue ) );
		}
	}
	else
	{
		DrawOsdMenuItemValue( itemIndex, &( menuItem->DisplayValue ) );
	}
}




//=========================================================================


// draw menu item display text		画图标-------画Icon及Text
void DrawOsdMenuItemText(BYTE itemIndex, MenuItemType *menuItem)
{
	if (menuItem->DisplayText == NULL && menuItem->DrawItemMethod != DWI_Icon)
	{
		return ;
	}
	if (menuItem->DrawItemMethod == DWI_Icon)
	{
		BYTE xdata i, j, *str;
		if(itemIndex == MenuItemIndex)		
			Osd_SetTextMonoColor( DRAK_RED_COLOR, BLACK_RED_COLOR );	//选中时，图标的前景色、背景色
		else								
			Osd_SetTextMonoColor( DRAK_WHITE_COLOR,	BLACK_COLOR );		//未选中时，图标的前景色、背景色
		#if 1//20130417-1
		if(MenuPageIndex == MainMenu &&  MenuItemIndex == MAIN_MAX_ITEM && !FactoryModeFlag) // F item
			return ;
		#endif
		//printData("DWI_Icon[%d]",itemIndex);
		if ( MenuPageIndex == MainMenu )
		{
			str = menuItem->DisplayText();
			OSD_TEXT_HI_ADDR_SET_BIT8(); //enable bit 9
			
			Osd_DrawCharDirect(menuItem->XPos, menuItem->YPos, str[0]);
			Osd_DrawCharDirect(menuItem->XPos + 1, menuItem->YPos, str[1]);
			
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		else
		{
			#if ENABLE_OVER_SCAN&& AudioFunc
			if (MenuPageIndex == HotExpansionMenu)
			{
				BYTE len;
				Osd_Set256TextColor( CPC_Background << 4 | CPC_Background, Color_2);
				for (len = 1; len < (OsdWindowHeight - 1); len++)
					Osd_DrawContinuesChar( 1, len, MonoSpace, (OsdWindowWidth - 2));
				if  ( (UserprefExpansionMode >= PIC_FORMAT_17Picth && UserprefExpansionMode <= PIC_FORMAT_W23Picth)) // && !INPUT_IS_NATIVE_TIMING())   //121228 Modify
				{
					DynamicLoadFont_RatioStatus();
					len = *(ExpansionValueText() + 1);
					len = OsdWindowWidth - len;
					len = (len + 1) / 2;
					Osd_Set256TextColor( CP_SelectItem, Color_2 );
					Osd_DrawPropStr( len, (OsdWindowHeight / 2),     ExpansionValueText() );
				}
				else
				{
					DynamicLoadHotIconFont();  //Load Icon font
					Osd_Set256TextColor( CP_SelectIcon >> 3, Color_8);
					OSD_TEXT_HI_ADDR_SET_BIT9(); //enable bit 9
					for( i = 0; i < 5; i++ )
					{
						for( j = 0; j < 3; j++ )
						{
							Osd_DrawCharDirect( menuItem->XPos + i, menuItem->YPos + j, _8ColorBigIconFont + i * 3 + j * 15 );
						}
					}
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
			}
			else
			#elif HotExpansionAdjust
			if (MenuPageIndex == HotExpansionMenu)
			{
				DynamicLoadHotIconFont();  //Load Icon font
				Osd_Set256TextColor( CP_SelectIcon >> 3, Color_8);
				OSD_TEXT_HI_ADDR_SET_BIT9(); //enable bit 9
				for( i = 0; i < 5; i++ )
					for( j = 0; j < 3; j++ )
						Osd_DrawCharDirect( menuItem->XPos + i, menuItem->YPos + j, _8ColorHotIconStart + i * 3 + j * 15 );
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
			else
			#endif
			{
				DynamicLoadHotIconFont();  //Load Icon font
				Osd_Set256TextColor(0x20, Color_4);
				OSD_TEXT_HI_ADDR_SET_BIT9(); //enable bit 9
				for( j = 0; j < 3; j++ )
					for( i = 0; i < 4; i++ )
						Osd_DrawCharDirect( menuItem->XPos + i, menuItem->YPos + j, _4ColorHotIconStart + (i + j * 4) * 2 );
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
	}
	#if Hot_Corss_ColorSelect
	else if (menuItem->DrawItemMethod == DWI_8x5Icon)
	{
		BYTE xdata i, j, *str;
		Osd_SetTextMonoColor( menuItem->SelForeColor, menuItem->SelBackColor );
		str = menuItem->DisplayText();
		OSD_TEXT_HI_ADDR_SET_BIT8(); //enable bit 9
		for( j = 0; j < 5; j++ )
			for( i = 0; i < 8; i++ )
				Osd_DrawCharDirect( menuItem->XPos + i, menuItem->YPos + j, *(str++));
		OSD_TEXT_HI_ADDR_CLR_TO_0();
	}
	#elif 	Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
	else if (menuItem->DrawItemMethod == DWI_10x6Icon)
	{
		BYTE xdata i, j, *str;
		Osd_SetTextMonoColor( menuItem->SelForeColor, menuItem->SelBackColor );
		str = menuItem->DisplayText();
		OSD_TEXT_HI_ADDR_SET_BIT8(); //enable bit 9
		for( j = 0; j < 6; j++ )
			for( i = 0; i < 10; i++ )
				Osd_DrawCharDirect( menuItem->XPos + i, menuItem->YPos + j, *(str + i + 11 * j));
		OSD_TEXT_HI_ADDR_CLR_TO_0();
	}
	#endif
	else if (menuItem->DrawItemMethod == DWI_Text)
	{
		if ( MenuPageIndex == FactoryMenu )
		{
			Osd_DrawRealStr_F( menuItem->XPos, menuItem->YPos, menuItem->DisplayText() );
		}
		else
		{
			if (menuItem->DisplayText() == Main_FText())
			{
				if( itemIndex == MenuItemIndex )
					Osd_SetTextMonoColor( menuItem->SelForeColor, menuItem->SelBackColor );
				else
					Osd_SetTextMonoColor( menuItem->ForeColor, menuItem->BackColor );
			}
			Osd_DrawPropStr(menuItem->XPos, menuItem->YPos, menuItem->DisplayText());
		}
	}
	else
		// full text
	{
		BYTE xPos;
#define len itemIndex
		//解决快捷菜单字体颜色问题
		if(itemIndex == MenuItemIndex)		
			Osd_SetTextMonoColor( DRAK_RED_COLOR, BLACK_RED_COLOR );	//选中时，图标的前景色、背景色
		else								
			Osd_SetTextMonoColor( DRAK_WHITE_COLOR, BLACK_COLOR );		//未选中时，图标的前景色、背景色

		if (menuItem->DrawItemMethod == DWI_FullText)
		{
			xPos = menuItem->XPos;
			Osd_DrawRealStr(xPos, menuItem->YPos, menuItem->DisplayText());
		}
		else if (menuItem->DrawItemMethod == DWI_CenterPropText)
		{
			#if 0//Dual
			if (menuItem->DisplayText() == NoSyncStatusText() && (UserPrefInputSelectType == INPUT_PRIORITY_AUTO))	//120301 Modify
				return;
			#endif
			#if INPUT_TYPE == INPUT_1A2H || INPUT_TYPE == INPUT_2H	//120511 Modify
			#endif
			{
				len = *(menuItem->DisplayText() + 1);
				len = OsdWindowWidth - len;
				len = (len + 1) / 2;
			}
			Osd_DrawPropStr(len, menuItem->YPos, menuItem->DisplayText());
		}
#undef len
	}
}
//=========================================================================
// draw menu item display value
void DrawOsdMenuItemValue(BYTE itemIndex, DrawValueType *valueItem)
{
	//printData("value address %x", (WORD)valueItem);
	if (valueItem->DrawNumber)
	{
		DrawOsdMenuItemNumber(itemIndex, valueItem->DrawNumber);
	}
	if (valueItem->DrawGuage)
	{
		DrawOsdMenuItemGuage(itemIndex, valueItem->DrawGuage);
	}
	if (valueItem->DrawRadioGroup)
	{
		DrawOsdMenuItemRadioGroup(itemIndex, valueItem->DrawRadioGroup);
	}
	#if 0  //2006-08-04 Andy
	if ((valueItem->DrawRadioGroup && itemIndex == MenuItemIndex)
	        || (valueItem->DrawRadioGroup && MenuPageIndex > MainMenu)) //||(valueItem->DrawRadioGroup&&MenuPageIndex==FactoryMenu))
		DrawOsdMenuItemRadioGroup(itemIndex, valueItem->DrawRadioGroup);
	#endif
	// printData("value address %x", (WORD)valueItem);
}
//=========================================================================
// draw number
void DrawOsdMenuItemNumber(BYTE itemIndex, DrawNumberType *numberItem)
{
	itemIndex = 0;
	#if Multi_Number
	{
		NumberType *number;
		BYTE i = 0;
		number = numberItem->DisplayNumber;
		if( number )
		{
#define drawItem    (number+i)
			while( 1 )
			{
				if( drawItem->Flags & dwiHex )
				{
					Osd_DrawHex( drawItem->XPos, drawItem->YPos, drawItem->GetValue() );
				}
				else
				{
					#if AboutDSUBFunc_Enable
					if((MenuPageIndex == FactoryMenu) &&
					        (
					            drawItem->GetValue == GetRedGainValue
					            || drawItem->GetValue == GetGreenGainValue
					            || drawItem->GetValue == GetBlueGainValue
					            || drawItem->GetValue == GetAdcRedOffsetValue
					            || drawItem->GetValue == GetAdcGreenOffsetValue
					            || drawItem->GetValue == GetAdcBlueOffsetValue
					        ))
					{
						DrawNum( drawItem->XPos, drawItem->YPos, 4, drawItem->GetValue() );
					}
					else
					#endif
						Osd_DrawNum( drawItem->XPos, drawItem->YPos, drawItem->GetValue() );
					#if !Enable_Adjust_SharpnessMenu
					#ifdef OffPower
					if ( drawItem->Flags & dwiOffTimer)
					{
						if (GetAutoPowerOffValue() < 10)
						{
							Osd_DrawCharDirect(drawItem->XPos + 2, drawItem->YPos, MonoNumberStart);
						}
					}
					#endif
					#endif
				}
				if( drawItem->Flags & dwiEnd )
				{
					break;
				}
				i++;
			}
#undef drawItem
		}
	}
	#else
#define xPos itemIndex
	xPos = numberItem->XPos;
	if (xPos == 0)
	{
		xPos = (OsdWindowWidth - 4) / 2 - 1;
	}
	if (FactoryModeFlag && MenuPageIndex == FactoryMenu)
	{
		if (CurrentMenuItem.DisplayValue.DrawNumber == numberItem)
		{
			Osd_SetTextColor(numberItem->ForeColor, numberItem->BackColor);
		}
		else
		{
			Osd_SetTextColor(CP_WhiteColor, CP_BlueColor);
		}
	}
	else
	{
		Osd_SetTextColor(numberItem->ForeColor, numberItem->BackColor);
	}
	if (numberItem->Flags & dwiHex)
	{
		Osd_DrawHex(numberItem->XPos, numberItem->YPos, numberItem->GetValue());
	}
	else
	{
		Osd_DrawNum(numberItem->XPos, numberItem->YPos, numberItem->GetValue());
	}
#undef xPos
	#endif
}

//=========================================================================
// draw guage
void DrawOsdMenuItemGuage(BYTE itemIndex, DrawGuageType *gaugeItem)
{
	//BYTE yPos;
	itemIndex = 0;
	#if Multi_Gauge
	{
		BYTE i;
		GaugeType *gauge;
		gauge = gaugeItem->DisplayGauge;
		if (!JustShowValueFlag)
		{
			if (MenuPageIndex != FactoryMenu)
			{
				if (gauge->Flags & dwiGauge)
				{
					Osd_SetTextColor(0, gaugeItem->BackColor);
				}
			}
		}
		if (gauge)
		{
			i = 0;
#define drawItem    (gauge+i)
#define xPos    itemIndex
			while (1)
			{
				xPos = drawItem->XPos;
				if (xPos == 0)
				{
					xPos = (OsdWindowWidth - gaugeItem->Length) / 2;
				}
				//Osd_SetTextColor(0, gaugeItem->BackColor);
				Osd_DrawGuage(xPos, drawItem->YPos, gaugeItem->Length, drawItem->GetValue());
				if (drawItem->Flags & dwiEnd)
				{
					break;
				}
				i++;
			}
#undef xPos
#undef drawItem
		}
	}
	#else
#define xPos    itemIndex
	xPos = gaugeItem->XPos;
	//yPos=gaugeItem->YPos;
	if (xPos == 0)
	{
		xPos = (OsdWindowWidth - gaugeItem->Length) / 2;
	}
	if (!(CurrentMenu.Flags & mpbAdjust))
	{
		Osd_SetTextColor(gaugeItem->ForeColor, gaugeItem->BackColor);
	}
	else
	{
		Osd_SetTextColor(CP_RedColor, CP_WhiteColor);
	}
	Osd_DrawGuage(gaugeItem->XPos, gaugeItem->YPos, gaugeItem->Length, gaugeItem->GetValue());
#undef xPos
	#endif
}

//=========================================================================
// draw radio
void DrawOsdMenuItemRadioGroup(BYTE itemIndex, DrawRadioGroupType *radioItem)
{
	RadioTextType *radioText;
	radioText = radioItem->RadioText;
	if( radioText )
	{
		BYTE i = 0;
		BYTE xPos;
		BYTE tmplength = 0;
		//  itemIndex = 0xFF;
		if( radioItem->GetValue )
		{
			itemIndex = radioItem->GetValue();
		}
#define drawItem    (radioText+i)
		while( 1 )
		{
			if( drawItem->DisplayText )
			{
				xPos = drawItem->XPos;
				if( xPos == 0 )
				{
					if( MenuPageIndex == FactoryMenu )
						xPos = ( OsdWindowWidth - strlen( drawItem->DisplayText() ) + 1 ) / 2;
				}
				if( drawItem->Flags & dwiRadioGroup )
				{
					#if Hotkey_ECO_Text_Enable
					if(MenuPageIndex == HotKeyECOMenu)
						//Osd_SetTextColor( radioItem->ForeColor, radioItem->BackColor );
						Osd_SetTextMonoColor(5, 0x0E);
					else
					#endif
						Osd_Set256TextColor( radioItem->ForeColor, radioItem->BackColor );
				}
				if ( MenuPageIndex == FactoryMenu
			        #if EN_ShowInfoUnderBurinInMenu
				        || MenuPageIndex == BurninMenu
			        #endif
				   )
				{
					Osd_DrawRealStr_F( xPos, drawItem->YPos, drawItem->DisplayText() );
				}
				/*
				else if(MenuPageIndex == MainMenu && (drawItem->Flags & dwiMainTitle))
				{
					tmplength = *( drawItem->DisplayText() + 1 );
					if(itemIndex != MenuItemIndex)
						break;
					xPos = (MAIN_MENU_H_SIZE - tmplength + 1) / 2;
					Osd_DrawPropStr( xPos, drawItem->YPos, drawItem->DisplayText() );
				}*/
				//================ 重画字体，图标和字体能同时选中=================
				else if(MenuPageIndex == MainMenu	&& (drawItem->Flags & dwiMainTitle))
				{
					if(itemIndex == MenuItemIndex)
					{
						Osd_Set256TextColor(F_DRAKRED_B_BLACKRED, Color_2);
					}
					else
					{
						Osd_Set256TextColor(F_WHITE_B_BLACK, Color_2);
					}
					if(itemIndex >= 0 && itemIndex <= 5)
					{
						Osd_DrawContinuesChar(drawItem->XPos, drawItem->YPos, SpaceFont, 3);
						Osd_DrawPropStr(drawItem->XPos, drawItem->YPos, drawItem->DisplayText());
					}
				}
				//=================================================================
				else
				{
					if( drawItem->Flags & dwiCenterArrowAlign )
					{
						tmplength = *( drawItem->DisplayText() + 1 );
						xPos = (drawItem->XPos + CENTER_ALIGN_STARTPOS) + (CENTER_ALIGN_LEN - tmplength + 1) / 2;
						Osd_DrawCharDirect( drawItem->XPos + CENTER_ALIGN_STARTPOS, drawItem->YPos, MonoMark_Left);
						Osd_DrawCharDirect( drawItem->XPos + CENTER_ALIGN_ENDPOS, drawItem->YPos, MonoMark_Right);
						#if ENABLE_OVER_SCAN//1//Eson20130116
						if ( drawItem->DisplayText == ExpansionValueText)
							DynamicLoadFont_RatioStatus();
						#endif
					}
					else if( drawItem->Flags & dwiCenterText )
					{
						tmplength = *( drawItem->DisplayText() + 1 );
						xPos = (HOT_MENU_H_SIZE - tmplength + 1) / 2;
						//    xPos = (drawItem->XPos+CENTER_ALIGN_STARTPOS)+(CENTER_ALIGN_LEN-tmplength+1)/2;
					}
					Osd_DrawPropStr( xPos, drawItem->YPos, drawItem->DisplayText() );
				}
			}
			if( drawItem->Flags & dwiEnd )
			{
				break;
			}
			i++;
		}
#undef drawItem
	}
}

void DrawOsdSubMenuItemValue( BYTE itemIndex, DrawValueType *valueItem )
{
	if( valueItem->DrawNumber )
	{
		DrawOsdMenuItemNumber( itemIndex, valueItem->DrawNumber );
	}
	if( valueItem->DrawGuage )
	{
		DrawOsdMenuItemGuage( itemIndex, valueItem->DrawGuage );
	}
	if( valueItem->DrawRadioGroup )
	{
		DrawOsdMenuItemRadioGroup( itemIndex, valueItem->DrawRadioGroup );
	}
}

void DrawOsdSubMenuItem( BYTE itemIndex, MenuItemType *menuItem )
{
	if( menuItem->Flags & mibInvisible )
		return;
	#if CHIP_ID>=CHIP_TSUMC
	if( menuItem->Flags & mibDVIDisable && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3 ) ) //121128 Modify
	#else
	if( menuItem->Flags & mibDVIDisable && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ) ) //121128 Modify
	#endif
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#if FreeSyncMenu_Enable
	else if( menuItem->Flags & mibFreeSyncDisable  && (SrcInputType != Input_HDMI) )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	else if( menuItem->Flags & mibUserColor  && ( UserPrefColorTemp != CTEMP_USER )
         #if PresetMode_Enable
	         && ( UserPrefColorTemp_Preset != CTEMP_USER )
         #endif
	       )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
	else if( menuItem->Flags & mibODDisable && ( Disabe_Overdrive_Item ) )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	else if( menuItem->Flags & mibDCRDisable && ( UserPrefDcrMode ) )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	else if( menuItem->Flags & mibStdEnable && ( UserPrefECOMode != ECO_Standard )
         #if PresetMode_Enable
	         && UserPrefECOMode != ECO_Preset
         #endif
	       )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#if CT_sRGB_ENABLE
	else if( menuItem->Flags & mibsRGBDisable && ( UserPrefColorTemp == CTEMP_SRGB && UserPrefECOMode == ECO_Standard ) )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	#if Enable_Expansion
	#if ENABLE_OVER_SCAN	//121228 Modify
	//else if( menuItem->Flags & mibExpansionDisable && INPUT_IS_NATIVE_TIMING())
	#else
	else if( menuItem->Flags & mibExpansionDisable && !ExpansionFlag )
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	#endif
	#if  LowBlueLightType == LowBlueLight_SharpFunc
	else if(( (MIB_LOWBLUEDISABLE & menuItem->Flags) && (UserPrefColorTemp != CTEMP_LowBlue)))
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	#if Disable_VgaToAdjustVolume
	else if(( (mibAutioDisable & menuItem->Flags) && CURRENT_INPUT_IS_VGA()))
		Osd_Set256TextColor( CP_DisableItem, Color_2 );
	#endif
	else
		Osd_Set256TextColor( menuItem->ForeColor, menuItem->BackColor );
	DrawOsdMenuItemText( itemIndex, menuItem );
	DrawOsdSubMenuItemValue( itemIndex, &( menuItem->DisplayValue ) );
}

void DrawOsdSubMenu( BYTE menupage )
{
	BYTE i;
	if( CurrentMenuItem.Flags & mibFactoryItem ) // Do not Display Factory Menu
		return;
	for( i = 0; i < tblMenus[menupage].ItemCount; i++ )
		DrawOsdSubMenuItem( i, &tblMenus[menupage].MenuItems[i] );
}





Bool DrawTimingInfo(void)
{
	WORD xdata freq;
	BYTE xdata VFreqProp[4];
	WORD xdata HDisplay = StandardModeWidth;//mStar_ReadWord(SPRHDC_H) & 0xfffe;
	WORD xdata VDisplay = StandardModeHeight;//mStar_ReadWord(SPRVDC_H);
	BYTE xdata ResolutionProp[27] = {0};		//28改27
	BYTE xdata TempPropData[5];
	BYTE xdata number, i, j, Vnumber;
	WORD xdata FontWide = 0;
	Osd_Set256TextColor( CP_UnselectItem, Color_2 );
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100~0x1FF
	Osd_DynamicLoadFont(ResoulationAddress, ResolutionProp, 27); //20180109  �޸ķֱ����л���1152x864 60hz ���������
	OSD_FONT_HI_ADDR_CLR_TO_0();
	for (Vnumber = 0; Vnumber < 8; Vnumber++)
		VFreqProp[Vnumber] = 0x01; //space
	for (number = 0; number < 28; number++)
		ResolutionProp[number] = 0x01; //space
	#if (ENABLE_FREESYNC) // C3583 use adaptive sync can't show FreeSync
	Vnumber = 0;
	if(IS_HDMI_FREESYNC() || IS_DP_FREESYNC())
	{
	}
	else
	#endif
	{
		//---V Freq--------------------------------------------------------------
		FontWide = 0;
		freq = VFreq(HFreq(SrcHPeriod), SrcVTotal);
		// 120424 coding addition for intermode vfreq information
		if(CURRENT_SOURCE_IS_INTERLACE_MODE())
		{
			freq *= 2;
		}
		if( ( freq % 10 ) >= 5 )	//120105 Modify for TPV Request
		{
			freq = ( freq + 10 ) / 10;
		}
		else
		{
			freq = freq / 10;
		}
		if (freq >= 100)
		{
			Vnumber = 3;
			VFreqProp[0] = (freq / 100) + 0x30;
			VFreqProp[1] = ((freq % 100) / 10) + 0x30;
			VFreqProp[2] = (freq % 10) + 0x30;
		}
		else
		{
			Vnumber = 2;
			VFreqProp[0] = (freq / 10) + 0x30;
			VFreqProp[1] = (freq % 10) + 0x30;
		}
	}
//---Resoulation--------------------------------------------------------------
	FontWide = 0;
	//120925 Modify
	#if CHIP_ID == CHIP_TSUMC || CHIP_ID == CHIP_TSUMD|| CHIP_ID == CHIP_TSUM9||CHIP_ID == CHIP_TSUMF//130603 miff
	HDisplay = SC0_READ_IMAGE_WIDTH();
	#else
	if(CURRENT_INPUT_IS_DISPLAYPORT())
	{
		HDisplay = 2 * SC0_READ_IMAGE_WIDTH();
	}
	else
	{
		HDisplay = SC0_READ_IMAGE_WIDTH();
	}
	#endif
	#if ENABLE_DUAL_LINK		//130108_23 Henrya
	if(CURRENT_INPUT_IS_DVI())
		if(msReadByte(SC0_A6)&BIT1)
			HDisplay = 2 * SC0_READ_IMAGE_WIDTH();
	#endif
	if( abs( HDisplay - 720 ) < 5 )
		HDisplay = 720;
	else if( abs( HDisplay - 1280 ) < 5 )
		HDisplay = 1280;
	else if( abs( HDisplay - 1920 ) < 5 )
		HDisplay = 1920;
	else if(( HDisplay == 1366 ) && ( StandardModeGroup == Res_1360x768 ) )
		HDisplay = 1360;
	if (HDisplay >= 1000)
	{
		number = 4;
		TempPropData[0] = (HDisplay / 1000) + 0x30;
		TempPropData[1] = ((HDisplay % 1000) / 100) + 0x30;
		TempPropData[2] = ((HDisplay % 100) / 10) + 0x30;
		TempPropData[3] = (HDisplay % 10) + 0x30;
	}
	else
	{
		number = 3;
		TempPropData[0] = (HDisplay / 100) + 0x30;
		TempPropData[1] = ((HDisplay % 100) / 10) + 0x30;
		TempPropData[2] = (HDisplay % 10) + 0x30;
	}
	for ( i = 0; i < number; i++ )
	{
		if(TempPropData[i] >= 0x30 && TempPropData[i] <= 0x39) //0~9
			ResolutionProp[i] = TempPropData[i] - 0x1F;
		if (TempPropData[i] == 0x31) // 1
			FontWide += 3;
		else// 0~9
			FontWide += 8;
		FontWide += 1;
	}
	ResolutionProp[i++] = 0x01; //space
	FontWide += 2;
	FontWide += 1;
	ResolutionProp[i++] = 0x39; //X
	FontWide += 9;
	FontWide += 1;
	//120925 Modify
	if( StandardModeGroup == Res_720x480 && ( CURRENT_SOURCE_IS_INTERLACE_MODE() ) && !CURRENT_INPUT_IS_VGA() )
		VDisplay = 480;
	else if ( StandardModeGroup == Res_720x576 )
		VDisplay = 576;
	else if( StandardModeGroup == Res_1920x1080 )
		VDisplay = 1080;
	else if( !CURRENT_INPUT_IS_VGA() && !( CURRENT_SOURCE_IS_INTERLACE_MODE() ) )
		VDisplay = SC0_READ_AUTO_HEIGHT();
	else
	{
		if(DecVScaleFlag)
			VDisplay = SC0_READ_IMAGE_HEIGHT() - DecVScaleValue;
		else
			VDisplay = SC0_READ_IMAGE_HEIGHT();
	}
	if (VDisplay >= 1000)
	{
		number = 4;
		TempPropData[0] = (VDisplay / 1000) + 0x30;
		TempPropData[1] = ((VDisplay % 1000) / 100) + 0x30;
		TempPropData[2] = ((VDisplay % 100) / 10) + 0x30;
		TempPropData[3] = (VDisplay % 10) + 0x30;
	}
	else
	{
		number = 3;
		TempPropData[0] = (VDisplay / 100) + 0x30;
		TempPropData[1] = ((VDisplay % 100) / 10) + 0x30;
		TempPropData[2] = (VDisplay % 10) + 0x30;
	}
	for ( j = i; j < i + number; j++ )
	{
		if(TempPropData[j - i] >= 0x30 && TempPropData[j - i] <= 0x39) //0~9
			ResolutionProp[j] = TempPropData[j - i] - 0x1F;
		if (TempPropData[j - i] == 0x31) // 1
			FontWide += 3;
		else// 0~9
			FontWide += 8;
		FontWide += 1;
	}
	ResolutionProp[j++] = 0x01; //space
	FontWide += 2;
	FontWide += 1;
	ResolutionProp[j++] = 0x01; // space
	FontWide += 8;
	FontWide += 1;
	ResolutionProp[j++] = 0x01; // space
	FontWide += 8;
	FontWide += 1;
	ResolutionProp[j++] = 0x01; //space
	FontWide += 2;
	FontWide += 1;
	#if (ENABLE_FREESYNC) // C3583 use adaptive sync can't show FreeSync
	if(IS_HDMI_FREESYNC() || IS_DP_FREESYNC())
		Osd_DrawPropStr( 0x1A, TimingInfoYpos, VsyncText() );
	else
	#endif
	{
//----------------------------------VFreq
		for ( i = 0; i < Vnumber; i++, j++ )
		{
			if(VFreqProp[i] >= 0x30 && VFreqProp[i] <= 0x39) //0~9
				ResolutionProp[j] = VFreqProp[i] - 0x1F;
			if (VFreqProp[i] == 0x31) // 1
				FontWide += 3;
			else// 0~9
				FontWide += 8;
			FontWide += 1;
		}
		ResolutionProp[j++] = 0x29; //H
		FontWide += 8;
		FontWide += 1;
		ResolutionProp[j++] = 0x5B; //z
		FontWide += 8;
		FontWide += 1;
		ResolutionProp[j++] = 0x01; //space
		FontWide += 2;
		FontWide += 1;
		ResolutionProp[j++] = 0x01; //space
		FontWide += 2;
		FontWide += 1;
		ResolutionProp[j++] = 0x01; //space
		FontWide += 2;
		FontWide += 1;
	}
//----------------------------------------------------------------
	ResolutionProp[j] = 0x00; //End
	if(((HDisplay == 640 || HDisplay == 720) && (VDisplay == 480 || VDisplay == 350 || VDisplay == 400)) || (HDisplay == 800 && VDisplay == 600))
		FontWide = (FontWide) / 12;
	else
		FontWide = (FontWide + 11) / 12;
	OSD_FONT_HI_ADDR_SET_BIT8();//0x100~0x1FF
	Osd_DynamicLoadFont(ResoulationAddress, ResolutionProp, j);
	OSD_FONT_HI_ADDR_CLR_TO_0();
	ResolutionProp[0] = ResoulationAddress;
	ResolutionProp[1] = FontWide - 1;
	Osd_Set256TextColor(F_WHITE_B_BLACKRED, Color_2);
	OSD_TEXT_HI_ADDR_SET_BIT8(); //enable bit 8
	Osd_DrawPropStr(49, 1, ResolutionProp);
	OSD_TEXT_HI_ADDR_CLR_TO_0();
	return TRUE;
}

BYTE GetPrevItem(MenuItemType *menuItem)
{
	signed char i = 0;
	if (MenuItemIndex)
	{
		i = MenuItemIndex;
		for (; i > 0;) //poro:2008-09-03,for Envision OSD issue...
		{
			i--;
			i = i % 255;
			#if INPUT_TYPE==INPUT_1D1H1DP||INPUT_TYPE==INPUT_1A2D||INPUT_TYPE==INPUT_1A1D1H||INPUT_TYPE == INPUT_1A2H1DP||INPUT_TYPE==INPUT_2A2D||INPUT_TYPE==INPUT_1A1H||INPUT_TYPE==INPUT_1A2H||INPUT_TYPE==INPUT_1A1D1H1DP||INPUT_TYPE==INPUT_1A1D1DP ||INPUT_TYPE==INPUT_1A1H1DP|| INPUT_TYPE==INPUT_2H	//131113 fay
			#if CHIP_ID>=CHIP_TSUMC
			if ((menuItem[i].Flags & mibDVIDisable) && (SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3  ))
			#else
			if ((menuItem[i].Flags & mibDVIDisable) && (SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ))
			#endif
			#else
			if (menuItem[i].Flags & mibDVIDisable && SrcInputType == Input_Digital)
			#endif
			{
				continue;
			}
			#if CT_sRGB_ENABLE
			if (menuItem[i].Flags & mibsRGBDisable && (UserPrefColorTemp == CTEMP_SRGB))
			{
				continue;
			}
			#endif
			if ( menuItem[i].Flags & mibUserColor && ( UserPrefColorTemp != CTEMP_USER )
		        #if PresetMode_Enable
			        && ( UserPrefColorTemp_Preset != CTEMP_USER )
		        #endif
			   )//jeff 1112		//120215 Modify
			{
				continue;
			}
			if (menuItem[i].Flags & mibStdEnable && (UserPrefECOMode != ECO_Standard)
		        #if PresetMode_Enable
			        && UserPrefECOMode != ECO_Preset
		        #endif
			   )
			{
				continue;
			}
			if (menuItem[i].Flags & mibDCRDisable && (UserPrefDcrMode))
			{
				continue;
			}
			#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
			if (menuItem[i].Flags & mibODDisable && (Disabe_Overdrive_Item))
			{
				continue;
			}
			#endif
			if (menuItem[i].Flags & mibFactoryItem && !FactoryModeFlag)
			{
				continue;
			}
			#if Enable_Expansion
			#if ENABLE_OVER_SCAN	//121228 Modify
			//if( menuItem[i].Flags & mibExpansionDisable && INPUT_IS_NATIVE_TIMING())
			#else
			if( menuItem[i].Flags & mibExpansionDisable && ( !ExpansionFlag ) )
			{
				continue;
			}
			#endif
			#endif
			#if  LowBlueLightType == LowBlueLight_SharpFunc
			if(( (MIB_LOWBLUEDISABLE & menuItem[i].Flags) && (UserPrefColorTemp != CTEMP_LowBlue)))
				continue;
			#endif
			#if Disable_VgaToAdjustVolume
			if(( (mibAutioDisable & menuItem[i].Flags) && CURRENT_INPUT_IS_VGA()))
				continue;
			#endif
			if (menuItem[i].Flags & mibSelectable && !(menuItem[i].Flags & mibDrawValue))
			{
				return i;
			}
		}
	}
	i = MenuItemCount;
	for ( ; i >= 0; )
	{
		i--;
		#if INPUT_TYPE==INPUT_1D1H1DP||INPUT_TYPE==INPUT_1A2D||INPUT_TYPE==INPUT_1A1D1H||INPUT_TYPE==INPUT_2A2D||INPUT_TYPE == INPUT_1A2H1DP||INPUT_TYPE==INPUT_1A1H||INPUT_TYPE==INPUT_1A2H||INPUT_TYPE==INPUT_1A1D1H1DP||INPUT_TYPE==INPUT_1A1D1DP ||INPUT_TYPE==INPUT_1A1H1DP || INPUT_TYPE==INPUT_2H	//131113 fay
		#if CHIP_ID>=CHIP_TSUMC
		if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3 ))
		#else
		if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ))
		#endif
		#else
		if (menuItem[i].Flags & mibDVIDisable && SrcInputType == Input_Digital)
		#endif
		{
			continue;
		}
		#if FreeSyncMenu_Enable
		if (menuItem[i].Flags & mibFreeSyncDisable && (SrcInputType != Input_HDMI))
		{
			continue;
		}
		#endif
		#if CT_sRGB_ENABLE
		if (menuItem[i].Flags & mibsRGBDisable && (UserPrefColorTemp == CTEMP_SRGB))
		{
			continue;
		}
		#endif
		if (menuItem[i].Flags & mibUserColor && ( UserPrefColorTemp != CTEMP_USER )
	        #if PresetMode_Enable
		        && ( UserPrefColorTemp_Preset != CTEMP_USER )
	        #endif
		   )		//120215 Modify
		{
			continue;
		}
		if (menuItem[i].Flags & mibStdEnable && (UserPrefECOMode != ECO_Standard)
	        #if PresetMode_Enable
		        && UserPrefECOMode != ECO_Preset
	        #endif
		   )
		{
			continue;
		}
		if (menuItem[i].Flags & mibDCRDisable && (UserPrefDcrMode))
		{
			continue;
		}
		#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
		if (menuItem[i].Flags & mibODDisable && (Disabe_Overdrive_Item))
		{
			continue;
		}
		#endif
		if (menuItem[i].Flags & mibFactoryItem && !FactoryModeFlag)
		{
			continue;
		}
		#if Enable_Expansion
		#if ENABLE_OVER_SCAN	//121228 Modify
		//if( menuItem[i].Flags & mibExpansionDisable && INPUT_IS_NATIVE_TIMING())
		#else
		if( menuItem[i].Flags & mibExpansionDisable && ( !ExpansionFlag ) )
		{
			continue;
		}
		#endif
		#endif
		#if  LowBlueLightType == LowBlueLight_SharpFunc
		if(( (MIB_LOWBLUEDISABLE & menuItem[i].Flags) && (UserPrefColorTemp != CTEMP_LowBlue)))
			continue;
		#endif
		#if Disable_VgaToAdjustVolume
		if(( (mibAutioDisable & menuItem[i].Flags) && CURRENT_INPUT_IS_VGA()))
			continue;
		#endif
		if (menuItem[i].Flags & mibSelectable && !(menuItem[i].Flags & mibDrawValue))
		{
			return i;
		}
	}
	return MenuItemIndex;
}

BYTE GetNextItem(MenuItemType *menuItem)
{
	BYTE i = 0, firsttime ;
	if (MenuItemIndex < MenuItemCount - 1)
	{
		i = MenuItemIndex;
		for ( ; i < MenuItemCount - 1;)
		{
			i++;
			#if INPUT_TYPE==INPUT_1D1H1DP||INPUT_TYPE==INPUT_1A2D||INPUT_TYPE==INPUT_1A1D1H||INPUT_TYPE == INPUT_1A2H1DP||INPUT_TYPE==INPUT_2A2D||INPUT_TYPE==INPUT_1A1H||INPUT_TYPE==INPUT_1A2H||INPUT_TYPE==INPUT_1A1D1H1DP||INPUT_TYPE==INPUT_1A1D1DP ||INPUT_TYPE==INPUT_1A1H1DP|| INPUT_TYPE==INPUT_2H	//131113 fay
			#if CHIP_ID>=CHIP_TSUMC
			if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3))
			#else
			if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ))
			#endif
			#else
			if (menuItem[i].Flags & mibDVIDisable && SrcInputType == Input_Digital)
			#endif
			{
				continue;
			}
			#if FreeSyncMenu_Enable
			if (menuItem[i].Flags & mibFreeSyncDisable && (SrcInputType != Input_HDMI))
			{
				continue;
			}
			#endif
			#if CT_sRGB_ENABLE
			if (menuItem[i].Flags & mibsRGBDisable && (UserPrefColorTemp == CTEMP_SRGB))
			{
				continue;
			}
			#endif
			if (menuItem[i].Flags & mibUserColor && ( UserPrefColorTemp != CTEMP_USER )
		        #if PresetMode_Enable
			        && ( UserPrefColorTemp_Preset != CTEMP_USER )
		        #endif
			   )		//120215 Modify
			{
				continue;
			}
			if (menuItem[i].Flags & mibStdEnable && (UserPrefECOMode != ECO_Standard)
		        #if PresetMode_Enable
			        && UserPrefECOMode != ECO_Preset
		        #endif
			   )
			{
				continue;
			}
			if (menuItem[i].Flags & mibDCRDisable && (UserPrefDcrMode))
			{
				continue;
			}
			#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
			if (menuItem[i].Flags & mibODDisable && (Disabe_Overdrive_Item))
			{
				continue;
			}
			#endif
			if (menuItem[i].Flags & mibFactoryItem && !FactoryModeFlag)
			{
				continue;
			}
			#if Enable_Expansion
			#if ENABLE_OVER_SCAN	//121228 Modify
			//if( menuItem[i].Flags & mibExpansionDisable && INPUT_IS_NATIVE_TIMING())
			#else
			if( menuItem[i].Flags & mibExpansionDisable && ( !ExpansionFlag ) )
			{
				continue;
			}
			#endif
			#endif
			#if  LowBlueLightType == LowBlueLight_SharpFunc
			if(( (MIB_LOWBLUEDISABLE & menuItem[i].Flags) && (UserPrefColorTemp != CTEMP_LowBlue)))
				continue;
			#endif
			#if Disable_VgaToAdjustVolume
			if(( (mibAutioDisable & menuItem[i].Flags) && CURRENT_INPUT_IS_VGA()))
				continue;
			#endif
			if (menuItem[i].Flags & mibSelectable && !(menuItem[i].Flags & mibDrawValue))
			{
				return i;
			}
		}
	}
	i = 0;
	firsttime = 1;
	for (; i < MenuItemIndex;)
	{
		{
			if(!firsttime)
				i++;
			else
				firsttime = 0;
		}
		#if INPUT_TYPE==INPUT_1D1H1DP||INPUT_TYPE==INPUT_1A2D||INPUT_TYPE==INPUT_1A1D1H||INPUT_TYPE == INPUT_1A2H1DP||INPUT_TYPE==INPUT_2A2D||INPUT_TYPE==INPUT_1A1H||INPUT_TYPE==INPUT_1A2H||INPUT_TYPE==INPUT_1A1D1H1DP||INPUT_TYPE==INPUT_1A1D1DP||INPUT_TYPE==INPUT_1A1H1DP || INPUT_TYPE==INPUT_2H	//131113 fay
		#if CHIP_ID>=CHIP_TSUMC
		if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3 ))
		#else
		if ((menuItem[i].Flags & mibDVIDisable) && ( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport ))
		#endif
		#else
		if (menuItem[i].Flags & mibDVIDisable && SrcInputType == Input_Digital)
		#endif
		{
			continue;
		}
		#if CT_sRGB_ENABLE
		if (menuItem[i].Flags & mibsRGBDisable && (UserPrefColorTemp == CTEMP_SRGB))
		{
			continue;
		}
		#endif
		if (menuItem[i].Flags & mibUserColor && (( UserPrefColorTemp != CTEMP_USER )
	        #if PresetMode_Enable
		        && ( UserPrefColorTemp_Preset != CTEMP_USER )
	        #endif
		                                        ))		//120215 Modify
		{
			continue;
		}
		if (menuItem[i].Flags & mibStdEnable && (UserPrefECOMode != ECO_Standard)
	        #if PresetMode_Enable
		        && UserPrefECOMode != ECO_Preset
	        #endif
		   )
		{
			continue;
		}
		if (menuItem[i].Flags & mibDCRDisable && (UserPrefDcrMode))
		{
			continue;
		}
		#if (ENABLE_DUAL_LINK)&&(ENABLE_RTE)		//130402 Modify
		if (menuItem[i].Flags & mibODDisable && (Disabe_Overdrive_Item))
		{
			continue;
		}
		#endif
		if (menuItem[i].Flags & mibFactoryItem && !FactoryModeFlag)
		{
			continue;
		}
		#if Enable_Expansion
		#if ENABLE_OVER_SCAN	//121228 Modify
		//if( menuItem[i].Flags & mibExpansionDisable && INPUT_IS_NATIVE_TIMING())
		#else
		if( menuItem[i].Flags & mibExpansionDisable && ( !ExpansionFlag ) )
		{
			continue;
		}
		#endif
		#endif
		#if  LowBlueLightType == LowBlueLight_SharpFunc
		if(( (MIB_LOWBLUEDISABLE & menuItem[i].Flags) && (UserPrefColorTemp != CTEMP_LowBlue)))
			continue;
		#endif
		#if Disable_VgaToAdjustVolume
		if(( (mibAutioDisable & menuItem[i].Flags) && CURRENT_INPUT_IS_VGA()))
			continue;
		#endif
		if (menuItem[i].Flags & mibSelectable && !(menuItem[i].Flags & mibDrawValue))
		{
			return i;
		}
	}
	return MenuItemIndex;
}



#if 1//20121105 Move MENUTEMP.c
// menuPageIndex => prev page index
// MenuPageIndex => current page index
#if 1
BYTE GetMenuItemIndex(BYTE menuPageIndex)
{
	//�����˵��˳������˵�ʱ����Ӧ��ITEM
	if( MenuPageIndex == MainMenu )
	{
		if( menuPageIndex == OSD_BriContrastMenu )
		{
			return MAIN_BriContrast_ITEM;
		}
		else if( menuPageIndex == PictureMenu )
		{
			return MAIN_Picture_ITEM;
		}
		else if( menuPageIndex == RGBColorMenu )
		{
			return MAIN_RGBColor_ITEM;
		}
		else if( menuPageIndex == OsdMenu )
		{
			return MAIN_Osd_ITEM;
		}
		else if( menuPageIndex == SettingMenu )
		{
			return MAIN_Setting_ITEM;
		}
		else if( menuPageIndex == OSD_MiscMenu )
		{
			return MAIN_Misc_ITEM;
		}
		else if( menuPageIndex == LanguageMenu )
		{
			return MAIN_Setting_ITEM;
		}
	}
	//�����˵��˳��������˵�ʱ����Ӧ��ITEM
	else if( MenuPageIndex == OSD_BriContrastMenu )
	{
		if( UserPrefDcrMode )
		{
			#if ENABLE_RTE && !PresetMode_Enable//120502 Modify
			if( menuPageIndex == OverdriveMenu)
				return BriContrast_Overdrive_ITEM;
			else
			#endif
				return BriContrast_DCR_ITEM;			//110304 Modify
		}
		#if CT_sRGB_ENABLE
		else if( menuPageIndex == MainMenu && UserPrefColorTemp == CTEMP_SRGB )
		{
			return BriContrast_ECO_ITEM;			//110301 Modify
		}
		#endif
		else if( menuPageIndex == MainMenu && UserPrefECOMode != ECO_Standard
	         #if PresetMode_Enable
		         && UserPrefECOMode != ECO_Preset
	         #endif
		       )
		{
			return BriContrast_ECO_ITEM;
		}
		else if( menuPageIndex == ECOMenu )
		{
			return BriContrast_ECO_ITEM;
		}
		#if Enable_Gamma
		#if PresetMode_Enable
		else if( menuPageIndex == GammaMenu )
		{
			return BriContrast_DCR_ITEM;
		}
		#else
		else if( menuPageIndex == GammaMenu )
		{
			return BriContrast_GAMMA_ITEM;
		}
		#endif
		#endif
		else if( menuPageIndex == DCRMenu )
		{
			return BriContrast_DCR_ITEM;
		}
		#if ENABLE_RTE  && !PresetMode_Enable
		else if( menuPageIndex == OverdriveMenu )
		{
			return BriContrast_Overdrive_ITEM;
		}
		#endif
		else if( menuPageIndex == BrightnessMenu )
		{
			return BriContrast_BRIGHTNESS_ITEM;
		}
		else if( menuPageIndex == ContrastMenu )
		{
			return BriContrast_CONTRAST_ITEM;
		}
	}
	else if( MenuPageIndex == PictureMenu )
	{
		#if Enable_Func_AdjExpansion
		#if CHIP_ID>=CHIP_TSUMC
		if( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport || SrcInputType == Input_Displayport3) //121128 Modify
		#else
		if( SrcInputType == Input_Digital || SrcInputType == Input_Digital2 || SrcInputType == Input_Displayport )  //121128 Modify
		#endif
		{
			//return Picture_IMAGERATIO_ITEM;
		}
		else
		#endif
		{
			if( menuPageIndex == HPositionMenu )
			{
				return Picture_HPOSITION_ITEM;
			}
			else if( menuPageIndex == VPositionMenu )
			{
				return Picture_VPOSITION_ITEM;
			}
			else if( menuPageIndex == ClockMenu )
			{
				return Picture_CLOCK_ITEM;
			}
			else if( menuPageIndex == FocusMenu )
			{
				return Picture_PHASE_ITEM;
			}
			/*#if Enable_Func_AdjExpansion
			else if( menuPageIndex == ExpansionMenu )
			{
				return Picture_IMAGERATIO_ITEM;
			}*/
			#endif
		}
	}
	else if( MenuPageIndex == RGBColorMenu )
	{
		if( menuPageIndex == RedMenu )
		{
			return RGB_Red_Item;
		}
		else if( menuPageIndex == GreenMenu )
		{
			return RGB_Green_Item;
		}
		else if( menuPageIndex == BlueMenu )
		{
			return RGB_Blue_Item;
		}
		#if LowBlueLightType==LowBlueLight_ColorTemp || LowBlueLightType==LowBlueLight_SharpFunc
		else if( menuPageIndex == LowBlueLightMenu )
		{
			return RGB_LowBlueLigth_Item;
		}
		#endif
	}
	else if( MenuPageIndex == OsdMenu )
	{
		if( menuPageIndex == LanguageMenu )
		{
			return OSD_LANGUAGE_ITEM;
		}
		#if OsdAdjustHVPos_Enable
		else if( menuPageIndex == OsdHPositionMenu )
		{
			return OSD_HPOSITION_ITEM;
		}
		else if( menuPageIndex == OsdVPositionMenu )
		{
			return OSD_VPOSITION_ITEM;
		}
		#endif
		else if( menuPageIndex == OsdTimeOutMenu )
		{
			return OSD_TIMEOUT_ITEM;
		}
		else if( menuPageIndex == TransparenceMenu )
		{
			return OSD_TRANSPARENCE_ITEM;
		}
	}
	else if( MenuPageIndex == SettingMenu )
	{
		if(SrcInputType != Input_VGA)
			return Setting_RESTR_ITEM;
		#ifdef OffPower
		else if( menuPageIndex == OffTimerMenu )
		{
			return Setting_OffPower_ITEM;
		}
		#endif
		#if AboutDSUBFunc_Enable
		else
			return Setting_AUTOCONFIG_ITEM;
		#endif
	}
	#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
	else if( MenuPageIndex == InputSelectMenu )
	{
		#if ENABLE_AutoDetech
		#if INPUT_TYPE == INPUT_2H||INPUT_TYPE == INPUT_1D1H1DP
		if (UserPrefInputSelectType == INPUT_PRIORITY_AUTO)
			return 0;
		#else
		if (UserPrefInputSelectType == INPUT_PRIORITY_AUTO)
			return 0;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_VGA)
			return 1;
		#endif
		#if INPUT_TYPE == INPUT_1A1H  //110424 Modify
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 2;
		#elif INPUT_TYPE == INPUT_1A2H
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
		{
			return 2;
		}
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
		{
			return 3;
		}
		#elif INPUT_TYPE == INPUT_2H
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 2;
		#elif INPUT_TYPE == INPUT_1A1D1H
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 2;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 3;
		#elif INPUT_TYPE == INPUT_1A1D1DP	//130924 xiandi
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 2;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DP)
			return 3;
		#elif INPUT_TYPE == INPUT_1D1H1DP	//130924 xiandi
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 2;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DP)
			return 3;
		#elif INPUT_TYPE == INPUT_1A1H1DP	//130924 xiandi
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 2;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DP)
			return 3;
		#elif INPUT_TYPE == INPUT_1A1DP	//20151126 Alpha
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DP)
			return 2;
		#elif (INPUT_TYPE == INPUT_1A1D1H1DP||INPUT_TYPE == INPUT_1A2H1DP)				//130105_22 Henry
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 2;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_HDMI)
			return 3;
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DP)
			return 4;
		#elif INPUT_TYPE == INPUT_1A1D						//130128 Modify
		else if (UserPrefInputSelectType == INPUT_PRIORITY_DVI)
			return 2;
		#endif
		#else
		#if ENABLE_VGA
		if (UserPrefInputType == INPUT_PRIORITY_VGA)
			return 0;
		#endif
		#if INPUT_TYPE == INPUT_1A1H  //110424 Modify
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 1;
		#elif INPUT_TYPE == INPUT_1A2H
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
		{
			return 1;
		}
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
		{
			return 2;
		}
		#elif INPUT_TYPE == INPUT_2H
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 0;
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 1;
		#elif INPUT_TYPE == INPUT_1A1D1H
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 2;
		#elif INPUT_TYPE == INPUT_1A1D1DP	//130924 xiandi
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 2;
		#elif INPUT_TYPE == INPUT_1D1H1DP	//130924 xiandi
		if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 0;
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 2;
		#elif INPUT_TYPE == INPUT_1A1H1DP	//130924 xiandi
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 2;
		#elif INPUT_TYPE == INPUT_1A1DP	//20151126 Alpha
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 2;
		#elif (INPUT_TYPE == INPUT_1A1D1H1DP)				//130105_22 Henry
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 2;
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 3;
		#elif (INPUT_TYPE == INPUT_1A2H1DP)				//130105_22 Henry
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI)
			return 1;
		else if (UserPrefInputType == INPUT_PRIORITY_HDMI2ND)
			return 2;
		else if (UserPrefInputType == INPUT_PRIORITY_DP)
			return 3;
		#elif INPUT_TYPE == INPUT_1A1D						//130128 Modify
		else if (UserPrefInputType == INPUT_PRIORITY_DVI)
			return 1;
		#endif
		#endif
	}
	#endif
	else if( MenuPageIndex == OSD_MiscMenu )
	{
		#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
		if( menuPageIndex == InputSelectMenu )
		{
			return Misc_InputSource_ITEM;
		}
		#endif
		#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
		#if AudioFunc
		#if EANBLE_MUTE_ON_OFF
		else if( menuPageIndex == MuteMenu )
		{
			return Misc_Mute_ITEM;
		}
		#endif
		else if( menuPageIndex == VolumeMenu )
		{
			return Misc_Volume_ITEM;
		}
		#endif
		#else
		#if AudioFunc
		#if EANBLE_MUTE_ON_OFF
		if( menuPageIndex == MuteMenu )
		{
			return Misc_Mute_ITEM;
		}
		#endif
		else if( menuPageIndex == VolumeMenu )
		{
			return Misc_Volume_ITEM;
		}
		#endif
		#endif
		#if Enable_Adjust_SharpnessMenu
		else if( menuPageIndex == SharpnessMenu )
		{
			return Misc_Sharpness_ITEM;
		}
		#endif
		#if ENABLE_RTE  && PresetMode_Enable
		else if( menuPageIndex == OverdriveMenu )
		{
			return Misc_Overdrive_ITEM;
		}
		#endif
		#if  DDCCI_ENABLE && DDCCCIMenu_Enable
		else if( menuPageIndex == DDCCIMenu )
		{
			return Misc_DDCCI_ITEM;
		}
		#endif
		#if (LowBlueLightType==LowBlueLight_Misc_Guage)||(LowBlueLightType==LowBlueLight_Misc_Group)
		else if( menuPageIndex == LowBlueLightMenu)
		{
			return Misc_LowBlueLigth_Item;
		}
		#endif
		#if  FreeSyncMenu_Enable
		else if( menuPageIndex == FreeSyncMenu )
		{
			return Misc_FreeSync_ITEM;
		}
		#endif
	}
	#if !AdjustLanguageFunction
	else if(MenuPageIndex == LanguageMenu)
	{
		return UserPrefLanguage;
	}
	#endif
	return 0;
}
#endif

#if OsdHelpKeyType == OsdHelpKey_Right
#define underBlankFontWide		1
#else
#define underBlankFontWide		3
#endif

//-------------------------------------------
#define DRAK_RED_COLOR			1	//my
#define ORANGE_RED_COLOR		2	//my
#define RED_COLOR				3	//my
#define BLACK_RED_COLOR			4	//my
#define LIGHT_GREEN_COLOR		5	//my
#define BLUE_COLOR				6	//my
#define BLACK_COLOR				7	//my
#define LIGHT_GRAY_COLOR		8	//my
#define DRAK_WHITE_COLOR		9	//my

#define F_DRAKRED_B_BLACK		0x17
#define F_DRAKRED_B_BLACKRED	0x14
#define F_WHITE_B_BLACK			0x97
#define F_WHITE_B_BLACKRED		0x94
//-------------------------------------------
//============================SymbolFont=================================
#define SpaceFont		          0x01     //空白键
#define LeftTopArc                0x02     //左上弧
#define RightTopArc               0x03     //右上弧
#define LeftLowerArc              0x04     //左下弧
#define RightLowerArc             0x05     //右下弧
#define UnderscoreThick           0x06     //下横线(粗)
#define OverlineThick             0x07     //上横线(粗)
#define LeftVerticalBarThick      0x08     //左竖线(粗)
#define RightVerticalBar          0x09     //右竖线
#define LeftTopCorner             0x0A     //左上角
#define LeftVerticalBar           0x0B     //左竖线
#define RightTopCorner            0x0C     //右上角
#define RightLowerCorner          0x0D     //右下角
#define LeftLowerCorner           0x0E     //左下角
#define Underscore                0x0F     //下横线
#define Overline                  0x10     //上横线
																//0x11		空
#define CrossSymbol               0x12     //×符号
#define MinusSign                 0x13     //减号
#define PlusSign                  0x14     //加号
#define PairSymbol                0x15     //√符号
#define Triangle                  0x16     //▲三角形
#define LowerTriangle             0x17     //▼倒三角
#define LetterEN                  0x18     //字母EN
																//0x19-0x1D		空
#define LefiTriangle              0x1E     //左三角
#define RightTriangle             0x1F     //右三角
#define LetterF                   0x20     //字母F
#define NumberZero                0x21     //数字0
#define NumberOne                 0x22     //数字1
#define NumberTwo                 0x23     //数字2
#define NumberThree               0x24     //数字3
#define NumberFour                0x25     //数字4
#define NumberFive                0x26     //数字5
#define NumberSix                 0x27     //数字6
#define NumberSeven               0x28     //数字7
#define NumberEight               0x29     //数字8
#define NumberNine                0x2A     //数字9
#define LeftLacuna                0x2B     //左缺角

#define _4COLOR_ADDR			0x200
#define LT_4COLOR_FONTSIZE		0x02	

#define XPOS_START		0
#define YPOS_START		0
#define XPOS_END		0x48
#define YPOS_END		0x18

#define MENU2_XPOS_START	25
#define MENU2_YPOS_START	5
#define MENU2_YPOS_END		19
#define MENU3_XPOS_START		49

//0x2C~0x4F为二级菜单文字

void DrawOsdBackGround(void)
{
	BYTE i, j;
	//主菜单背景
	if ( MenuPageIndex == MainMenu )
	{
		//========================大背景========================
		Osd_SetTextMonoColor(BLACK_COLOR, BLACK_COLOR);
		for (i = 0; i <= OsdWindowHeight - 1; i++)
		{
			Osd_DrawContinuesChar( XPOS_START, i, SpaceFont, OsdWindowWidth);
		}
		/*cher = 0x00;
		for (i=0x04; i<0x13; i+=2)
		{
			for(j=0x10; j<0x40; j+=2)
			{
				if(cher == 0x100)
					break;
				Osd_SetTextMonoColor(BLACK_COLOR, DRAK_RED_COLOR);
				Osd_DrawCharDirect(j, i, cher);
				cher++;
			}
		}*/
		//=====================上背景第一行=====================		
		//------------------------左上角---------------------
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalLT[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i, YPOS_START, strLT_4ColorFont[0][i] - _4COLOR_ADDR );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=2; i<6; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i, YPOS_START, OverlineThick);
		}
		//-------------------------TOP01---------------------
		Osd_SetTextMonoColor(BLACK_COLOR, DRAK_RED_COLOR );
		for(i=0; i<5; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect( XPOS_START+i+6, YPOS_START, strTOP01_2ColorFont[0][i] );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP02---------------------
		for(i=0; i<2; i++)		
		{
			Osd_Set256TextColor((PalTOP02[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect( XPOS_START+i+11, YPOS_START, strTOP02_4ColorFont[0][i] - _4COLOR_ADDR + 4 );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_RED_COLOR);
		for(i=0; i<16; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+13, YPOS_START, OverlineThick);
		}
		//-------------------------TOP03---------------------
		for(i=0; i<2; i++)		
		{
			Osd_Set256TextColor((PalTOP03[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect( XPOS_START+i+29, YPOS_START, strTOP03_4ColorFont[0][i] - _4COLOR_ADDR + 13 );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP04---------------------
		Osd_SetTextMonoColor( DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect( XPOS_START+i+31, YPOS_START, strTOP04_2ColorFont[0][i] );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_RED_COLOR);
		for(i=0; i<7; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+33, YPOS_START, SpaceFont);
		}
		//-------------------------TOP05---------------------
		Osd_SetTextMonoColor(BLACK_COLOR, DRAK_RED_COLOR);
		for(i=0; i<2; i++)		
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect( XPOS_START+i+40, YPOS_START, strTOP05_2ColorFont[0][i] );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP06---------------------
		Osd_Set256TextColor((PalTOP03[0][0] >> 2), Color_4);
		OSD_TEXT_HI_ADDR_SET_BIT9();
		Osd_DrawCharDirect( XPOS_START+i+40, YPOS_START, strTOP06_4ColorFont[0][0] - _4COLOR_ADDR + 15 );
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_RED_COLOR);
		for(i=0; i<16; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+43, YPOS_START, OverlineThick);
		}
		//---------------------------------------------------
		for(i=0; i<2; i++)		
		{
			Osd_Set256TextColor((PalTOP03[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect( XPOS_START+i+59, YPOS_START, strTOP03_4ColorFont[0][i] - _4COLOR_ADDR + 13 );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		Osd_SetTextMonoColor( DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect( XPOS_START+i+61, YPOS_START, strTOP04_2ColorFont[0][i] );
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP07---------------------
		Osd_SetTextMonoColor(BLACK_COLOR, DRAK_RED_COLOR);
		for(i=0; i<3; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+63, YPOS_START, strTOP07_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=2; i<6; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+64, YPOS_START, OverlineThick);
		}
		//------------------------右上角---------------------
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalLT[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+70, YPOS_START, strRT_4ColorFont[0][i] - _4COLOR_ADDR + 2);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		
		//=====================上背景第二行=====================	
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<3; i++)
		{
			Osd_DrawCharDirect(XPOS_START, YPOS_START+1+i, LeftVerticalBarThick);
			Osd_DrawCharDirect(XPOS_START+71, YPOS_START+1+i,RightVerticalBar);
		}
		//-------------------------TOP08---------------------
		for(i=0; i<3; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+9, YPOS_START+1, strTOP08_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP09---------------------
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalTOP09[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+12, YPOS_START+1, strTOP09_4ColorFont[0][i] - _4COLOR_ADDR + 16);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(BLACK_RED_COLOR, BLACK_RED_COLOR);
		for(i=0; i<15; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+14, YPOS_START+1, SpaceFont);
		}
		//-------------------------TOP10---------------------
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalTOP10[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+28, YPOS_START+1, strTOP10_4ColorFont[0][i] - _4COLOR_ADDR + 18);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP11---------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+30, YPOS_START+1, strTOP11_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//------------------------Title----------------------
		Osd_SetTextMonoColor(DRAK_WHITE_COLOR, DRAK_RED_COLOR);
		for(i=0; i<9; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+32, YPOS_START+1, str_Title_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP12---------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+41, YPOS_START+1, strTOP12_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP13---------------------
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalTOP13[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+43, YPOS_START+1, strTOP13_4ColorFont[0][i] - _4COLOR_ADDR + 20);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(BLACK_RED_COLOR, BLACK_RED_COLOR);
		for(i=0; i<13; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i+45, YPOS_START+1, SpaceFont);
		}
		for(i=0; i<2; i++)
		{
			Osd_Set256TextColor((PalTOP10[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+58, YPOS_START+1, strTOP10_4ColorFont[0][i] - _4COLOR_ADDR + 18);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP14---------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+60, YPOS_START+1, strTOP14_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP15---------------------
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+62, YPOS_START+1, strTOP15_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//=====================上背景第三行=====================	
		//Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		//-------------------------TOP16---------------------
		for(i=0; i<5; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+10, YPOS_START+2, strTOP16_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP17---------------------
		for(i=0; i<13; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+15, YPOS_START+2, strTOP17_2ColorFont[0][0]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP18---------------------
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+28, YPOS_START+2, strTOP18_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		for(i=0; i<13; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+30, YPOS_START+2, strTOP17_2ColorFont[0][0]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP19---------------------
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+43, YPOS_START+2, strTOP19_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		for(i=0; i<13; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+45, YPOS_START+2, strTOP17_2ColorFont[0][0]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------TOP20---------------------
		for(i=0; i<4; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i+58, YPOS_START+2, strTOP20_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//========================刷新率=========================
		for(i=0; i<2; i++)
		{
			for(j=0; j<2; j++)
			{
				Osd_Set256TextColor((PalSXL[i][j] >> 2), Color_4);
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(XPOS_START+j+17, YPOS_START+i, strSXL_4ColorFont[i][j] - _4COLOR_ADDR + 34);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
		//========================分辨率=========================
		for(i=0; i<2; i++)
		{
			for(j=0; j<2; j++)
			{
				Osd_Set256TextColor((PalFBL[i][j] >> 2), Color_4);
				OSD_TEXT_HI_ADDR_SET_BIT9();
				Osd_DrawCharDirect(XPOS_START+j+46, YPOS_START+i, strFBL_4ColorFont[i][j] - _4COLOR_ADDR + 38);
				OSD_TEXT_HI_ADDR_CLR_TO_0();
			}
		}
		DrawTimingInfo();		//分辨率、刷新率
		//========================左、右背景=====================	
		//-------------------------LIGHT01---------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_START+i, YPOS_START+4, str_LIGHT01_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//-------------------------RIGHT01---------------------
		for(i=0; i<2; i++)
		{
			OSD_TEXT_HI_ADDR_SET_BIT8();
			Osd_DrawCharDirect(XPOS_END-2+i, YPOS_START+4, str_RIGHT01_2ColorFont[0][i]);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_RED_COLOR);
		for(i=0; i<4; i++)
		{
			Osd_DrawCharDirect(XPOS_START, YPOS_START+5+i, SpaceFont);
			Osd_DrawCharDirect(XPOS_END-1, YPOS_START+5+i, SpaceFont);
		}
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		for(i=0; i<16; i++)
		{
			Osd_DrawCharDirect(XPOS_START+1, YPOS_START+5+i, LeftVerticalBarThick);
			Osd_DrawCharDirect(XPOS_END-2, YPOS_START+5+i, RightVerticalBar);
		}		
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_WHITE_COLOR);
		for(i=0; i<4; i++)
		{
			Osd_DrawCharDirect(XPOS_START, YPOS_START+9+i, SpaceFont);
			Osd_DrawCharDirect(XPOS_END-1, YPOS_START+9+i, SpaceFont);
		}
		OSD_TEXT_HI_ADDR_SET_BIT8();
		//-------------------------LIGHT02---------------------
		Osd_DrawCharDirect(XPOS_START, YPOS_START+9, str_LIGHT02_2ColorFont[0][0]);
		//-------------------------RIGHT02---------------------
		Osd_DrawCharDirect(XPOS_END-1, YPOS_START+9, str_RIGHT02_2ColorFont[0][0]);
		//-------------------------LIGHT03---------------------
		Osd_DrawCharDirect(XPOS_START, YPOS_START+13, str_LIGHT03_2ColorFont[0][0]);
		//-------------------------RIGHT03---------------------
		Osd_DrawCharDirect(XPOS_END-1, YPOS_START+13, str_RIGHT03_2ColorFont[0][0]);
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_RED_COLOR);
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START, YPOS_START+14+i, SpaceFont);
			Osd_DrawCharDirect(XPOS_END-1, YPOS_START+14+i, SpaceFont);
		}
		//-------------------------LIGHT04---------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		OSD_TEXT_HI_ADDR_SET_BIT8();
		Osd_DrawCharDirect(XPOS_START, YPOS_START+16, str_LIGHT04_2ColorFont[0][0]);
		//-------------------------RIGHT04---------------------
		Osd_DrawCharDirect(XPOS_END-1, YPOS_START+16, str_RIGHT04_2ColorFont[0][0]);
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		for(i=0; i<5; i++)
		{
			Osd_DrawCharDirect(XPOS_START, YPOS_START+17+i, LeftVerticalBarThick);
			Osd_DrawCharDirect(XPOS_END-1, YPOS_START+17+i, RightVerticalBar);
		}	
		//========================下背景=====================	
		//--------------------------LD-----------------------
		for(i=0; i<5; i++)
		{
			for(j=0; j<3; j++)
			{
				if(PalLD[j][i] >= 0x17)
				{
					if(PalLD[j][i] == 0x17)
						Osd_SetTextMonoColor(BLACK_COLOR, DRAK_RED_COLOR);
					else if(PalLD[j][i] == 0x79)
						Osd_SetTextMonoColor(BLACK_COLOR, BLACK_COLOR);
					else if(PalLD[j][i] == 0x97)
						Osd_SetTextMonoColor(DRAK_WHITE_COLOR, DRAK_WHITE_COLOR);
					else if(PalLD[j][i] == 0x19)
						Osd_SetTextMonoColor(DRAK_WHITE_COLOR, DRAK_RED_COLOR);
				}
				else
					Osd_Set256TextColor((PalLD[j][i] >> 2), Color_4);
				if(PalLD[j][i] >= 0x17)
				{	
					OSD_TEXT_HI_ADDR_SET_BIT8();
					Osd_DrawCharDirect(XPOS_START+i, YPOS_END-3+j, str_LD_ColorFont[j][i]);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
				else
				{
					OSD_TEXT_HI_ADDR_SET_BIT9();
					Osd_DrawCharDirect(XPOS_START+i, YPOS_END-3+j, str_LD_ColorFont[j][i] - _4COLOR_ADDR + 22);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
			}
		}
		//--------------------------RD-----------------------
		for(i=0; i<5; i++)
		{
			for(j=0; j<3; j++)
			{
				if(PalRD[j][i] >= 0x71)
				{
					if(PalRD[j][i] == 0x71)
						Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
					else if(PalRD[j][i] == 0x97)
						Osd_SetTextMonoColor(BLACK_COLOR, BLACK_COLOR);
					else if(PalRD[j][i] == 0x79)
						Osd_SetTextMonoColor(DRAK_WHITE_COLOR, DRAK_WHITE_COLOR);
					else if(PalRD[j][i] == 0x91)
						Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_WHITE_COLOR);
				}
				else
					Osd_Set256TextColor((PalRD[j][i] >> 2), Color_4);
				if(PalRD[j][i] >= 0x71)
				{
					OSD_TEXT_HI_ADDR_SET_BIT8();
					Osd_DrawCharDirect(XPOS_END-5+i, YPOS_END-3+j, str_RD_ColorFont[j][i]);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
				else
				{
					OSD_TEXT_HI_ADDR_SET_BIT9();
					Osd_DrawCharDirect(XPOS_END-5+i, YPOS_END-3+j, str_RD_ColorFont[j][i] - _4COLOR_ADDR + 28);
					OSD_TEXT_HI_ADDR_CLR_TO_0();
				}
			}
		}
		//---------------------bottom01----------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, BLACK_COLOR);
		OSD_TEXT_HI_ADDR_SET_BIT8();
		for(i=5; i<28; i++)
		{
			Osd_DrawCharDirect(XPOS_START+i, YPOS_END-1, str_bottom01_2ColorFont[1][0]);
			Osd_DrawCharDirect(XPOS_START+i, YPOS_END-2, str_bottom01_2ColorFont[0][0]);
			Osd_DrawCharDirect(XPOS_END-i, YPOS_END-1, str_bottom01_2ColorFont[1][0]);
			Osd_DrawCharDirect(XPOS_END-i, YPOS_END-2, str_bottom01_2ColorFont[0][0]);
		}
		//---------------------bottom02----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+28+i, YPOS_END-1, str_bottom02_2ColorFont[1][i]);
			Osd_DrawCharDirect(XPOS_START+28+i, YPOS_END-2, str_bottom02_2ColorFont[0][i]);
		}
		//---------------------bottom03----------------------
		Osd_DrawCharDirect(XPOS_START+30, YPOS_END-2, str_bottom03_2ColorFont[0][0]);
		//---------------------bottom04----------------------
		Osd_DrawCharDirect(XPOS_START+30, YPOS_END-1, str_bottom04_2ColorFont[0][0]);
		//---------------------bottom05----------------------
		Osd_DrawCharDirect(XPOS_START+30, YPOS_END-3, str_bottom05_2ColorFont[0][0]);	
		//---------------------bottom06----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+31, YPOS_END-3+i, str_bottom06_2ColorFont[i][0]);
		}
		//---------------------bottom07----------------------
		for(i=0; i<3; i++)
		{
			Osd_DrawCharDirect(XPOS_START+32, YPOS_END-4+i, str_bottom07_2ColorFont[i][0]);
		}
		//---------------------bottom09----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+33, YPOS_END-4+i, str_bottom09_2ColorFont[i][0]);
		}
		//---------------------bottom08----------------------
		for(i=0; i<5; i++)
		{
			Osd_DrawCharDirect(XPOS_START+34+i, YPOS_END-4, str_bottom08_2ColorFont[0][0]);
		}
		//---------------------bottom10----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+39, YPOS_END-4+i, str_bottom10_2ColorFont[i][0]);
		}
		//---------------------bottom11----------------------
		for(i=0; i<3; i++)
		{
			Osd_DrawCharDirect(XPOS_START+40, YPOS_END-4+i, str_bottom11_2ColorFont[i][0]);
		}
		//---------------------bottom12----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+41, YPOS_END-3+i, str_bottom12_2ColorFont[i][0]);
		}
		//---------------------bottom13----------------------
		for(i=0; i<3; i++)
		{
			Osd_DrawCharDirect(XPOS_START+42, YPOS_END-3+i, str_bottom13_2ColorFont[i][0]);
		}
		//---------------------bottom14----------------------
		for(i=0; i<2; i++)
		{
			Osd_DrawCharDirect(XPOS_START+43+i, YPOS_END-1, str_bottom14_2ColorFont[1][i]);
			Osd_DrawCharDirect(XPOS_START+43+i, YPOS_END-2, str_bottom14_2ColorFont[0][i]);
		}
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_RED_COLOR);
		Osd_DrawCharDirect(XPOS_START+33, YPOS_END-2, SpaceFont);
		Osd_DrawCharDirect(XPOS_START+39, YPOS_END-2, SpaceFont);
		for(i=0; i<3; i++)
		{
			Osd_DrawCharDirect(XPOS_START+31+i, YPOS_END-1, SpaceFont);
			Osd_DrawCharDirect(XPOS_START+39+i, YPOS_END-1, SpaceFont);
		}
		//---------------------------------------------------
		Osd_SetTextMonoColor(DRAK_RED_COLOR, DRAK_RED_COLOR);
		for(i=0x22; i<0x27;i++)
		{
			if(i!=0x24)
			{
				Osd_DrawCharDirect(XPOS_START+i, YPOS_END-3, SpaceFont);
				Osd_DrawCharDirect(XPOS_START+i, YPOS_END-1, SpaceFont);
			}
		}
		
		//------------------------buttom1--------------------
		Osd_Set256TextColor((Palbu1[0][0] >> 2), Color_4);
		OSD_TEXT_HI_ADDR_SET_BIT9();
		Osd_DrawCharDirect(XPOS_START+0x24, YPOS_END-3, strbu1_4ColorFont[0][0] - _4COLOR_ADDR + 6);   
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		//------------------------buttom2--------------------
		for(i=0; i<5; i++)
		{
			Osd_Set256TextColor((Palbu2[0][i] >> 2), Color_4);
			OSD_TEXT_HI_ADDR_SET_BIT9();
			Osd_DrawCharDirect(XPOS_START+i+0x22, YPOS_END-2, strbut2_4ColorFont[0][i] - _4COLOR_ADDR + 7);
			OSD_TEXT_HI_ADDR_CLR_TO_0();
		}
		//------------------------buttom3--------------------
		Osd_Set256TextColor((Palbu3[0][0] >> 2), Color_4);
		OSD_TEXT_HI_ADDR_SET_BIT9();
		Osd_DrawCharDirect(XPOS_START+0x24, YPOS_END-1, strbu3_4ColorFont[0][0] - _4COLOR_ADDR + 12);   
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		
		//------------------------画竖线---------------------
		Osd_SetTextMonoColor(RED_COLOR, BLACK_COLOR);
		for (i = 4; i < 18; i++)
		{
			Osd_DrawCharDirect(XPOS_START+24, YPOS_START+i, LeftVerticalBar);
		}
		for (i = 4; i < 18; i++)
		{
			Osd_DrawCharDirect(XPOS_START+48, YPOS_START+i, LeftVerticalBar);
		}
		
		//==============================================================
		#if	OsdHelpKeyType == OsdHelpKey_Under
		UpdataHelyKeyShowInMenu();
		Osd_SetTextMonoColor(7, 2);
		Osd_DrawCharDirect(13, CurrentMenu.YSize - 2, 0x11);
		Osd_DrawCharDirect(14, CurrentMenu.YSize - 2, 0x12);
		Osd_DrawCharDirect(16, CurrentMenu.YSize - 2, 0x13);
		Osd_DrawCharDirect(17, CurrentMenu.YSize - 2, 0x14);
		Osd_DrawCharDirect(18, CurrentMenu.YSize - 2, 0x15);
		Osd_DrawCharDirect(20, CurrentMenu.YSize - 2, 0x16);
		Osd_DrawCharDirect(21, CurrentMenu.YSize - 2, 0x17);
		Osd_DrawCharDirect(23, CurrentMenu.YSize - 2, 0x18);
		Osd_DrawCharDirect(24, CurrentMenu.YSize - 2, 0x19);
		Osd_DrawCharDirect(25, CurrentMenu.YSize - 2, 0x1A);
		#elif OsdHelpKeyType ==	 OsdHelpKey_Right
		UpdataHelyKeyShowInMenu();
		Osd_SetTextMonoColor(7, 2);
		OSD_TEXT_HI_ADDR_SET_BIT8();
		#if ModelName == MODEL_HS275HFB
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 12, 0x80);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 12, 0x81);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 11, 0x82);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 11, 0x83);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 9, 0x84);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 9, 0x85);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 8, 0x86);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 8, 0x87);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 6, 0x88);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 6, 0x89);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 5, 0x8A);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 5, 0x8B);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 4, 0x8C);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 4, 0x8D);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 3, 0x8E);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 3, 0x8F);
		#elif ModelName == MODEL_HS225HFB
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 13, 0x80);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 13, 0x81);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 12, 0x82);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 12, 0x83);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 9, 0x84);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 9, 0x85);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 8, 0x86);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 8, 0x87);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 6, 0x88);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 6, 0x89);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 5, 0x8A);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 5, 0x8B);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 3, 0x8C);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 3, 0x8D);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 2, 0x8E);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 2, 0x8F);
		#endif
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		#endif
	}
	//快捷菜单背景
	else if ( (MenuPageIndex >= HotKeyECOMenu && MenuPageIndex <= AutoMenu)
	          || MenuPageIndex == InputInfoMenu
          #ifdef OffPower
	          || MenuPageIndex == OffPowerWarningMenu//20110310-98
          #endif
	          || MenuPageIndex < RootMenu )
	{
		Osd_SetTextMonoColor(0x00, 0x0E);
		for (i = 0; i <= OsdWindowHeight - 1; i++)
		{
			Osd_DrawContinuesChar( 0, i, SpaceFont, OsdWindowWidth);
		}
		Osd_SetTextMonoColor(0x06, CPC_TranColor);
		Osd_DrawCharDirect( 0, 0, MonoFrame_LT );
		Osd_DrawCharDirect( OsdWindowWidth - 1, 0, MonoFrame_RT );
		Osd_DrawCharDirect( 0, OsdWindowHeight - 1, MonoFrame_LD );
		Osd_DrawCharDirect( OsdWindowWidth - 1, OsdWindowHeight - 1, MonoFrame_RD );
		Osd_SetTextMonoColor(0, 2);
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, 0, SpaceFont);
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 1, SpaceFont);
		}
		Osd_SetTextMonoColor(1, 7);
		Osd_DrawCharDirect(0, 1, AutoMenuFrameLeftSide_1);
		Osd_DrawCharDirect(0, CurrentMenu.YSize - 2, AutoMenuFrameLeftSide_3);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, 1, AutoMenuFrameRightSide_1);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, CurrentMenu.YSize - 2, AutoMenuFrameRightSide_3);
		for(i = 2; i <= CurrentMenu.YSize - 3; i++)
		{
			Osd_DrawCharDirect(0, i, AutoMenuFrameLeftSide_2);
			Osd_DrawCharDirect(CurrentMenu.XSize - 1, i, AutoMenuFrameRightSide_2);
		}
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, 1, AutoMenuFrameMide_Top);
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 2, AutoMenuFrameMide_Bottom);
		}
	}
	//二级菜单背景
	else if (PrevPage == MainMenu && (MenuPageIndex >= OSD_BriContrastMenu && MenuPageIndex <= OSD_MiscMenu))
	{
		Osd_SetTextMonoColor(BLACK_COLOR, BLACK_COLOR);
		for (i = MENU2_YPOS_START; i <= MENU2_YPOS_END; i++)	
		{
			Osd_DrawContinuesChar( MENU2_XPOS_START, i, SpaceFont, 20);	
			Osd_DrawContinuesChar( MENU3_XPOS_START, i, SpaceFont, 20);	
		}
	}
}


/*
void DrawOsdBackGround(void)
{
	BYTE i;
	if ( MenuPageIndex == MainMenu )
	{
		Osd_SetTextMonoColor(0x00, 0x0E);
		for (i = 0; i <= OsdWindowHeight - 1; i++)
		{
			Osd_DrawContinuesChar( 0, i, SpaceFont, OsdWindowWidth);
		}
		//draw Four Cornu
		Osd_SetTextMonoColor(0x06, CPC_TranColor);
		Osd_DrawCharDirect(0, 0, MonoFrame_LT);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, 0, MonoFrame_RT);
		#if OsdHelpKeyType == OsdHelpKey_Right
		#else
		Osd_DrawCharDirect(0, CurrentMenu.YSize - 1, MonoFrame_LD);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, CurrentMenu.YSize - 1, MonoFrame_RD);
		#endif
		//draw frame
		Osd_SetTextMonoColor(0, 2);
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, 0, SpaceFont);
			Osd_DrawCharDirect(i, 1, SpaceFont);
		}
		Osd_DrawCharDirect(0, 1, SpaceFont);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, 1, SpaceFont);
		//draw Top and Bottom& left & right line
		Osd_SetTextMonoColor(5, 2);
		for(i = 0; i < CurrentMenu.XSize; i++)
		{
			Osd_DrawCharDirect(i, 2, MenuFrame_TopSide);
		}
		for(i = 0; i < CurrentMenu.XSize; i++)
		{
			Osd_DrawCharDirect(i, CurrentMenu.YSize - underBlankFontWide, MenuFrame_BottomSide);
		}
		Osd_SetTextMonoColor(5, 7);
		for(i = 3; i < CurrentMenu.YSize - underBlankFontWide; i++)
		{
			Osd_DrawCharDirect(5, i, MenuFrame_LeftSide);
		}
		#if OsdHelpKeyType == OsdHelpKey_Right
		for(i = 3; i < CurrentMenu.YSize - underBlankFontWide; i++)
		{
			Osd_DrawCharDirect(CurrentMenu.XSize - 5, i, MenuFrame_RightSide);
		}
		Osd_SetTextMonoColor(2, 2);
		for(i = 3; i < CurrentMenu.YSize - underBlankFontWide; i++)
		{
			Osd_DrawCharDirect(CurrentMenu.XSize - 4, i, SpaceFont);
			Osd_DrawCharDirect(CurrentMenu.XSize - 3, i, SpaceFont);
			Osd_DrawCharDirect(CurrentMenu.XSize - 2, i, SpaceFont);
			Osd_DrawCharDirect(CurrentMenu.XSize - 1, i, SpaceFont);
		}
		#else
		for(i = 3; i < CurrentMenu.YSize - underBlankFontWide; i++)
		{
			Osd_DrawCharDirect(CurrentMenu.XSize - 1, i, MenuFrame_RightSide);
		}
		#endif
		Osd_SetTextMonoColor(0, 2);
		#if OsdHelpKeyType == OsdHelpKey_Right
		#else
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 2, SpaceFont);
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 1, SpaceFont);
		}
		Osd_DrawCharDirect(0, CurrentMenu.YSize - 2, SpaceFont);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, CurrentMenu.YSize - 2, SpaceFont);
		#endif
		#if	OsdHelpKeyType == OsdHelpKey_Under
		UpdataHelyKeyShowInMenu();
		Osd_SetTextMonoColor(7, 2);
		Osd_DrawCharDirect(13, CurrentMenu.YSize - 2, 0x11);
		Osd_DrawCharDirect(14, CurrentMenu.YSize - 2, 0x12);
		Osd_DrawCharDirect(16, CurrentMenu.YSize - 2, 0x13);
		Osd_DrawCharDirect(17, CurrentMenu.YSize - 2, 0x14);
		Osd_DrawCharDirect(18, CurrentMenu.YSize - 2, 0x15);
		Osd_DrawCharDirect(20, CurrentMenu.YSize - 2, 0x16);
		Osd_DrawCharDirect(21, CurrentMenu.YSize - 2, 0x17);
		Osd_DrawCharDirect(23, CurrentMenu.YSize - 2, 0x18);
		Osd_DrawCharDirect(24, CurrentMenu.YSize - 2, 0x19);
		Osd_DrawCharDirect(25, CurrentMenu.YSize - 2, 0x1A);
		#elif OsdHelpKeyType ==	 OsdHelpKey_Right
		UpdataHelyKeyShowInMenu();
		Osd_SetTextMonoColor(7, 2);
		OSD_TEXT_HI_ADDR_SET_BIT8();
		#if ModelName == MODEL_HS275HFB
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 12, 0x80);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 12, 0x81);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 11, 0x82);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 11, 0x83);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 9, 0x84);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 9, 0x85);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 8, 0x86);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 8, 0x87);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 6, 0x88);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 6, 0x89);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 5, 0x8A);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 5, 0x8B);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 4, 0x8C);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 4, 0x8D);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 3, 0x8E);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 3, 0x8F);
		#elif ModelName == MODEL_HS225HFB
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 13, 0x80);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 13, 0x81);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 12, 0x82);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 12, 0x83);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 9, 0x84);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 9, 0x85);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 8, 0x86);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 8, 0x87);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 6, 0x88);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 6, 0x89);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 5, 0x8A);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 5, 0x8B);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 3, 0x8C);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 3, 0x8D);
		Osd_DrawCharDirect(0x2A, CurrentMenu.YSize - 2, 0x8E);
		Osd_DrawCharDirect(0x2B, CurrentMenu.YSize - 2, 0x8F);
		#endif
		OSD_TEXT_HI_ADDR_CLR_TO_0();
		#endif
	}
	else if ( (MenuPageIndex >= HotKeyECOMenu && MenuPageIndex <= AutoMenu)
	          || MenuPageIndex == InputInfoMenu
          #ifdef OffPower
	          || MenuPageIndex == OffPowerWarningMenu//20110310-98
          #endif
	          || MenuPageIndex < RootMenu )
	{
		Osd_SetTextMonoColor(0x00, 0x0E);
		for (i = 0; i <= OsdWindowHeight - 1; i++)
		{
			Osd_DrawContinuesChar( 0, i, SpaceFont, OsdWindowWidth);
		}
		Osd_SetTextMonoColor(0x06, CPC_TranColor);
		Osd_DrawCharDirect( 0, 0, MonoFrame_LT );
		Osd_DrawCharDirect( OsdWindowWidth - 1, 0, MonoFrame_RT );
		Osd_DrawCharDirect( 0, OsdWindowHeight - 1, MonoFrame_LD );
		Osd_DrawCharDirect( OsdWindowWidth - 1, OsdWindowHeight - 1, MonoFrame_RD );
		Osd_SetTextMonoColor(0, 2);
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, 0, SpaceFont);
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 1, SpaceFont);
		}
		Osd_SetTextMonoColor(1, 7);
		Osd_DrawCharDirect(0, 1, AutoMenuFrameLeftSide_1);
		Osd_DrawCharDirect(0, CurrentMenu.YSize - 2, AutoMenuFrameLeftSide_3);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, 1, AutoMenuFrameRightSide_1);
		Osd_DrawCharDirect(CurrentMenu.XSize - 1, CurrentMenu.YSize - 2, AutoMenuFrameRightSide_3);
		for(i = 2; i <= CurrentMenu.YSize - 3; i++)
		{
			Osd_DrawCharDirect(0, i, AutoMenuFrameLeftSide_2);
			Osd_DrawCharDirect(CurrentMenu.XSize - 1, i, AutoMenuFrameRightSide_2);
		}
		for(i = 1; i <= CurrentMenu.XSize - 2; i++)
		{
			Osd_DrawCharDirect(i, 1, AutoMenuFrameMide_Top);
			Osd_DrawCharDirect(i, CurrentMenu.YSize - 2, AutoMenuFrameMide_Bottom);
		}
	}
}
*/


