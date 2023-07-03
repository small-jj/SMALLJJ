//主菜单
extern BYTE* MainMenu_ColorSetUpText(void);
extern BYTE* MainMenu_BrightnessSetUpText(void);
extern BYTE* MainMenu_ScreenSetUpText(void);
extern BYTE* MainMenu_GameSetUpText(void);
extern BYTE* MainMenu_MenuSetUpText(void);
extern BYTE* MainMenu_PIP_PBPSetUpText(void);
extern BYTE* MainMenu_OtherSetUpText(void);
//颜色
extern BYTE* Menu2_WarmTemp_Text(void);
extern BYTE* Menu2_CoolTemp_Text(void);
extern BYTE* Menu2_Chromaticity_Text(void);
extern BYTE* Menu2_ColorSaturation_Text(void);
//亮度
extern BYTE* Menu2_Brightness_Text(void);
extern BYTE* Menu2_Contrast_Text(void);
extern BYTE* Menu2_DynamicContrast_Text(void);
extern BYTE* Menu2_DynamicBrightness_Text(void);
//画面
extern BYTE* Menu2_ScenarioMode_Text(void);
extern BYTE* Menu2_ScreenRatio_Text(void);
extern BYTE* Menu2_Gamma_Text(void);
extern BYTE* Menu2_Sharpness_Text(void);
extern BYTE* Menu2_LowBlueLight_Text(void);
extern BYTE* Menu2_HDR_Text(void);
extern BYTE* Menu2_DarkBalance_Text(void);
//游戏专用功能
extern BYTE* Menu2_MPRT_Text(void);
extern BYTE* Menu2_AdaptiveSync_Text(void);
extern BYTE* Menu2_ResponseTime_Text(void);
extern BYTE* Menu2_RefreshRate_Text(void);
extern BYTE* Menu2_GameAlignment_Text(void);
extern BYTE* Menu2_GameTiming_Text(void);
extern BYTE* Menu2_AmbientLight_Text(void);
//菜单设置
extern BYTE* Menu2_Language_Text(void);
extern BYTE* Menu2_OSD_DisplayTime_Text(void);
extern BYTE* Menu2_OSD_HPosition_Text(void);
extern BYTE* Menu2_OSD_VPostion_Text(void);
extern BYTE* Menu2_MenuRotation_Text(void);
extern BYTE* Menu2_MenuLock_Text(void);
extern BYTE* Menu2_ShortcutKey1_Text(void);
extern BYTE* Menu2_ShortcutKey2_Text(void);
extern BYTE* Menu2_ShortcutKey3_Text(void);
extern BYTE* Menu2_ShortcutKey4_Text(void);
//其他设置
extern BYTE* Menu2_SignalInput_Text(void);
extern BYTE* Menu2_AudioInput_Text(void);
extern BYTE* Menu2_Mute_Text(void);
extern BYTE* Menu2_Volume_Text(void);
extern BYTE* Menu2_AutoShutdown_Text(void);
extern BYTE* Menu2_EyeProtectionReminder_Text(void);
extern BYTE* Menu2_Reset_Text(void);
extern BYTE* Menu2_Information_Text(void);

//------------------------------------------------------------------


extern BYTE* MainMenu_BrightText(void);
extern BYTE* MainMenu_ImageText(void);
extern BYTE* MainMenu_ColorText(void);
extern BYTE* MainMenu_OSDText(void);
extern BYTE* MainMenu_ResetText(void);
extern BYTE* MainMenu_MiscText(void);

#if !AdjustLanguageFunction
extern BYTE *strEnglishText( void );
extern BYTE *strFranceText( void );
extern BYTE *strEspanolText( void );
extern BYTE *strPortuguesText( void );
extern BYTE *strDeutschText( void );
extern BYTE *strItalianoText( void );
extern BYTE *strNederlandsText( void );
extern BYTE * strSvenskaText( void );
extern BYTE *strSuomiText( void );
extern BYTE *strPolskiText( void );
extern BYTE *strCestinaText( void );
extern BYTE *strPycText( void );
extern BYTE *strKoreanText( void );
extern BYTE *strTChineseText( void );
extern BYTE *strSChineseText( void );
extern BYTE *strJapanText( void );
#endif

