#include <DataSave/Data.h>
#include <IO.h>
#include <DataS.h>

DataSave SaveData;

DataSave::DataSave()
{
}
uint8_t bit = 0;
uint8_t DataSave::READ_SDA(void)
{
    uint8_t data = digitalRead(I2C_SDA);
    return data;
}

void DataSave::SDA_OUT(void)
{
    pinMode(I2C_SDA, OUTPUT);
}
void DataSave::SDA_IN(void)
{
    pinMode(I2C_SDA, INPUT_PULLUP);
}

//产生IIC起始信号
void DataSave::IIC_Start(void)
{
    SDA_OUT(); //sda线输出
    digitalWrite(I2C_SDA, HIGH);
    digitalWrite(I2C_SCL, HIGH);
    delayMicroseconds(40);
    digitalWrite(I2C_SDA, LOW); //START:when CLK is high,DATA change form high to low
    delayMicroseconds(40);
    digitalWrite(I2C_SCL, LOW); //钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void DataSave::IIC_Stop(void)
{
    SDA_OUT(); //sda线输出
    digitalWrite(I2C_SCL, LOW);
    digitalWrite(I2C_SDA, LOW); //STOP:when CLK is high DATA change form low to high
    delayMicroseconds(40);
    digitalWrite(I2C_SCL, HIGH);
    digitalWrite(I2C_SDA, HIGH); //发送I2C总线结束信号
    delayMicroseconds(40);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t DataSave::IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN(); //SDA设置为输入
    digitalWrite(I2C_SDA, HIGH);
    delayMicroseconds(10);
    digitalWrite(I2C_SCL, HIGH);
    delayMicroseconds(10);
    while (READ_SDA())
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC_Stop();
            Serial.println("wait error");
            return 1;
        }
    }
    digitalWrite(I2C_SCL, LOW); //时钟输出0
    return 0;
}
//产生ACK应答
void DataSave::IIC_Ack(void)
{
    digitalWrite(I2C_SCL, LOW);
    SDA_OUT();
    digitalWrite(I2C_SDA, LOW);
    delayMicroseconds(20);
    digitalWrite(I2C_SCL, HIGH);
    delayMicroseconds(20);
    digitalWrite(I2C_SCL, LOW);
}
//不产生ACK应答
void DataSave::IIC_NAck(void)
{
    digitalWrite(I2C_SCL, LOW);
    SDA_OUT();
    digitalWrite(I2C_SDA, HIGH);
    delayMicroseconds(20);
    digitalWrite(I2C_SCL, HIGH);
    delayMicroseconds(20);
    digitalWrite(I2C_SCL, LOW);
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void DataSave::IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    digitalWrite(I2C_SCL, LOW); //拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        if ((txd & 0x80) >> 7)
            digitalWrite(I2C_SDA, HIGH);
        else
            digitalWrite(I2C_SDA, LOW);
        txd <<= 1;
        delayMicroseconds(20); //对TEA5767这三个延时都是必须的
        digitalWrite(I2C_SCL, HIGH);
        delayMicroseconds(20);
        digitalWrite(I2C_SCL, LOW);
        delayMicroseconds(20);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t DataSave::IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN(); //SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        digitalWrite(I2C_SCL, LOW);
        delayMicroseconds(20);
        digitalWrite(I2C_SCL, HIGH);
        receive <<= 1;
        if (READ_SDA())
            receive++;
        delayMicroseconds(20);
    }
    if (!ack)
        IIC_NAck(); //发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}

void DataSave::begin()
{
    pinMode(I2C_SDA, OUTPUT);
    pinMode(I2C_SCL, OUTPUT);

    digitalWrite(I2C_SDA, HIGH);
    digitalWrite(I2C_SCL, HIGH);

    uint8_t temp;
    temp = ReadByte(255); //避免每次开机都写AT24CXX
    Serial.printf("read:%d\n", temp);
    if (temp != 0X55)     //排除第一次初始化的情况
    {
        WriteByte(255, 0X55);
        temp = ReadByte(255);
        if (temp == 0X55)
            Serial.println("done");
        else
        {
            Serial.println("error");
        }
    }
}

