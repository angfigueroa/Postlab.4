// Incluir las librer�as
#include <xc.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000

// Configuraci�n del ADC
void ADC_CONF(int frec){
    
    ADCON0bits.ADON = 1; // Habilitar ADC

    ADCON0bits.CHS = 0b0101; // Selecciona el canal para conversi�n

    ADCON1bits.ADFM = 0; // Justificaci�n a la izquierda
    ADCON1bits.VCFG0 = 0; // Vref- se conecta a VSS
    ADCON1bits.VCFG1 = 0; // Vref+ se conecta a VDD

    ADCON0bits.GO = 0; // Limpia el bit de inicio

    // Configura el tiempo de adquisici�n del ADC seg�n la frecuencia
    switch(frec){
        case 1:
            ADCON0bits.ADCS = 0B00; // Fosc/2 
            break;
        case 4:
            ADCON0bits.ADCS = 0B01; // Fosc/8
            break;
        case 8:
            ADCON0bits.ADCS = 0B10; // Fosc/32 
            break;
    }
}

// Funci�n para realizar una conversi�n ADC en modo de barrido continuo
void ADC_IF(){
    if (ADCON0bits.GO == 0){ // Si el ADC no est� en proceso de conversi�n
           
            __delay_us(50); // Peque�o retardo para estabilizar la se�al
            ADCON0bits.GO = 1; // Iniciar una nueva conversi�n
 }
}