//=============================================		//my
extern BYTE* Color_Icon(void);				//0 颜色
extern BYTE* BrightnessContrast_Icon(void);	//1 亮度 对比度
extern BYTE* Screen_Icon(void);				//2 画面
extern BYTE* GameProFeatures_Icon(void);		//3 游戏专业功能
extern BYTE* MenuSettings_Icon(void);		//4 菜单功能
extern BYTE* OtherSettings_Icon(void);		//5 其他功能

//-----------------------------------------
extern BYTE code strTOP01_2ColorFont[1][6];
extern BYTE code strTOP04_2ColorFont[1][3];
extern BYTE code strTOP05_2ColorFont[1][3];
extern BYTE code strTOP07_2ColorFont[1][4];
extern BYTE code strTOP08_2ColorFont[1][4];
extern BYTE code strTOP11_2ColorFont[1][3];
extern BYTE code strTOP12_2ColorFont[1][3];
extern BYTE code strTOP13_4ColorFont[1][3];
extern BYTE code strTOP14_2ColorFont[1][3];
extern BYTE code strTOP15_2ColorFont[1][3];
extern BYTE code strTOP16_2ColorFont[1][6];
extern BYTE code strTOP17_2ColorFont[1][2];
extern BYTE code strTOP18_2ColorFont[1][3];
extern BYTE code strTOP19_2ColorFont[1][3];
extern BYTE code strTOP20_2ColorFont[1][5];

extern BYTE code str_LIGHT01_2ColorFont[1][3];
extern BYTE code str_RIGHT01_2ColorFont[1][3];
extern BYTE code str_LIGHT02_2ColorFont[1][2];
extern BYTE code str_RIGHT02_2ColorFont[1][2];
extern BYTE code str_LIGHT03_2ColorFont[1][2];
extern BYTE code str_RIGHT03_2ColorFont[1][2];
extern BYTE code str_LIGHT04_2ColorFont[1][2];
extern BYTE code str_RIGHT04_2ColorFont[1][2];

extern BYTE code strLT_4ColorFont[1][3];
extern BYTE code strRT_4ColorFont[1][3];
extern BYTE code str_LD_ColorFont[3][6];
extern BYTE code str_RD_ColorFont[3][6];

extern BYTE code str_bottom01_2ColorFont[2][2];
extern BYTE code str_bottom02_2ColorFont[2][3];
extern BYTE code str_bottom03_2ColorFont[1][2];
extern BYTE code str_bottom04_2ColorFont[1][2];
extern BYTE code str_bottom05_2ColorFont[1][2];
extern BYTE code str_bottom06_2ColorFont[2][2];
extern BYTE code str_bottom07_2ColorFont[3][2];
extern BYTE code str_bottom08_2ColorFont[1][2];
extern BYTE code str_bottom09_2ColorFont[2][2];
extern BYTE code str_bottom10_2ColorFont[2][2];
extern BYTE code str_bottom11_2ColorFont[3][2];
extern BYTE code str_bottom12_2ColorFont[2][2];
extern BYTE code str_bottom13_2ColorFont[3][2];
extern BYTE code str_bottom14_2ColorFont[2][3];

extern BYTE code strTOP02_4ColorFont[1][3];
extern BYTE code strbu1_4ColorFont[1][2];
extern BYTE code strbut2_4ColorFont[1][6];
extern BYTE code strbu3_4ColorFont[1][2];
extern BYTE code strTOP03_4ColorFont[1][3];
extern BYTE code strTOP06_4ColorFont[1][2];
extern BYTE code strTOP09_4ColorFont[1][3];
extern BYTE code strTOP10_4ColorFont[1][3];

extern BYTE code strSXL_4ColorFont[2][3];
extern BYTE code strFBL_4ColorFont[2][3];
extern BYTE code str_Title_2ColorFont[1][10];

