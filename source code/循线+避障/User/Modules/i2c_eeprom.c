/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "i2c_eeprom.h"

enum ENUM_I2C_EEPROM_REPLY
{
I2C_EEPROM_NACK=0
,I2C_EEPROM_ACK=1
};

enum ENUM_I2C_EEPROM_BUS_STATE
{
I2C_EEPROM_READY=0
,I2C_EEPROM_BUS_BUSY=1
,I2C_EEPROM_BUS_ERROR=2
};

void I2C_EEPROM_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  // Configure I2C1 pins: SCL and SDA 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
}

/*
 * 函数名：delay_i2c
 * 描述  ：延时
 * 输入  ：无
 * 输出  ：无
 * 调用  ：函数中调用
 */
void delay_i2c(void)
{ 
   u8 i=10; //i=10延时1.5us//这里可以优化速度 ，经测试最低到5还能写入
   while(i--); 
   
}

/*
 * 函数名：DelayMs
 * 描述  ：延时ms
 * 输入  ：无
 * 输出  ：无
 * 调用  ：函数中调用
 */
void DelayMs(uint16_t ms)
{
 u8 i;
 u16 j;
 for(i = ms; i > 0; i--)
 {
  for(j = 11998; j > 0; j--); // ( (6*j+9)*i+15 ) / 72000000 
  
 }
}

/*
 * 函数名：I2C_EEPROM_Start
 * 描述  ：起始信号
 * 输入  ：无
 * 输出  ：无
 * 调用  ：函数中调用
 */
u8 I2C_EEPROM_Start(void)
{
   SDAH;
   SCLH;
   delay_i2c();
   if(!SDAread)return I2C_EEPROM_BUS_BUSY; //SDA线为低电平则总线忙,退出
   SDAL;
   delay_i2c();
   if(SDAread) return I2C_EEPROM_BUS_ERROR; //SDA线为高电平则总线出错,退出
   SCLL;
   delay_i2c();
   return I2C_EEPROM_READY;
}

/*
 * 函数名：I2C_EEPROM_Stop
 * 描述  ：停止信号
 * 输入  ：无
 * 输出  ：无
 * 调用  ：函数中调用
 */
void I2C_EEPROM_Stop(void)
{
   SDAL;
   SCLL;
   delay_i2c();
   SCLH;
   delay_i2c();
   SDAH;
   delay_i2c();
}

void I2C_EEPROM_Ack(void)
{ 
   SCLL;
   delay_i2c();
   SDAL;
   delay_i2c();
   SCLH;
   delay_i2c();
   SCLL;
   delay_i2c();
}

void I2C_EEPROM_NoAck(void)
{ 
   SCLL;
   delay_i2c();
   SDAH;
   delay_i2c();
   SCLH;
   delay_i2c();
   SCLL;
   delay_i2c();
}

/*
 * 函数名：I2C_EEPROM_WaitAck
 * 描述  ：等待应答信号
 * 输入  ：无
 * 输出  ：无
 * 调用  ：函数中调用
 */
uint8_t I2C_EEPROM_WaitAck(void)   //返回为:=1有ACK,=0无ACK
{
 SCLL;
 delay_i2c();
 SDAH;   
 delay_i2c();
 SCLH;
 delay_i2c();
 if(SDAread)
 {
          SCLL;
          return 0;
 }
 SCLL;
 return 1;
}

/*
 * 函数名：I2C_EEPROM_SendByte
 * 描述  ：发送数据
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void I2C_EEPROM_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCLL;
        delay_i2c();
        if(SendByte&0x80)
          SDAH;  
        else 
        SDAL;   
        SendByte<<=1;
        delay_i2c();
        SCLH;
        delay_i2c();
    }
    SCLL;
}

/*
 * 函数名：I2C_EEPROM_ReceiveByte
 * 描述  ：接收数据
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
u8 I2C_EEPROM_ReceiveByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;
    SDAH;    
    while(i--)
    {
      ReceiveByte <<= 1;      
      SCLL;
      delay_i2c();
      SCLH;
      delay_i2c(); 
      if(SDAread)
      {
        ReceiveByte |= 0x01;
      }
    }
    SCLL;
    return ReceiveByte;
}

/*
 * 函数名：I2C_EEPROM_WriteByte
 * 描述  ：写入一个字节
 * 输入  ：写入1字节数据           SendByte：待写入数据    WriteAddress：待写入地址
 * 输出  ：3写入成功；0写器件地址出错，1总线忙，2出错
 * 调用  ：外部调用
 */ 