void DataSave::WriteByte(uint8_t address, uint8_t data)
{
    IIC_Start();
    if (EE_TYPE > AT24C16)
    {
        IIC_Send_Byte(0XA0); //发送写命令
        IIC_Wait_Ack();
        IIC_Send_Byte(address >> 8); //发送高地址
    }
    else
    {
        IIC_Send_Byte(0XA0 + ((address / 256) << 1)); //发送器件地址0XA0,写数据
    }
    IIC_Wait_Ack();
    IIC_Send_Byte(address % 256); //发送低地址
    IIC_Wait_Ack();
    IIC_Send_Byte(data); //发送字节
    IIC_Wait_Ack();
    IIC_Stop(); //产生一个停止条件
    delay(10);
}
void DataSave::WritePage(uint8_t address, uint8_t *data, uint8_t length)
{
    while (length--)
    {
        WriteByte(address, *data);
        address++;
        data++;
    }
}
uint8_t DataSave::ReadByte(uint8_t address)
{
    uint8_t temp = 0;
    IIC_Start();
    if (EE_TYPE > AT24C16)
    {
        IIC_Send_Byte(0XA0); //发送写命令
        IIC_Wait_Ack();
        IIC_Send_Byte(address >> 8); //发送高地址
        IIC_Wait_Ack();
    }
    else
        IIC_Send_Byte(0XA0 + ((address / 256) << 1)); //发送器件地址0XA0,写数据

    IIC_Wait_Ack();
    IIC_Send_Byte(address % 256); //发送低地址
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(0XA1); //进入接收模式
    IIC_Wait_Ack();
    temp = IIC_Read_Byte(0);
    IIC_Stop(); //产生一个停止条件
    return temp;
}
void DataSave::ReadPage(uint8_t address, uint8_t *data, uint8_t length)
{
    while (length)
    {
        *data++ = ReadByte(address++);
        length--;
    }
}

void DataSave::SaveData(VI data)
{
    uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    DataTran tran;
    tran.f = data.SetV;
    for (int i = 0; i < 4; i++)
    {
        a[i] = tran.u[i];
    }
    tran.f = data.SetI;
    for (int i = 0; i < 4; i++)
    {
        a[i + 4] = tran.u[i];
    }
    WritePage(0x00, a, 8);
    free(a);
}
void DataSave::GetData(VI *data)
{
    uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    ReadPage(0x00, a, 8);
    DataTran tran;
    for (int i = 0; i < 4; i++)
    {
        tran.u[i] = a[i];
    }
    data->SetV = tran.f;
    for (int i = 0; i < 4; i++)
    {
        tran.u[i] = a[i + 4];
    }
    data->SetV = tran.f;
    free(a);
}
void DataSave::SetSave(Mode mode, Local local, float data)
{
    DataTran tran;
    switch (mode)
    {
    case V:
        tran.f = data;
        WritePage(0x10 + local, tran.u, 4);
        break;
    case I:
        tran.f = data;
        WritePage(0x20 + local, tran.u, 4);
        break;
    }
}
void DataSave::GetSave(Mode mode, Local local, float *data)
{
    DataTran tran;
    switch (mode)
    {
    case V:
        ReadPage(0x10 + local, tran.u, 4);
        data[0] = tran.f;
        break;
    case I:
        ReadPage(0x20 + local, tran.u, 4);
        data[0] = tran.f;
        break;
    }
}
void DataSave::Remove(Mode mode, Local local)
{
    uint8_t a[] = {0, 0, 0, 0};
    switch (mode)
    {
    case V:
        WritePage(0x10 + local, a, 4);
        break;
    case I:
        WritePage(0x20 + local, a, 4);
        break;
    }
}