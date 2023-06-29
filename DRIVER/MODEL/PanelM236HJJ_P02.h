#ifndef __PanelLM230HT11__
#define __PanelLM230HT11__
#define PanelName           "M236HJJ-P02"
//#define PANEL_TYPE            PANEL_22_WIDE

#define PanelDither     8

#define PanelTTL            0
#define PanelTCON           0
#define PanelLVDS           0xFF
#define PanelRSDS           0

#define LVDS_TIMode     0xff
#define PanelDualPort       0xFF
#define PanelSwapPort       0
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0//xFF
#define PanelSwapEvenRB     0//xFF
#define PanelSwapMLSB       0
#define PanelSwapPlusMinus      0
#define PANEL_SWAP_PN       0xFF

#define PanelDClkDelay    0
#define PanelInvDE      0
#define PanelInvDClk    0
#define PanelInvHSync   0
#define PanelInvVSync   0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent  1 // Dclk current
#define PanelDECurrent    1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent  1 // Even data current

#define PanelOnTiming1      30//60//20 // time between panel & data while turn on power
#define PanelOnTiming2      550//350//220 // time between data & back light while turn on power
#define PanelOffTiming1     300//350//220 // 2005/5/3// time between back light & data while turn off power
#define PanelOffTiming2     20//20//25 // 2005/5/3//10 // time between data & panel while turn off power

#define PanelHSyncWidth     35
#define PanelHSyncBackPorch 40

#define PanelVSyncWidth     6
#define PanelVSyncBackPorch 20

#define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)


#define PanelWidth    		1920
#define PanelHeight   		1080

#define PanelHTotal   		2200
#define PanelVTotal   		1125

#define PanelMaxHTotal     	2300
#define PanelMinHTotal     	2120

#define PanelMaxVTotal     	1220
#define PanelMinVTotal     	1110

#define PanelDCLK       		150
#define PanelMaxDCLK     	196
#define PanelMinDCLK     		118

// TCON  setting for LVDS
//PVS / FSYNC
#define GPO9_VStart             0x7
#define GPO9_VEnd               0x705
#define GPO9_HStart             0x0
#define GPO9_HEnd               0x0
#define GPO9_Control            0x7

//HSYNC
#define GPOA_VStart             0x006
#define GPOA_VEnd               0x408
#define GPOA_HStart             0
#define GPOA_HEnd               0
#define GPOA_Control            0x4



#endif

