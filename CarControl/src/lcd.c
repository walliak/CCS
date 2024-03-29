/************************************************************
			12864LCD与MSP430F5529接线引脚

			序号 430引脚						序号	430引脚
	SCL		14->P3.4				SDA		13->P6.5
	A0		12->					RST		11->
	PB4		10->P6.4				PB3		9 ->P6.3
	PB2		8 ->P6.2				PB1		7 ->P6.1
	PA4		6 ->P3.2				PA3		5 ->P6.6
	GND		4 ->GND					PA2		3 ->P1.6
	VDD		2 ->VDD					PA1		1 ->P3.3

************************************************************/
#include "MSP430F5529.h"
#include <lcd.h>

const unsigned char  Fix[32]=
{
	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
};

const unsigned char DzkCode[1][32]=
{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

const unsigned char  AsciiFontData[95][16]	=
{
/*--  文字:     --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  !  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x98,0x18,0x00,0x00,0x00,

/*--  文字:  "  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x08,0x30,0x48,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  #  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x04,0x04,0x1F,0x04,0x1F,0x04,0x00,0x00,0x40,0xF8,0x40,0xF8,0x40,0x40,0x00,

/*--  文字:  $  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0E,0x11,0x3F,0x10,0x0C,0x00,0x00,0x00,0x30,0x08,0xFE,0x88,0x70,0x00,0x00,

/*--  文字:  %  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x0E,0x11,0x0E,0x01,0x06,0x18,0x00,0x00,0x00,0x18,0x60,0x80,0x70,0x88,0x70,0x00,

/*--  文字:  &  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0F,0x11,0x0F,0x01,0x01,0x00,0x00,0xF0,0x08,0xC8,0x28,0xF0,0x08,0x08,0x00,

/*--  文字:  '  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x08,0x68,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  (  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,0x00,0x00,0x00,0xC0,0x30,0x08,0x04,0x00,

/*--  文字:  )  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,0x04,0x08,0x30,0xC0,0x00,0x00,0x00,

/*--  文字:  *  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,

/*--  文字:  +  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x01,0x01,0x01,0x0F,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,

/*--  文字:  ,  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x1A,0x1C,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  -  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  .  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  /  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x01,0x06,0x38,0x40,0x00,0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,

/*--  文字:  0  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00,0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,

/*--  文字:  1  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,

/*--  文字:  2  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0C,0x10,0x10,0x10,0x11,0x0E,0x00,0x00,0x18,0x28,0x48,0x88,0x08,0x18,0x00,

/*--  文字:  3  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0C,0x10,0x11,0x11,0x12,0x0C,0x00,0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,

/*--  文字:  4  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x04,0x1F,0x00,0x00,0x00,0x00,0xC0,0x40,0x48,0xF8,0x48,0x48,0x00,

/*--  文字:  5  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x1F,0x11,0x12,0x12,0x12,0x11,0x00,0x00,0x30,0x08,0x08,0x08,0x08,0xF0,0x00,

/*--  文字:  6  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x07,0x08,0x11,0x11,0x19,0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x08,0xF0,0x00,

/*--  文字:  7  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x1C,0x10,0x10,0x13,0x1C,0x10,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0E,0x11,0x11,0x11,0x11,0x0E,0x00,0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,

/*--  文字:  9  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0F,0x10,0x10,0x10,0x09,0x07,0x00,0x00,0x00,0x98,0x88,0x88,0x10,0xE0,0x00,

/*--  文字:  :  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,

/*--  文字:  ;  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x0C,0x00,0x00,0x00,0x00,

/*--  文字:  <  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,

/*--  文字:  =  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,

/*--  文字:  >  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,

/*--  文字:  ?  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x1C,0x20,0x20,0x20,0x21,0x1E,0x00,0x00,0x00,0x00,0x18,0xD8,0x00,0x00,0x00,

/*--  文字:  @  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x07,0x08,0x13,0x14,0x17,0x08,0x07,0x00,0xE0,0x10,0xE8,0x28,0xC8,0x28,0xD0,0x00,

/*--  文字:  A  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x07,0x18,0x07,0x00,0x00,0x00,0x08,0x78,0xC8,0x40,0xC8,0x78,0x08,0x00,

/*--  文字:  B  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x11,0x11,0x12,0x0C,0x00,0x08,0xF8,0x08,0x08,0x08,0x88,0x70,0x00,

/*--  文字:  C  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x07,0x08,0x10,0x10,0x10,0x10,0x1C,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0x20,0x00,

/*--  文字:  D  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x10,0x10,0x10,0x08,0x07,0x00,0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,

/*--  文字:  E  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x08,0xF8,0x08,0x08,0xC8,0x08,0x10,0x00,

/*--  文字:  F  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x08,0xF8,0x08,0x00,0xC0,0x00,0x00,0x00,

/*--  文字:  G  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x07,0x08,0x10,0x10,0x10,0x1C,0x00,0x00,0xE0,0x10,0x08,0x08,0x48,0x70,0x40,0x00,

/*--  文字:  H  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x01,0x11,0x1F,0x10,0x00,0x08,0xF8,0x08,0x00,0x08,0xF8,0x08,0x00,

/*--  文字:  I  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,

/*--  文字:  J  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x06,0x02,0x02,0x02,0xFC,0x00,0x00,0x00,

/*--  文字:  K  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x03,0x14,0x18,0x10,0x00,0x08,0xF8,0x08,0x80,0x68,0x18,0x08,0x00,

/*--  文字:  L  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x08,0xF8,0x08,0x08,0x08,0x08,0x18,0x00,

/*--  文字:  M  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x1E,0x01,0x1E,0x1F,0x10,0x00,0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,

/*--  文字:  N  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x1C,0x03,0x10,0x1F,0x10,0x00,0x08,0xF8,0x08,0x80,0x70,0xF8,0x00,0x00,

/*--  文字:  O  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,

/*--  文字:  P  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x11,0x11,0x11,0x0E,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  Q  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xE0,0x10,0x28,0x28,0x18,0x14,0xE4,0x00,

/*--  文字:  R  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x11,0x11,0x11,0x0E,0x00,0x00,0x08,0xF8,0x08,0x80,0x60,0x18,0x08,0x00,

/*--  文字:  S  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x0E,0x11,0x11,0x10,0x10,0x1C,0x00,0x00,0x38,0x08,0x08,0x88,0x88,0x70,0x00,

/*--  文字:  T  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x18,0x10,0x10,0x1F,0x10,0x10,0x18,0x00,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,

/*--  文字:  U  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x10,0x00,0x10,0x1F,0x10,0x00,0x00,0xF0,0x08,0x08,0x08,0xF0,0x00,0x00,

/*--  文字:  V  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1E,0x11,0x00,0x11,0x1E,0x10,0x00,0x00,0x00,0xE0,0x18,0xE0,0x00,0x00,0x00,

/*--  文字:  W  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x00,0x1F,0x00,0x1F,0x10,0x00,0x00,0x80,0xF8,0x00,0xF8,0x80,0x00,0x00,

/*--  文字:  X  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x18,0x16,0x01,0x16,0x18,0x10,0x00,0x08,0x18,0x68,0x80,0x68,0x18,0x08,0x00,

/*--  文字:  Y  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1C,0x13,0x00,0x13,0x1C,0x10,0x00,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,

/*--  文字:  Z  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x08,0x10,0x10,0x13,0x1C,0x10,0x00,0x00,0x08,0x38,0xC8,0x08,0x08,0x18,0x00,

/*--  文字:  [  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0xFC,0x04,0x04,0x04,0x00,

/*--  文字:  \  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x30,0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x1C,0x02,0x00,

/*--  文字:  ]  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0xFC,0x00,0x00,0x00,

/*--  文字:  ^  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x20,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  _  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  `  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  a  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0x00,0x30,0x48,0x88,0x88,0xF8,0x08,0x00,

/*--  文字:  b  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,

/*--  文字:  c  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0x00,

/*--  文字:  d  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x12,0x1F,0x00,0x00,0xF0,0x08,0x08,0x08,0x10,0xF8,0x08,

/*--  文字:  e  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0xF0,0x88,0x88,0x88,0x88,0x90,0x00,

/*--  文字:  f  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x02,0x02,0x0F,0x12,0x12,0x18,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,

/*--  文字:  g  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x03,0x02,0x00,0x00,0xAC,0x52,0x52,0x52,0x92,0x0C,0x00,

/*--  文字:  h  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x01,0x02,0x02,0x02,0x01,0x00,0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,

/*--  文字:  i  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x02,0x1A,0x1B,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,

/*--  文字:  j  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x02,0x1A,0x1B,0x00,0x00,0x00,0x06,0x02,0x02,0x02,0xFC,0x00,0x00,

/*--  文字:  k  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x10,0x1F,0x00,0x00,0x03,0x02,0x02,0x00,0x08,0xF8,0x48,0x80,0x68,0x18,0x08,0x00,

/*--  文字:  l  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x10,0x10,0x1F,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,

/*--  文字:  m  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x02,0x03,0x02,0x01,0x00,0x00,0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,

/*--  文字:  n  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,

/*--  文字:  o  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x01,0x02,0x02,0x01,0x00,0x00,0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,

/*--  文字:  p  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x02,0xFE,0x0A,0x08,0x08,0x08,0xF0,0x00,

/*--  文字:  q  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0xF0,0x08,0x08,0x08,0x12,0xFE,0x02,

/*--  文字:  r  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x02,0x03,0x01,0x02,0x02,0x03,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,

/*--  文字:  s  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x01,0x02,0x02,0x02,0x03,0x00,0x00,0x00,0x98,0x48,0x48,0x48,0x30,0x00,0x00,

/*--  文字:  t  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x02,0x02,0x0F,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0xF0,0x08,0x08,0x00,0x00,

/*--  文字:  u  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x00,0x00,0x00,0x02,0x03,0x00,0x00,0xF0,0x08,0x08,0x08,0x10,0xF8,0x08,

/*--  文字:  v  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x00,0x00,0xE0,0x18,0x20,0xC0,0x00,0x00,

/*--  文字:  w  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x00,0x03,0x00,0x03,0x02,0x00,0x00,0xC0,0x38,0xC0,0x38,0xC0,0x00,0x00,

/*--  文字:  x  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x02,0x03,0x00,0x02,0x03,0x02,0x00,0x00,0x08,0x18,0xE8,0xE0,0x18,0x08,0x00,

/*--  文字:  y  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x02,0x02,0xE2,0x1C,0x30,0xC0,0x00,0x00,

/*--  文字:  z  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x03,0x02,0x02,0x02,0x03,0x02,0x00,0x00,0x08,0x18,0x68,0x88,0x08,0x18,0x00,

/*--  文字:  {  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0x01,0x7E,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x04,0x00,0x00,

/*--  文字:  |  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,

/*--  文字:  }  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x00,0x40,0x7E,0x01,0x00,0x00,0x00,0x00,0x00,0x04,0xFC,0x00,0x00,0x00,0x00,

/*--  文字:  ~  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
0x00,0x60,0x80,0x80,0x40,0x20,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

};



void Delayms(unsigned int time)
{
	int i;
	while(time--)
	for(i=0;i<=20;i++);
}

void WrateC(unsigned char com)

{
    unsigned char  i,j,k,a,b;
	    ClrLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=com;
//			 if(com&0x80==0x0080)
//			 {
//				 P6OUT|=com&0x80 >> 2 ;                 //只改变P6.5对其他位无影响
//			 }
//			 else
//			 {
//				 P6OUT&=~(0x20) ;
//			 }

/*****************	referred from HWJ8**************/
			 a = P6OUT & 0x20;
			 b = (com & 0x80)/4;
			 if(a != b)
				 P6OUT = P6OUT ^ 0x20;
 /* **************************************************/
			 P3OUT &=~BIT4;								  //P3.4 置0
			 for(k = 0;k < 3;k ++);//延时
			 P3OUT |=BIT4;
			 for(k = 0;k < 3;k ++);//延时     
			 com=j<<1;
		}
		SetLCDRS;
}