//=============================================

extern BYTE* BrightnessIcon(void);
extern BYTE* ImageIcon(void);
extern BYTE* ColorTempIcon(void);
extern BYTE* OSDIcon(void);
extern BYTE* ResetIcon(void);
extern BYTE* MiscIcon(void);
extern BYTE *Main_FText(void);


#if AudioFunc
#if EANBLE_MUTE_ON_OFF

extern BYTE *MuteText( void );
extern BYTE *MuteValueText( void );
#endif
extern BYTE *VolumeText( void );
#endif
#if DDCCI_ENABLE && DDCCCIMenu_Enable
extern BYTE *DDCCIText( void );
extern BYTE *DDCCIValueText( void );
#endif
#if FreeSyncMenu_Enable
extern BYTE *FreeSyncText( void );
extern BYTE *FreeSyncValueText( void );
#endif

#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
extern BYTE *InputSourceText( void );
#endif
#if ENABLE_HDMI2
extern BYTE *HDMI2Text( void );
#endif
#if ENABLE_HDMI
extern BYTE *HDMIText( void );
#endif
#if ENABLE_DP_INPUT
extern BYTE *DPText( void );
#endif
#if ENABLE_DVI
extern BYTE *DigitalText( void );
#endif
#if ENABLE_VGA
extern BYTE *AnalogText(void);
#endif
extern BYTE *AutoText( void );
#if HKC_INPUTSELECT_MODE
extern BYTE *InputTypeRationText( void );
#endif


/*******************************************************************************
*
*
*
*
*
*
*
*
*******************************************************************************/


















extern BYTE *VersionDateText(void);
extern BYTE *ChangeDateText(void);
extern BYTE *ModelNameText(void);
BYTE *ChipNameText( void );

extern BYTE *DateText(void);
extern BYTE *HourText(void);
extern BYTE *ContrastText( void );
extern BYTE *BrightnessText( void );
extern BYTE *ECOModeText( void );
extern BYTE *ECOModeValue( void );
extern BYTE *GammaText( void );
extern BYTE *GammaModeValue( void );
extern BYTE *DCRText( void );
extern BYTE *DcrValueText( void );
#if (ENABLE_RTE)
extern BYTE *OverdriveText( void );
extern BYTE *OverdriveValueText( void );
#endif



extern BYTE *ClockText( void );
extern BYTE *FocusText( void );
extern BYTE *HPositionText( void );
extern BYTE *VPositionText( void );
extern BYTE *SharpnessText( void );


extern BYTE *ColorTempText( void );
extern BYTE *ColorTempValueText( void );
extern BYTE *UserColorRText( void );
extern BYTE *UserColorGText( void );
extern BYTE *UserColorBText( void );
#if MWEFunction

extern BYTE *BF_HueText( void );
extern BYTE *BF_SaturationText( void );

extern BYTE *BF_RightArrowText( void );

#endif

extern BYTE *OsdHPositionText( void );
extern BYTE *OsdVPositionText( void );
extern BYTE *OsdTimeOutText( void );
extern BYTE *TransparenceText( void );
extern BYTE *LanguageText( void );


extern BYTE *InputSelectText( void );
extern BYTE *SubAutoColorText( void );
extern BYTE *AutoConfigText( void );
#if Enable_Adjust_SharpnessMenu
extern BYTE *SharpnessText( void );
#else
#ifdef OffPower
extern BYTE *OffTimerText( void );
extern BYTE *NullText( void );
#endif
#endif
extern BYTE *ResetText( void );



extern BYTE *EraseEEPROMText( void );
#if ENABLE_FREESYNC
extern BYTE *FreeSyncVsyncText( void );
#endif
#if Enable_Expansion
extern BYTE *ExpansionText( void );
extern BYTE *ExpansionValueText( void );
#endif
extern BYTE *InformationExtraText( void );
extern BYTE *InputConnectorText( void );
extern BYTE *ResolutionText( void );
extern BYTE *HFrequenceText( void );
extern BYTE *VFrequenceText( void );

