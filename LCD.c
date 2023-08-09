// Define la frecuencia del microcontrolador y funci�n de retardo
#define _XTAL_FREQ 8000000


// Incluir las librer�as
#include "LCD.h"

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0
    PORTD = a;
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0); // Comando para borrar la memoria interna del LCD
    Lcd_Cmd(1); // Comando para desplazar el cursor a la posici�n inicial y borrar la pantalla
}

void Lcd_Set(char a, char b) {
    if (a == 1){
        Lcd_Cmd((b & 0x0F)|0x80); // Posici�n del cursor en la l�nea 1
    }
else if (a == 2){
        Lcd_Cmd((b & 0x0F)|0xC0); // Posici�n del cursor en la l�nea 2
    }
}

void Lcd_Init(void) {
    PORTD = (0x00); // Establece el puerto de datos en 0x00
    __delay_ms(15);
    // Configura el LCD en modo 8 bits y 2 l�neas
    Lcd_Cmd(0x30);      //0011 0000
    __delay_ms(4);
    Lcd_Cmd(0x30);      //0011 0000
    __delay_us(100);
    Lcd_Cmd(0x30);      //0011 0000
    // Configura el modo de pantalla (2 l�neas y matriz de 5x8)
    Lcd_Cmd(0x38);      //0011 1000
    // Configura el desplazamiento del cursor
    Lcd_Cmd(0x00);      //0000 1000
    // Borra la pantalla y coloca el cursor en la posici�n inicial
    Lcd_Cmd(0x0C);      //0000 0001
    // Configura el modo de entrada del LCD
    Lcd_Cmd(0x00);      //0000 0110
    // Apaga el desplazamiento del cursor
    Lcd_Cmd(0x06);      //0001 0000
    // Enciende el LCD sin mostrar el cursor ni el parpadeo

}

void Lcd_Write(char a) {
    RS = 1; // => RS = 1
    PORTD = a; // Data transfer
    EN = 1; // => E = 1
    __delay_us(40);
    EN = 0; // => E = 0
}

void Lcd_Write_Str(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++) // Recorre la cadena de caracteres hasta el final ('\0')
        Lcd_Write(a[i]); // Escribe cada car�cter en el LCD utilizando la funci�n Lcd_Write
}

void Lcd_ShiftR(void) {
    Lcd_Cmd(0x01); // Env�a comando para borrar la pantalla
    Lcd_Cmd(0x0C); // Env�a comando para activar el desplazamiento del texto hacia la derecha
}

void Lcd_ShiftL(void) {
    Lcd_Cmd(0x01); // Env�a comando para borrar la pantalla
    Lcd_Cmd(0x08); // Env�a comando para activar el desplazamiento del texto hacia la izquierda
}