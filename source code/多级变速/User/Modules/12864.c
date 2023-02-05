#include "12864.h"

#define uchar unsigned char
#define uint unsigned int
#define GPIOA_ODR_A  (GPIOA_BASE+0x0C)
#define GPIOA_IDR_A  (GPIOA_BASE+0x08)
#define GPIOB_ODR_A  (GPIOB_BASE+0x0C)
#define GPIOB_IDR_A  (GPIOB_BASE+0x08)
#define GPIOC_ODR_A  (GPIOC_BASE+0x0C)
#define GPIOC_IDR_A  (GPIOC_BASE+0x08)
#define GPIOD_ODR_A  (GPIOD_BASE+0x0C)
#define GPIOD_IDR_A  (GPIOD_BASE+0x08)
#define GPIOE_ODR_A  (GPIOE_BASE+0x0C)
#define GPIOE_IDR_A  (GPIOE_BASE+0x08)
#define BitBand(Addr,BitNum)    *((volatile unsigned long *)((Addr&0xF0000000)+0x2000000+((Addr&0xfffff)<<5)+(BitNum<<2)))

#define PAout(n)   BitBand(GPIOA_ODR_A,n)
#define PAin(n)    BitBand(GPIOA_IDR_A,n)
#define PBout(n)   BitBand(GPIOB_ODR_A,n)
#define PBin(n)    BitBand(GPIOB_IDR_A,n)
#define PCout(n)   BitBand(GPIOC_ODR_A,n)
#define PCin(n)    BitBand(GPIOC_IDR_A,n)
#define PDout(n)   BitBand(GPIOD_ODR_A,n)
#define PDin(n)    BitBand(GPIOD_IDR_A,n)
#define PEout(n)   BitBand(GPIOE_ODR_A,n)
#define PEin(n)    BitBand(GPIOE_IDR_A,n)
#define SCL PCout(12)    // E      
#define SDA PCout(11)   //R/W      
#define CS  PCout(10)   //RS

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uchar PointH[32][16];
uchar PointL[32][16];
unsigned char adress_table[]=                 //定义液晶点阵的坐标
{ 
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,      //第一行汉字位置 
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,      //第二行汉字位置 
0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,      //第三行汉字位置 
0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F       //第四行汉字位置 
};
/*************************************************************/
/*                      初始化液晶接口                       */
/*************************************************************/
void lcd_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIOB, GPIOC and AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO , ENABLE);  //RCC_APB2Periph_AFIO
  
  /* LEDs pins configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void LCD_12864_init(void) 
{
 SCL = 0;
 SDA = 0;
 CS = 0;
 lcd_config();
 lcd_clear();
 delay_ms(10);
 clrRAM_12864();
 delay_ms(10);
 lcd_string(0,0,"    小二科技    ");
 lcd_string(2,0,"   wifi-robots  ");
}


/*************************************************************/
/*                   IIC写一个字节的数据                     */
/*************************************************************/
void write_byte(unsigned char A) 
{ 
  unsigned char j; 
  for(j=0;j<8;j++)        
  { 
    if((A<<j)&0x80)SDA=1; 
    else SDA=0; 
    SCL=1;
    delay_1(1);
    SCL=0;
    delay_1(1);
  } 
} 

/*************************************************************/
/*                     向液晶发送数据                        */
/*************************************************************/
void write_Data(unsigned char C) 
{ 
  CS=1; 
  SCL=0; 
  write_byte(0xFA); 
  write_byte(C&0xF0);          //写高四位数据 
  write_byte(0xf0&(C<<4));            //写低四位数据 
  CS=0; 
  delay_1(50);
} 

/*************************************************************/
/*                      向液晶发送命令                       */
/*************************************************************/
void write_command(unsigned char B) 
{ 
  CS=1; 
  SCL=0; 
  write_byte(0xF8); 
  write_byte(B&0xF0);        //写高四位数据 
  write_byte(0xf0&(B<<4));        //写低四位数据 
  CS=0; 
  delay_1(50);
} 


/***************************************************************************/
/*                            清屏子程序                                   */
/***************************************************************************/
void lcd_clear(void)
{
    write_command(0x30);//0011,0000 功能设置，一次送8位数据，基本指令集 
    write_command(0x03);//AC归0,不改变DDRAM内容 
    write_command(0x01);//0000,0001 清DDRAM 
    write_command(0x06);//写入时,游标右移动 
    write_command(0x0C);//0000,1100  整体显示，游标off，游标位置off  
}

/***************************************************************************/
/*                           向LCD发送字符串                               */
/***************************************************************************/
void lcd_string(unsigned char row,unsigned char col,char *data1)   //row为写入数据所在的行数,col为写入数据所在的列数，*data1为写入的数据
{
  for(;row<4&&(*data1)!=0;row++)
  { 
      for(;col<8&&(*data1)!=0;col++)
      { 
          write_command(adress_table[row*8+col]);
          delay(50);       //延时50us
           
          write_Data(*data1++); 
          delay(50);       //延时50us
          write_Data(*data1++); 
          delay(50);       //延时50us
      } 
      col=0; 
  }
}