#if ENABLE_FREESYNC
extern BYTE *VsyncText( void );
#endif




extern BYTE *ColorBoostText(void);
extern BYTE *FullText(void);
extern BYTE *NatureSkinText(void);
extern BYTE *GreenFieldText(void);
extern BYTE *SkyBlueText(void);
extern BYTE *AutoDetectText(void);
extern BYTE *DemoText(void);
extern BYTE *FreeColorBarText(void);
extern BYTE *FreeColorFullModeText(void);
extern BYTE *FreeColorSkinProtectModeText(void);
extern BYTE *FreeColorGreenEnhanceModeText(void);
extern BYTE *FreeColorBlueEnhanceModeText(void);
extern BYTE *FreeColorAutoDetectModeText(void);
extern BYTE *FreeColorDemoModeText(void);
extern BYTE *BFHPositionText(void);
extern BYTE *BFVPositionText(void);
extern BYTE *BFPositionText(void);
extern BYTE *BF_FrameSizeText(void);
extern BYTE *BF_BrightnessText(void);
extern BYTE *BF_ContrastText(void);
extern BYTE *BF_HueText(void);
extern BYTE *BF_SaturationText(void);
extern BYTE *BF_PositionText(void);
extern BYTE *BF_RightArrowText(void);
extern BYTE *BF_SwitchText(void);
extern BYTE *BF_SwitchValueText(void);
extern BYTE *OsdHPositionText(void);
extern BYTE *OsdVPositionText(void);
extern BYTE *OsdTransparenceText(void);
extern BYTE *OsdTimeOutText(void);
extern BYTE *LanguageText(void);
#if AdjustLanguageFunction
extern BYTE *LanguageStatusText( void );
#endif
extern BYTE *LanguageValueText(void);
extern BYTE *LanguageValue1Text(void);
extern BYTE *Language1Text(void);
#if 1//Dual
extern BYTE *InputSelectText(void);
#endif
extern BYTE *AutoConfigText(void);
extern BYTE *InformationText(void);
#if (INPUT_TYPE!=INPUT_1A) && (INPUT_TYPE!=INPUT_1H)
extern BYTE *InputSourceText(void);
#endif


extern BYTE *ExtraBarText(void);
extern BYTE *InformationArrowText(void);
// 071218 reserved for extra page fw version
//extern BYTE *VersionText(void);
//extern BYTE *FW_VerText(void);
#if DDCCI_ENABLE && DDCCCIMenu_Enable
extern BYTE *DDCCIText(void);
extern BYTE *DDCCIValueText(void);
#endif

#if Enable_Expansion
extern BYTE *ExpansionText(void);
extern BYTE *ExpansionValueText(void);
#endif
extern BYTE *InformationExtraText(void);
extern BYTE *InputConnectorText(void);
extern BYTE *ResolutionText(void);
extern BYTE *HResText(void);
extern BYTE *VResText(void);
extern BYTE *X_Text(void);
extern BYTE *HFrequenceText(void);
extern BYTE *VFrequenceText(void);
extern BYTE *KHzText(void);
extern BYTE *HzText(void);


extern BYTE *OutOfRangeText(void);
extern BYTE* CableNotConnectText(void);
extern BYTE *NoSyncText( void );
extern BYTE *NoSyncStatusText( void );

#ifdef OffPower
extern BYTE *OffTimerM98Text( void );
extern BYTE *MonitorOffText( void );
#endif


#if ENABLE_OSD_LowBlueLight
extern BYTE *LowBlueLightText( void );
extern BYTE *LowBlueLightStatusText( void );
#endif

#if Hot_Corss_ColorSelect
extern BYTE* CorssIcon(void);
#elif Hot_Corss_FY_ColorSelect || Hot_Corss_FND_Select
extern BYTE* CorssIcon1(void);
extern BYTE* CorssIcon2(void);
extern BYTE* CorssIcon3(void);
#endif



