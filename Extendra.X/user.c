/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    // Initialize the ports
    TRISB=0xFF;
    TRISA=0xFF;
    TRISC=0xFF;
    WPUB=0xFF;
    ANSELA=0;
    LATA=0;
    ANSELB=0;
    LATB=0;
    ANSELC=0;
    LATC=0;
    
    // Initialize the SPI pins
    SS_CONFIG = 1;NOP();
    SCK_CONFIG = 1;NOP();
    SDO_CONFIG = 1;NOP();
    SDI_CONFIG = 1;NOP();

    // Configure the SPI to work with the Arduino
    SSPSTAT = 0;NOP();
    SSPSTATbits.CKE = 1;NOP(); // from idle to active
    SSPSTATbits.SMP = 0;NOP();
    SSPCON1bits.SSPEN = 1; // enable SPI pins
    NOP();
    SSPCON1bits.CKP = 0;
    NOP();
    SSPCON1bits.SSPM = 0b0100;
    NOP();
    SSSEL = 0; // select RA5 as SS

    SSPCON3bits.BOEN = 1; // Enable daisy-chain

    SSPIE = 1; // enable interrupt of SPI comunication
    PEIE = 1; // enable peripheral interrups
    GIE = 1; // enable global interrupst

    // ADC Configuration

    ADCON1bits.ADPREF = 00; // Internal reference
    NOP();
    ADCON1bits.ADFM = 0; // left justification
    NOP();
    ADCON1bits.ADCS = 0x101; // Divisor for 16MHz -> 1us conversion
}

const char channel_selector[] =
{   0*4+1, //0,
    1*4+1, //1,
    2*4+1, //2,
    3*4+1, //3,
    14*4+1, //14,
    18*4+1, //18,
    19*4+1, //19,
    12*4+1, //12,
    10*4+1, //10,
    8*4+1, //8,
    9*4+1, //9,
    11*4+1 //11
};
unsigned analogRead(int pin){
    unsigned int value;
    if (pin>11) return 0;
    char channel = channel_selector[pin];
    ADCON0 = channel;
    pinMode(pin,INPUT);
    setAnalog(pin,1);

    ADCON0bits.GO = 1; NOP();
    while(ADCON0bits.GO==1);
    value=ADRES;
    
    ADCON0bits.ADON=0;
    return value;
}

void pinMode(int pin,int mode)
{
    switch(pin){
        case 0: POT1_CONFIG = mode; break;
        case 1: POT2_CONFIG = mode; break;
        case 2: POT3_CONFIG = mode; break;
        case 3: POT4_CONFIG = mode; break;
        case 4: POT5_CONFIG = mode; break;
        case 5: POT6_CONFIG = mode; break;
        case 6: POT7_CONFIG = mode; break;
        case 7: POT8_CONFIG = mode; break;
        case 8: POT9_CONFIG = mode; break;
        case 9: POT10_CONFIG = mode; break;
        case 10: POT11_CONFIG = mode; break;
        case 11: POT12_CONFIG = mode; break;
        case 12: DIG1_CONFIG = mode; break;
        case 13: DIG2_CONFIG = mode; break;
        case 14: DIG3_CONFIG = mode; break;
        case 15: DIG4_CONFIG = mode; break;
        default: break;
    }
}

void setAnalog(int pin,int mode)
{
    switch(pin){
        case 0: POT1_ANALOG = mode; break;
        case 1: POT2_ANALOG = mode; break;
        case 2: POT3_ANALOG = mode; break;
        case 3: POT4_ANALOG = mode; break;
        case 4: POT5_ANALOG = mode; break;
        case 5: POT6_ANALOG = mode; break;
        case 6: POT7_ANALOG = mode; break;
        case 7: POT8_ANALOG = mode; break;
        case 8: POT9_ANALOG = mode; break;
        case 9: POT10_ANALOG = mode; break;
        case 10: POT11_ANALOG = mode; break;
        case 11: POT12_ANALOG = mode; break;
        default: break;
    }
}

