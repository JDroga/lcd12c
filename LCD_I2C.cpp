#include "LCD_I2C.h"

LCD_I2C::LCD_I2C(PinName sda, PinName scl) : _i2c(sda, scl) {
    _i2c.frequency(100000);  // Configura la frecuencia de la comunicación I2C (100 kHz)
}

// Función para inicializar el LCD
void LCD_I2C::init() {
    wait(0.05);  // Espera 50ms para la inicialización
    sendCommand(0x30);  // Inicia LCD en modo de 4 bits
    wait(0.005);
    sendCommand(0x30);
    wait(0.001);
    sendCommand(0x30);
    wait(0.01);
    sendCommand(0x20);  // Configura el LCD en modo de 4 bits
    wait(0.01);
    sendCommand(0x28);  // 2 líneas y 5x8 caracteres
    sendCommand(0x0C);  // Enciende la pantalla
    sendCommand(0x06);  // Modo de entrada, incrementa el cursor
    clear();  // Limpia la pantalla
}

// Función para borrar la pantalla LCD
void LCD_I2C::clear() {
    sendCommand(0x01);  // Comando de limpiar pantalla
    wait(0.02);         // Espera suficiente para completar la acción
}

// Función para escribir caracteres en la pantalla LCD
void LCD_I2C::print(const char* str) {
    while (*str) {
        sendData(*str++);
    }
}

// Función para configurar la posición del cursor
void LCD_I2C::setCursor(int row, int col) {
    uint8_t addr = 0x80;  // Dirección del cursor en la primera línea
    if (row == 1) {
        addr = 0xC0;  // Dirección del cursor en la segunda línea
    }
    addr += col;  // Ajusta la columna
    sendCommand(addr);
}

// Función para enviar un comando al LCD
void LCD_I2C::sendCommand(uint8_t cmd) {
    char data[4];
    data[0] = (cmd & 0xF0) | 0x0C;  // Envia el primer nibble
    data[1] = (cmd & 0xF0) | 0x08;  // Envia el primer nibble (sin habilitar el EN)
    data[2] = ((cmd << 4) & 0xF0) | 0x0C;  // Envia el segundo nibble
    data[3] = ((cmd << 4) & 0xF0) | 0x08;  // Envia el segundo nibble (sin habilitar el EN)

    _i2c.write(LCD_ADDR, data, 4);  // Envia el comando al LCD por I2C
}

// Función para enviar datos al LCD
void LCD_I2C::sendData(uint8_t data) {
    char data_buf[4];
    data_buf[0] = (data & 0xF0) | 0x0D;  // Envia el primer nibble con RS activado
    data_buf[1] = (data & 0xF0) | 0x09;  // Envia el primer nibble (sin habilitar el EN)
    data_buf[2] = ((data << 4) & 0xF0) | 0x0D;  // Envia el segundo nibble
    data_buf[3] = ((data << 4) & 0xF0) | 0x09;  // Envia el segundo nibble (sin habilitar el EN)

    _i2c.write(LCD_ADDR, data_buf, 4);  // Envia los datos al LCD por I2C
}