//清屏函数
 //正行的清屏函数速度较快          

void clrRAM_12864(void)
{
 uchar i, j, k ;
 write_command(0x34);//打开扩展指令集，绘图显示关
 write_command(0x36);//打开扩展指令集，绘图显示开
 for( i = 0 ; i < 2 ; i++ )//分上下两屏写
 {
      for( j = 0 ; j < 32 ; j++ )
      {
          write_command( 0x80 + j ) ;//写Y 坐标
          //delay1ms(1);
          if( i == 0 )//写X 坐标
          {
              write_command( 0x80 ) ;
     
          }
          else //写下                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                半屏
          {
          write_command( 0x88 ) ;
  
          }
          for( k = 0 ; k < 16 ; k++ ) //写一整行数据
          {
              write_Data(0x00) ;
          }
      }
  }
  write_command(0x30);
} 
//********************************************************
//画点函数
//参数：color=1，该点填充(1)；color=0，该点填充(0)；
//********************************************************

void Point_Display(uchar x,uchar y,uchar color)
{
   uchar x_dyte,x_byte;//横坐标在哪一个字节，哪一位
   uchar y_dyte,y_byte;//纵坐标在哪一个字节，哪一位


   write_command(0x34);
   write_command(0x36);	
   
   //x,y的坐标互换，即普通的x，y坐标
   x_dyte=x/16;       //算出它在哪一个字节（地址） 
                      //一个地址是16位的 
   x_byte=x&0x0f;      //算出他在哪一位
   y_dyte=y/32;       //确定是上半屏还是下半屏 
                      //0:上半屏，1下半屏
   y_byte=y&0x1f;      //计算0~31当中的哪一行，即确定是在第几行
   
 
   //delay1ms(1); 
   write_command(0x80+y_byte);//先写垂直坐标(最高位必须为1)
   write_command(0x80+x_dyte+8*y_dyte);//水平坐标
                                        //下半屏的水平坐标起始地址为0x80
										//(+8*y_byte)来确定
										//是用上半屏还是下半屏
    if(x_byte<8)
    {
	 if(color==1) {
	  
	 PointH[y_byte][x_dyte+8*y_dyte] |=0X01<<(7-x_byte);
	 write_Data(PointH[y_byte][x_dyte+8*y_dyte]);
	 }//写高字节因为坐标是从左到右的
    else {
    PointH[y_byte][x_dyte+8*y_dyte] &=~(0X01<<(7-x_byte));  
	 write_Data(PointH[y_byte][x_dyte+8*y_dyte]);
    }
	 write_Data(PointL[y_byte][x_dyte+8*y_dyte]);                  //原数据送回
    }
    else
    { 
     write_Data(PointH[y_byte][x_dyte+8*y_dyte]); 
	  if(color==1) {
	   PointL[y_byte][x_dyte+8*y_dyte]|=0x01<<(15-x_byte); 
     write_Data(PointL[y_byte][x_dyte+8*y_dyte]);
	  }
     else {
    PointL[y_byte][x_dyte+8*y_dyte]&=~(0x01<<(15-x_byte));  
	  write_Data(PointL[y_byte][x_dyte+8*y_dyte]); 
     }
	}
    write_command(0x30);
}

//下面是线显示
//横线显示当y相等时
void Line_Display_Horizontal(uchar x0,uchar x1,uchar y,uchar color)
{
 uchar t;
 if(x0 > x1)
 {
  t=x1;
  x1=x0;
  x0=t;
 }
 for(;x0 <= x1;x0++)
 {
  Point_Display(x0,y,color);
 }
}

//竖线显示当x相等时
void Line_Display_Vertical(uchar x,uchar y0,uchar y1,uchar color)
{
 uchar z;
 if(y0>y1)
 {
  z=y1;
  y1=y0;
  y0=z;
 }
 for(;y0<=y1;y0++)
 {
  Point_Display(x,y0,color);
 }
 write_command(0x30);
}