void WrateD(unsigned char dat)

{
    unsigned char  i,j,k,a,b;
	    SetLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=dat;
			 
//			 P6OUT |=dat&0x80 >>2 ;

/*****************	referred from HWJ8**************/
			 a = P6OUT & 0x20;
			 b = (dat & 0x80)/4;
			 if(a != b)
				 P6OUT = P6OUT ^ 0x20;
/* **************************************************/

			 P3OUT &=~BIT4;
			 for(k = 0;k < 3;k ++);//延时
			 P3OUT |=BIT4;
			 for(k = 0;k < 3;k ++);//延时   
			 dat=j<<1;
		}
		ClrLCDRS;
}

void LCDWrite(unsigned char type,unsigned char dat)
{ 

	if(type)
	{
		WrateC(dat);
	}
	else
	{
		WrateD(dat);
	}
}

void LCDInit()
{
 	P6DIR |=  BIT5 + BIT4; //P6.5 LCD IO 口设置
 	P3DIR |= BIT4 + BIT2;  //P3.4 输出

// 	P3DS |=BIT2 + BIT4;
// 	P6DS |=BIT4 + BIT5;
//    P74OUT |= BIT0;             //P4.0-P4.4设置为推挽输出
	SetLCDRST;
	Delayms(10);
	ClrLCDRST;
	Delayms(10);
	SetLCDRST;
	Delayms(10);
	LCDWrite(W_CMD,0xE2);	//软件复位
	LCDWrite(W_CMD,0xA3);//Bais set		显示偏压
	LCDWrite(W_CMD,0xA0);//ADC seg镜像选择 0xa0正常，0xA1左右镜像
	LCDWrite(W_CMD,0xC0);//com output scan direction，com镜像选择 0xc0正常，0xC8上下镜像
	LCDWrite(W_CMD,0x26);
	Delayms(5);

	

	LCDWrite(W_CMD,0x2C);//内部电源管理，
	Delayms(10);
	LCDWrite(W_CMD,0x2E);//三条指令间隔时间2ms
	Delayms(10);
	LCDWrite(W_CMD,0x2F);
	Delayms(10);

//	LCDWrite(W_CMD,0x24);//电压调整寄存器高位 范围：0x21-0x27 
	LCDWrite(W_CMD,0x81);//电压模式选择
	LCDWrite(W_CMD,0x20);//电压调整寄存器低位 范围：0x00-0x3f
	Delayms(10);
	LCDWrite(W_CMD,0xF8);
	LCDWrite(W_CMD,0x01);
    Delayms(5);
	LCDWrite(W_CMD,0xAF);//显示开         
//	LCDWrite(W_CMD,0x40);//从首行开始显示
	Drawchar('c',3,10);
}


