#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "mbed.h"

// Dirección del LCD, puede variar según tu configuración
#define LCD_ADDR 0x4E  // O 0x27

class LCD_I2C {
public:
    LCD_I2C(PinName sda, PinName scl);
    void init();
    void clear();
    void print(const char* str);
    void setCursor(int row, int col);

private:
    I2C _i2c;
    void sendCommand(uint8_t cmd);
    void sendData(uint8_t data);
};

#endif