//下面是两种不同的表达形式
//第一种这个是把bresenham算法的结论来做的算法
void Line_Display_Arbitrarily(uchar x0,uchar y0,uchar x1,uchar y1,uchar color)
{
 int temp;
 int dx,dy;
 int s1,s2,status,i;
 int Dx,Dy,sub;
 dx=x1-x0;
 if(dx>=0)//判断x是增加还是减小
  s1=1;
 else
  s1=-1;
 dy=y1-y0;
 if(dy>=0)//判断x是增加还是减小
  s2=1;
 else
  s2=-1;
  
 if(dx<0)
 Dx=-dx;
 else
 Dx=dx;
 if(dy<0)
 Dy=-dy;
 else
 Dy=dy;
 
 if(Dy>Dx) //以角度45为分界线，靠近y轴是status=1,靠近x轴是status=0
 {
  temp=Dx;
  Dx=Dy;
  Dy=temp;
  status=1;
 }
 else
  status=0;
//判断垂直线和水平线
if(dx==0)
Line_Display_Vertical(x0,y0,y1,color);
if(dy==0)
Line_Display_Horizontal(x0,x1,y0,color);
 
//bresenham算法画任意两点的直线
 sub=2*Dy-Dx;//第一次判断下一个点的位置 
 for(i=0;i<Dx;i++)
 {
  Point_Display(x0,y0,color);//画出第一个点
  if(sub>=0)
  {
   if(status==1)//靠近y轴
    x0=x0+s1;    //x加1
   else         //靠近x轴
    y0=y0+s2;   //y加1
   sub=sub-2*Dx;//计算下一个点的位置	
  }
   if(status==1)
    y0=y0+s2;
   else
    x0=x0+s1;
   sub=sub+2*Dy; 
 }
 write_command(0x30);
}

void Round_Display_Hollow(uchar x,uchar y,uchar r)
{
 int a,b;
 int di;
 a=0;b=r;
 di=3-2*r;//判断下一个点的位置的标志
 while(a<=b)
 {
  Point_Display(x-b,y-a,1);//3
  Point_Display(x+b,y-a,1);//0
  Point_Display(x-a,y+b,1);//1
  Point_Display(x-b,y-a,1);//7
  Point_Display(x-a,y-b,1);//2
  Point_Display(x+b,y+a,1);//4
  Point_Display(x+a,y-b,1);//5
  Point_Display(x+a,y+b,1);//6
  Point_Display(x-b,y+a,1);
  a++;
  //使用bresenham算法画圆
  if(di<0)
   di=di+4*a+6;        
  else
   {
   	di=di+10+4*(a-b);
	b--;
   }
  Point_Display(x+a,y+b,1); 
 }
 write_command(0x30);
}
//画实心圆
void Round_Display_Solid(uchar x,uchar y,uchar r)
{
 uchar dx,dy,ref;
 uchar Temp;

if(r == 0)return;
dx = r;
dy = 1;
ref =(uchar)( 707 * r / 1000);      // 0.707r
while(dy <= dx)
{
   if(dx > ref)
    Line_Display_Arbitrarily(x+ref+1,y+dy,x+dx,y+dy,1);
   if(x>=ref+1&&dx>ref)
   {
    if(x<dx)
     Temp=0;
    else
     Temp=x-dx;
    Line_Display_Arbitrarily(Temp,y + dy,x-ref-1,y+dy,1);
   }
   
   if(y>=dy&&dx>ref)
    Line_Display_Arbitrarily(x+ref+1,y-dy,x+dx,y-dy,1);
   if(x>=ref+1&&y>=dy&&dx>ref)
   {
    if(x<dx)
     Temp=0;
    else
     Temp=x-dx;
     Line_Display_Arbitrarily(Temp,y-dy,x-ref-1,y-dy,1);
   }
   if(dy!=dx||dx==ref)
   {
    if(y<dx)
     Temp=0;
    else
     Temp=y-dx;
    Line_Display_Arbitrarily(x+dy,Temp,x+dy,y+dx,1);
   }
   if(x>=dy&&(dy!=dx||dy==ref))
   {
    if(y<dx)
     Temp = 0;
    else
     Temp=y-dx;
    Line_Display_Arbitrarily(x - dy, Temp, x - dy, y + dx,1);
   } 
   dy++;
   if((r*r-dy*dy)<=(dx-1)*dx)
   dx--; 
} 
Line_Display_Arbitrarily(x+ref+1,y,x+r,y,1);
if(x >= ref + 1)
{
   if(x<r)
    Temp=0;
   else
    Temp=x-r;
    Line_Display_Arbitrarily(Temp,y,x-ref-1,y,1);
}
if(y<r)
   Temp=0;
else
   Temp=y-r;
   Line_Display_Arbitrarily(x,Temp,x,y+r,1);
 write_command(0x30);
}
static void delay_1(vu32 nCount)
{
  vu32 i = 0;   
   while(nCount--) 
   { 
      i=2;  //自己定义 
      while(i--) ;     
   } 
}
static void delay(vu32 nCount)
{
  vu32 i = 0;   
   while(nCount--) 
   { 
      i=10;  //自己定义 
      while(i--) ;     
   } 
}

static void delay_ms(vu32 nCount)
{
  vu32 i = 0;   
   while(nCount--) 
   { 
      i=12000;  //自己定义 
      while(i--) ;     
   } 
}
