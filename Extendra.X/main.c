/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

void delay(int k){
    for(int i=0;i<k;i++)
        for(int j=0;j<100;j++);
}


unsigned char command;
unsigned char channel;
unsigned char byte1In;
unsigned char byte2In;
unsigned char byte1Out;
unsigned char byte2Out;
unsigned char count;

unsigned char processCommand(unsigned char in){
    unsigned int value;

    if(count==0){ // first byte, the command
        command = in&0xE0;
        channel = in&0x1F;

        switch(command){
            case 0x20: // Pin configuration
                byte1Out = 0;
                byte2Out = 0;
                break;
            case 0x40: // Digital output (LED)
                byte1Out = 0;
                byte2Out = 0;
                break;
            case 0x60: // Digital input (Button)
                SDO_CONFIG=0;
                value = getPinValue(channel);
                byte1Out = 0x00FF & value;
                byte2Out = (0xFF00 & value)>>8;
                
                break;
            case 0x80: // Analog input (Knob)
                SDO_CONFIG=0;
                value = getPinValue(channel)>>9;
                byte1Out = 0x00FF & value;
                byte2Out = (0xFF00 & value)>>8;
                
                break;
            case 0xA0: // Analog output (not implemented)
                byte1Out = 0;
                byte2Out = 0;
                break;
            default:
                count=0; // unknown command, ignore
                return in;
            } // switch
            count = 1;
            return byte1Out;

    }
    if(count==1){
        byte1In = in;
        count=2;
        return byte2Out;
    }
    if(count==2){
        byte2In = in;
        count = 0;
        if(command==0x20){
            channel =0;
            
            setPinType(byte1In,byte2In);
            
        }
        if(command==0x40)
        {
  
             unsigned int v = (byte2In<<8) | byte1In;
             setPinValue(channel,v);
             
        }
        
         return in;
    }
    count = 0;
    return in;
}

void main(void)
{
    ConfigureOscillator();
    InitApp();

    initializePins();
    unsigned char pin=0;
    //setPinType(1,LED);
    //setPinType(0,KNOB);

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