void digitalWrite(int pin,int value){
    switch(pin){
        case 0: POT1_PIN = value; break;
        case 1: POT2_PIN = value; break;
        case 2: POT3_PIN = value; break;
        case 3: POT4_PIN = value; break;
        case 4: POT5_PIN = value; break;
        case 5: POT6_PIN = value; break;
        case 6: POT7_PIN = value; break;
        case 7: POT8_PIN = value; break;
        case 8: POT9_PIN = value; break;
        case 9: POT10_PIN = value; break;
        case 10: POT11_PIN = value; break;
        case 11: POT12_PIN = value; break;
        case 12: DIG1_PIN = value; break;
        case 13: DIG2_PIN = value; break;
        case 14: DIG3_PIN = value; break;
        case 15: DIG4_PIN = value; break;
        default: break;
    }
}

int digitalRead(int pin){
    int value = 0;
    switch(pin){
        case 0: value = POT1_PIN; break;
        case 1: value = POT2_PIN; break;
        case 2: value = POT3_PIN; break;
        case 3: value = POT4_PIN; break;
        case 4: value = POT5_PIN; break;
        case 5: value = POT6_PIN; break;
        case 6: value = POT7_PIN; break;
        case 7: value = POT8_PIN; break;
        case 8: value = POT9_PIN; break;
        case 9: value = POT10_PIN; break;
        case 10: value = POT11_PIN; break;
        case 11: value = POT12_PIN; break;
        case 12: value = DIG1_PIN; break;
        case 13: value = DIG2_PIN; break;
        case 14: value = DIG3_PIN; break;
        case 15: value = DIG4_PIN; break;
        default: break;
    }
    return value;
}


unsigned int pinTypes[NPINS];
unsigned int pinStates[NPINS];
unsigned int pinStates1[NPINS];



void initializePins(){
    for(int i=0;i<NPINS;i++){
        pinTypes[i]=UNUSED;
        pinStates[i]=0;
    }
}

void setPinType(unsigned char pin,unsigned char type_){
    if(pin>=NPINS) return;
    switch(type_){
        case KNOB:
            pinMode(pin,INPUT);
            pinTypes[pin] = KNOB;
            break;
        case BUTTON:
            pinMode(pin,INPUT);
            pinTypes[pin] = BUTTON;
            break;
        case LED:
            pinMode(pin,OUTPUT);
            pinTypes[pin] = LED;
            break;
        case BLINK:
            pinMode(pin,OUTPUT);
            pinTypes[pin] = BLINK;
            break;
        default:
            break;
        }
}

unsigned int getPinValue(unsigned char pin){
    if(pin>=NPINS) return 0;
    switch(pinTypes[pin]){
        case KNOB:
            return pinStates[pin];
        case BUTTON:
            return pinStates[pin]>DEBOUNCE_MAX/2?127:0;
        case LED:
            return pinStates[pin]>0?127:0;
        case BLINK:
            return pinStates[pin]>0?127:0;
        default:
            return 0;
        }
}

void setPinValue(unsigned char pin,unsigned int value){
    if(pin>NPINS) return;
    switch(pinTypes[pin]){
        case KNOB:
            break;
        case BUTTON:
            break;
        case LED:
            pinStates[pin]=value;
            break;
        case BLINK:
            pinStates[pin] = value>0?BLINK_LENGTH:0;
            break;
        default:
            break;
        }
}
int get_diff_scaled(unsigned int value, unsigned int reference){
    unsigned int diff;
    if(value==reference) return 0;
    if(value>reference) {
        diff = value-reference;
        diff = diff>>6;
        return diff;
    }else{
        diff = reference-value;
        diff = diff>>6;
        return (-diff);
    }
}


void processPin(unsigned char pin){
    unsigned int value;
    int delta;

    switch(pinTypes[pin]){
        case KNOB:
            value = analogRead(pin);
            delta = get_diff_scaled(value,pinStates[pin]);
            pinStates1[pin] += delta;
            pinStates[pin] = pinStates1[pin];
            break;
        case BUTTON:
            value = digitalRead(pin);
            delta = get_diff_scaled((value==1?DEBOUNCE_MAX:0),pinStates[pin]);
            pinStates1[pin]+=delta;
            pinStates[pin] = pinStates1[pin];
            break;
        case LED:
            if(pinStates[pin]!=0)
                pinStates1[pin]=pinStates1[pin]==0?1:0;
            else
                pinStates1[pin]=0;
            digitalWrite(pin,pinStates1[pin]);
            break;
        case BLINK:
            if(pinStates[pin]>0){
                digitalWrite(pin,1);
                pinStates[pin]=pinStates[pin]-1;
            } else {
                digitalWrite(pin,0);
            }
            break;
        default:
            break;
        }
}