u8 I2C_EEPROM_WriteByte(u8 SendByte, u8 WriteAddress)
{  
    u8 i;
   // u16 j;
 i = I2C_EEPROM_Start();
    if(i)
   return i;
      
    I2C_EEPROM_SendByte( ADDR_24CXX & 0xFE);//写器件地址  写入：地址最低位是0，读取：地址最低位是1
    
 if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
 
    I2C_EEPROM_SendByte(WriteAddress);   //设置起始地址      
    I2C_EEPROM_WaitAck(); 
    I2C_EEPROM_SendByte(SendByte);           //写数据
    I2C_EEPROM_WaitAck();   
    I2C_EEPROM_Stop(); 
 //注意：因为这里要等待EEPROMPROM写完，可以采用查询或延时方式(10ms)
    DelayMs(20); //写入延时 12ms  写周期大于10ms即可
    return 3;
}
 
/*
 * 函数名：I2C_EEPROM_WriteByte
 * 描述  ：读出一个字节
 * 输入  ：字节地址
 * 输出  ：0写器件地址出错，1总线忙，2出错,
 * 调用  ：外部调用
 */ 
u8 I2C_EEPROM_ReadByte( u8 ReadAddress)
{  
    u8 i,temp;
    i = I2C_EEPROM_Start();
    if(i)
   return i;
     
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE));//写器件地址，先执行一次伪写操作 
    if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
    I2C_EEPROM_SendByte(ReadAddress);   //设置起始地址      
    I2C_EEPROM_WaitAck();
    I2C_EEPROM_Start();
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE)|0x01);    //读器件地址    写入：地址最低位是0，读取：地址最低位是1
    I2C_EEPROM_WaitAck();
   
    //*pDat = I2C_EEPROM_ReceiveByte();
    temp = I2C_EEPROM_ReceiveByte();
    
    I2C_EEPROM_NoAck();
     
    I2C_EEPROM_Stop();
    return temp;//返回的如果是0，1，2则与错误代码相同了，再考虑一下
}
/***************************************************************************
向24c256中写多个字节
psrc_data：指向要写入数据数组的指针
adr：24c256中要写入数据的首地址
nbyte：写入的字节数
返回值:  0：执行完毕；1：执行出现错误
形参中：C02只有一个地址adr；C256中有高位地址hadr和低位地址ladr
***************************************************************************/
u8 I2C_EEPROM_BufferWrite(u8 *psrc_data,u8 adr,u8 nbyte)
{
   u8 i;
  
 for(;nbyte!=0;nbyte--)
 {
  i = I2C_EEPROM_Start();
        if(i)
     return i;
         
        I2C_EEPROM_SendByte( ADDR_24CXX & 0xFE);//写器件地址 
    
     if(!I2C_EEPROM_WaitAck())
     {
       I2C_EEPROM_Stop(); 
       return 0;
     }
 
        I2C_EEPROM_SendByte(adr);   //设置起始地址      
        I2C_EEPROM_WaitAck(); 
        I2C_EEPROM_SendByte(*psrc_data);           //写数据
        I2C_EEPROM_WaitAck();   
        psrc_data++;    //指向待写数据的指针加1
  adr++;    //对24C08的操作地址加1 
        I2C_EEPROM_Stop(); 
  //注意：因为这里要等待EEPROMPROM写完，可以采用查询或延时方式(10ms)
        DelayMs(12); //写入延时 12ms  写周期大于10ms即可
        
 }
 return 0;
}

/***************************************************************************
从24c02读多个字节
pdin_data：指向要保存读出数据的数组的指针
adr：24c02中要读出数据的首地址
nbyte：读出的字节数
返回值:  0：执行完毕；1：执行出现错误
***************************************************************************/
u8 I2C_EEPROM_BufferRead(u8 *pdin_data,u8 adr,u8 nbyte)
{
   u8 i;
    i = I2C_EEPROM_Start();
    if(i)
   return i;
     
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE));//写器件地址，先执行一次伪写操作 
    if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
 I2C_EEPROM_SendByte(adr);   //设置起始地址      
    I2C_EEPROM_WaitAck();
    I2C_EEPROM_Start();
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE)|0x01);    //读器件地址    写入：地址最低位是0，读取：地址最低位是1
    I2C_EEPROM_WaitAck();
 while(nbyte!=1)                 //读入前(nbyte-1)个字节
 {
  *pdin_data = I2C_EEPROM_ReceiveByte(); //循环从24C02中读数据，存入pdin_data所指的存储器中
  I2C_EEPROM_Ack();   //IIC应答
  pdin_data++;  //指向存储读入数据的存储器指针加1
  nbyte--;  //剩余要读入的字节减1
 };
 *pdin_data = I2C_EEPROM_ReceiveByte();  //读入最后一个字节
 I2C_EEPROM_NoAck();      //IIC无应答操作
     
    I2C_EEPROM_Stop();   
 
 return 0;
}

