extern Bool mStar_AutoHTotal(BYTE vsyncTime);
extern Bool mStar_AutoPhase(BYTE vsyncTime);
//2006-03-30 Andy extern void mStar_AutoPosition(void);
extern Bool mStar_AutoPosition(void);
extern Bool mStar_AutoAdjustAdcGain(BYTE vsyncTime);
extern Bool mStar_AutoAdjustAdcOffset(BYTE vsyncTime);
extern Bool mStart_ADCOffset_AtuoCalibraton(void);
extern Bool mStar_AutoAdcColor(BYTE vsyncTime);
extern Bool mStar_AutoGeomtry(void);
extern Bool mStar_AutoColor(void);
extern WORD SearchMaxWidth( BYTE vsyncTime );
extern void WaitAutoStatusReady( WORD u16RegAddr, BYTE regFlag );