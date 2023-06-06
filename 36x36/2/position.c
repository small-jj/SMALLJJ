


 BYTE code  tCNOPalette[] =
{
		 // 2 color [0x00]  CNO_0_0
		 CP256_RGB_C(   0,   0,   0), 
		 CP256_RGB_C( 255, 255, 255), 
};

#define CPCNO(x)  (x+0)
 BYTE code PalCNO[2][4]=
{
	{	 CPCNO(0x00), CPCNO(0x00), CPCNO(0x00), 
	 0},
	{	 CPCNO(0x00), CPCNO(0x00), CPCNO(0x00), 
	 0}
};