//---------------------------------------------
//LCD_set_XY: 设置LCD坐标函数
//输入参数：X：0－127  Y：0－7
//编写日期：
//---------------------------------------------
void LCD_setXY(unsigned char X, unsigned char Y)
{
	unsigned char gao,di;
	WrateC(0xB0 | Y); //页
	gao = X & 0xf0;
	gao = gao >> 4;
	di = X & 0x0f;
	WrateC(0x10 | gao);  //set Column address MSB
    WrateC(0x00 | di);  //set column address LSB

}

void LCD_draw_point(unsigned char x,unsigned char y)    
{
	LCD_setXY(x,y);
	LCDWrite(W_DAT,0xff) ;
}

void Clear()
{
   unsigned char page,j;
	 for(page=0xB7;page>=0xB0;page--)  
    {  
	LCDWrite(W_CMD,page);
	LCDWrite(W_CMD,0x10);
	LCDWrite(W_CMD,0x00);  
     for(j=0;j<128;j++)  
        {  
         WrateD(0x00);  
        }  
    } 
}

void clear_half()
{
   unsigned char page,j;
	 for(page=0xB7;page>=0xB4;page--)  
    {  
	LCDWrite(W_CMD,page);
	LCDWrite(W_CMD,0x10);
	LCDWrite(W_CMD,0x00);  
     for(j=0;j<128;j++)  
        {  
         WrateD(0x00);  
        }  
    } 
}

