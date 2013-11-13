
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_ON & CLKOUTEN_OFF & IESO_ON & FCMEN_OFF);
__CONFIG(WRT_OFF & VCAPEN_OFF & STVREN_OFF & BORV_LO & LPBOR_OFF & LVP_OFF);


#include "user.h"


unsigned char channel;
unsigned char byte1Out;
unsigned char byte2Out;
unsigned char count;

#define BOARDB

unsigned char processCommand(unsigned char in){
    unsigned int value;

    if(in!=0x00){
       SDO_CONFIG = 0;
       channel = 0;
#ifdef BOARDA
       setPinValue(0,in&0x01?1:0);
       setPinValue(1,in&0x02?1:0);
       setPinValue(2,in&0x04?1:0);
       setPinValue(3,in&0x08?1:0);
       setPinValue(12,in&0x10?1:0);
       setPinValue(4,in&0x20?1:0);
       setPinValue(5,in&0x40?1:0);
#else
       setPinValue(0,in&0x01?1:0);
       setPinValue(1,in&0x02?1:0);
       setPinValue(2,in&0x04?1:0);
       setPinValue(3,in&0x08?1:0);
       setPinValue(12,in&0x10?1:0);
       setPinValue(11,in&0x20?1:0);
       setPinValue(10,in&0x40?1:0);
#endif
    }
    SDO_CONFIG = 0;
    value = getPinValue(channel);
    channel++;
    return (0xFF00 & value)>>8;
}

void setPinModes(){



#ifdef BOARDA
setPinType(0,LED);
setPinType(1,LED);
setPinType(2,LED);
setPinType(3,LED);
setPinType(4,LED);
setPinType(5,LED);
setPinType(6,KNOB);
setPinType(7,KNOB);
setPinType(8,KNOB);
setPinType(9,KNOB);
setPinType(10,KNOB);
setPinType(11,KNOB);
setPinType(12,LED);
setPinType(13,BUTTON);
setPinType(14,BUTTON);
setPinType(15,UNUSED);
#else
setPinType(0,LED);
setPinType(1,LED);
setPinType(2,LED);
setPinType(3,LED);
setPinType(4,UNUSED);
setPinType(5,UNUSED);
setPinType(6,UNUSED);
setPinType(7,BUTTON);
setPinType(8,UNUSED);
setPinType(9,UNUSED);
setPinType(10,LED);
setPinType(11,LED);
setPinType(12,LED);
setPinType(13,BUTTON);
setPinType(14,UNUSED);
setPinType(15,UNUSED);
#endif

}

void main(void)
{
    InitApp();
    initializePins();
    setPinModes();

    unsigned char pin=0;

    while(1)
    {
        processPin(pin);
        pin = (pin+1)%NPINS;
        CLRWDT();
    }

}

void interrupt isr(void)
{
    if(SSPIF==1){
        SDO_CONFIG = 1;
        SSPIF=0;
        char data = SSPBUF;
        data = processCommand(data);
        SSPBUF = data;
    }

}



