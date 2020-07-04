#include <DataSave/Data.h>
#include <IO.h>
#include <DataS.h>
#include <DataSave/w25qxx.h>
#include <../../../libraries/SPI/src/SPI.h>

DataSave SaveData;

DataSave::DataSave()
{
}

void DataSave::begin()
{
    uint8_t temp, temp1;
    fpioa_set_function(SPI_SCK, FUNC_SPI0_SCLK);
    fpioa_set_function(SPI_MOSI, FUNC_SPI0_D0);
    fpioa_set_function(SPI_MISO, FUNC_SPI0_D1);
    fpioa_set_function(SPI_CS, FUNC_SPI0_SS0);

    w25qxx_init();
    w25qxx_read_id(&temp, &temp1);
    Serial.printf("ID:0x%02x%02x\n", temp, temp1);
    uint8_t *data = (uint8_t *)malloc(32 * sizeof(uint8_t));
    w25qxx_read_data(0x40, data, 32);

    if (data[1] != write_buff[1])
    {
        Serial.println("init");
        w25qxx_write_data(0x40, write_buff, 32);
    }
    else
    {
        Serial.println("done");
    }
    free(data);
}

void DataSave::SaveData(VI data)
{
    // uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    // DataTran tran;
    // tran.f = data.SetV;
    // for (int i = 0; i < 4; i++)
    // {
    //     a[i] = tran.u[i];
    // }
    // tran.f = data.SetI;
    // for (int i = 0; i < 4; i++)
    // {
    //     a[i + 4] = tran.u[i];
    // }
    // WritePage(0x00, a, 8);
    // free(a);
}
void DataSave::GetData(VI *data)
{
    // uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    // ReadPage(0x00, a, 8);
    // DataTran tran;
    // for (int i = 0; i < 4; i++)
    // {
    //     tran.u[i] = a[i];
    // }
    // data->SetV = tran.f;
    // for (int i = 0; i < 4; i++)
    // {
    //     tran.u[i] = a[i + 4];
    // }
    // data->SetV = tran.f;
    // free(a);
}
void DataSave::SetSave(Mode mode, Local local, float data)
{
    // DataTran tran;
    // switch (mode)
    // {
    // case V:
    //     tran.f = data;
    //     WritePage(0x10 + local, tran.u, 4);
    //     break;
    // case I:
    //     tran.f = data;
    //     WritePage(0x20 + local, tran.u, 4);
    //     break;
    // }
}
void DataSave::GetSave(Mode mode, Local local, float *data)
{
    // DataTran tran;
    // switch (mode)
    // {
    // case V:
    //     ReadPage(0x10 + local, tran.u, 4);
    //     data[0] = tran.f;
    //     break;
    // case I:
    //     ReadPage(0x20 + local, tran.u, 4);
    //     data[0] = tran.f;
    //     break;
    // }
}
void DataSave::Remove(Mode mode, Local local)
{
    // uint8_t a[] = {0, 0, 0, 0};
    // switch (mode)
    // {
    // case V:
    //     WritePage(0x10 + local, a, 4);
    //     break;
    // case I:
    //     WritePage(0x20 + local, a, 4);
    //     break;
    // }
}