void DrawPoint(unsigned char x,unsigned char y)
{
    unsigned char senddat,yy;
	static unsigned char DataOld=0,yOld=0,xOld=0;
	yy=(int)(y/8);
	if((yy==yOld)&&(x==xOld))
	   senddat = DataOld | (0x80>>(y%8));
	else
	   senddat = 0x80>>(y%8);
	LCD_setXY(x,abs(yy-7));
	LCDWrite(W_DAT,senddat);
	DataOld = senddat;
	yOld=yy;
	xOld=x;
}


/*********************************************************************
*在屏幕上显示一个字符
*参数：C字符  	row 行:0~3  col 列:0~15
*********************************************************************/
void Drawchar( char c,unsigned char row,unsigned char col )
{	
    char b,Row,Col;
    unsigned char k;
	k=c-0x20;
	Row=(63-(16*row));
	Col=8*col;

	for(b = 0;b<16;b++)
	{

	 if(b<8)
	 {
	  if((AsciiFontData[k][b]&0x80)!=0)
	  DrawPoint(Col+b,Row);
	  	
	  
	  if((AsciiFontData[k][b]&0x40)!=0)
	  DrawPoint(Col+b,Row-1);
	   	
	  if((AsciiFontData[k][b]&0x20)!=0)
	  DrawPoint(Col+b,Row-2);
	   	
	  if((AsciiFontData[k][b]&0x10)!=0)
	  DrawPoint(Col+b,Row-3);

	  if((AsciiFontData[k][b]&0x08)!=0)
	  DrawPoint(Col+b,Row-4);
	  	
	  if((AsciiFontData[k][b]&0x04)!=0)
	  DrawPoint(Col+b,Row-5);
	   
	  if((AsciiFontData[k][b]&0x02)!=0)
      DrawPoint(Col+b,Row-6);
	  	
	  if((AsciiFontData[k][b]&0x01)!=0)
	  DrawPoint(Col+b,Row-7);
	  }
	  else
	  {
	   if((AsciiFontData[k][b]&0x80)!=0)
	  DrawPoint(Col+b-8,Row-8);
	  	
	  
	  if((AsciiFontData[k][b]&0x40)!=0)
	  DrawPoint(Col+b-8,Row-9);
	   	
	  if((AsciiFontData[k][b]&0x20)!=0)
	  DrawPoint(Col+b-8,Row-10);
	   	
	  if((AsciiFontData[k][b]&0x10)!=0)
	  DrawPoint(Col+b-8,Row-11);

	  if((AsciiFontData[k][b]&0x08)!=0)
	  DrawPoint(Col+b-8,Row-12);
	  	
	  if((AsciiFontData[k][b]&0x04)!=0)
	  DrawPoint(Col+b-8,Row-13);
	   
	  if((AsciiFontData[k][b]&0x02)!=0)
      DrawPoint(Col+b-8,Row-14);
	  	
	  if((AsciiFontData[k][b]&0x01)!=0)
	  DrawPoint(Col+b-8,Row-15);
	  }	  
	
	}

}

