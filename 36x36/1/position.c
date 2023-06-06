


 BYTE code  tPNOPalette[] =
{
		 // 2 color [0x00]  PNO_0_0
		 CP256_RGB_C(   0,   0,   0), 
		 CP256_RGB_C( 255, 255, 255), 
};

#define CPPNO(x)  (x+0)
 BYTE code PalPNO[2][4]=
{
	{	 CPPNO(0x00), CPPNO(0x00), CPPNO(0x00), 
	 0},
	{	 CPPNO(0x00), CPPNO(0x00), CPPNO(0x00), 
	 0}
};
