#ifndef _LCD_H__
#define  __LCD_H__
	#define		W_CMD	1			//指令
	#define		W_DAT	0			//数据
	#define SetLCDRS 	 P3OUT |= BIT2 		 //宏定义，对LCD_RS进行位操作
	#define ClrLCDRS 	 P3OUT &= ~BIT2
	#define SetLCDRST	 P6OUT |= BIT4 		 //宏定义，对LCD_RST进行位操作
	#define ClrLCDRST 	 P6OUT &= ~BIT4
	void Delayms(unsigned int ms);
	void WrateC(unsigned char com);
	void WrateD(unsigned char dat);
	void LCDWrite(unsigned char type,unsigned char dat);
	void LCDInit();
	void LCD_setXY(unsigned char X, unsigned char Y);
	void LCD_draw_point(unsigned char x,unsigned char y);
	void DrawPoint(unsigned char x,unsigned char y);
	void Clear();
	void clear_half();
	void Drawchar( char c,unsigned char row,unsigned char col);
	void DrawcharS(char *c,unsigned char row,unsigned char col);
	void Drawint(unsigned int num,unsigned char row,unsigned char col);
	void Drawfloat2_2(float num,unsigned char row,unsigned char col);


#endif