/*********************************************************************
*在屏幕上显示一串字符
*参数：C【】字符串  	row 起始行:0~3  low 起始列:0~15
*********************************************************************/
void DrawcharS(char *c,unsigned char row,unsigned char col)
{
  int flag=0,i=0;
  unsigned char R,L,TOTAL;
  TOTAL=(row*16)+col;
  if(TOTAL>63||row>3||col>15)
   {flag=1;}

  while(flag==0)
  {
   if(*c!='\0')
   {
     R=	(TOTAL+i)/16 ;
   	 L=	(TOTAL+i)%16;
	 Drawchar(*c,R,L);
	 c++;
	 i++;
	 if((TOTAL+i)>63)
	  {
	   	 flag=1;
	  }
   }
   else
   {
     flag=1;
   }
 }

}

/*********************************************************************
*在屏幕上显示数字
*参数：NO数字  	row 起始行:0~3  low 起始列:0~15
*********************************************************************/
void Drawint(unsigned int num,unsigned char row,unsigned char col)
{
	Drawchar(0x30+((num/1)%10),row,col+4);
	Drawchar(0x30+((num/10)%10),row,col+3);
	Drawchar(0x30+((num/100)%10),row,col+2);
	Drawchar(0x30+((num/1000)%10),row,col+1);
	Drawchar(0x30+((num/10000)%10),row,col+0);
}

/*********************************************************************
*在屏幕上显示浮点数字
*参数：NO数字  	row 起始行:0~3  low 起始列:0~15
*********************************************************************/
void Drawfloat2_2(float num,unsigned char row,unsigned char col)
{	if(num<0) 
  {
     num=-num;
    Drawchar('-',row,col+0);
  }   
    else	 {Drawchar('+',row,col+0);}
	Drawchar(0x30+((int)(num/10.0)%10),row,col+1);
	Drawchar(0x30+((int)(num/1.0)%10),row,col+2);
	Drawchar('.',row,col+3);
	Drawchar(0x30+((int)(num*10.0)%10),row,col+4);
	Drawchar(0x30+((int)(num*100.0)%10),row,col+5);
}

/***********************************************
*汉字无斜线

*在屏幕上显示一个汉字（16*16个点，共32个字节）
*参数： C为汉字在DzkCode中的下标位置，
		row 在LCD屏上显示的行 0-3；
		col 在LCD屏上显示的列 0-7；
*扫描方式：纵向--先左右后上下
		   高位在前

**********************************************/


/***********************************************
*显示一行汉字

*参数： C为一串下标位置，
		row 在LCD屏上显示的行 0-3；
		col 在LCD屏上显示的列 0-7；

*每行最多显示8个汉字，自动换行

**********************************************/
//void DrawhanziS(unsigned char *C,unsigned char row,unsigned char col)
//{
//  int flag=0,i=0;
//  unsigned char R,L,TOTAL;
//  TOTAL=(row*8)+col;
//  if(TOTAL>63||row>3||col>15)
//   {flag=1;}
//
//  while(flag==0)
//  {
//   if(*C!='\0')
//   {
//     R=	(TOTAL+i)/8 ;
//   	 L=	(TOTAL+i)%8;
//	 Drawhanzifix(*C,R,L);
//	 C++;
//	 i++;
//	 if((TOTAL+i)>63)
//	  {
//	   	 flag=1;
//	  }
//   }
//   else
//   {
//     flag=1;
//   }
// }
//
//}
