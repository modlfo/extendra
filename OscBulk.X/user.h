/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define DIG1 12
#define DIG2 13
#define DIG3 14
#define DIG4 15

#define POT1 0
#define POT2 1
#define POT3 2
#define POT4 3
#define POT5 4
#define POT6 5
#define POT7 6
#define POT8 7
#define POT9 8
#define POT10 9
#define POT11 10
#define POT12 11

#define DIG1_PIN RA4
#define DIG2_PIN RA7
#define DIG3_PIN RA6
#define DIG4_PIN RC0

#define POT1_PIN RA0
#define POT2_PIN RA1
#define POT3_PIN RA2
#define POT4_PIN RA3
#define POT5_PIN RC2
#define POT6_PIN RC6
#define POT7_PIN RC7
#define POT8_PIN RB0
#define POT9_PIN RB1
#define POT10_PIN RB2
#define POT11_PIN RB3
#define POT12_PIN RB4

#define DIG1_CONFIG TRISA4
#define DIG2_CONFIG TRISA7
#define DIG3_CONFIG TRISA6
#define DIG4_CONFIG TRISC0

#define POT1_CONFIG TRISA0
#define POT2_CONFIG TRISA1
#define POT3_CONFIG TRISA2
#define POT4_CONFIG TRISA3
#define POT5_CONFIG TRISC2
#define POT6_CONFIG TRISC6
#define POT7_CONFIG TRISC7
#define POT8_CONFIG TRISB0
#define POT9_CONFIG TRISB1
#define POT10_CONFIG TRISB2
#define POT11_CONFIG TRISB3
#define POT12_CONFIG TRISB4

#define POT1_ANALOG ANSELAbits.ANSA0
#define POT2_ANALOG ANSELAbits.ANSA1
#define POT3_ANALOG ANSELAbits.ANSA2
#define POT4_ANALOG ANSELAbits.ANSA3
#define POT5_ANALOG ANSELCbits.ANSC2
#define POT6_ANALOG ANSELCbits.ANSC6
#define POT7_ANALOG ANSELCbits.ANSC7
#define POT8_ANALOG ANSELBbits.ANSB0
#define POT9_ANALOG ANSELBbits.ANSB1
#define POT10_ANALOG ANSELBbits.ANSB2
#define POT11_ANALOG ANSELBbits.ANSB3
#define POT12_ANALOG ANSELBbits.ANSB4

#define SS_CONFIG TRISA5
#define SCK_CONFIG TRISC3
#define SDO_CONFIG TRISC5
#define SDI_CONFIG TRISC4

#define SS_PIN RA5

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

#define NPINS 16
/* These are the diferent types
 * of elements that we use      */
#define UNUSED  0
#define KNOB    1  // Analog input
#define BUTTON  2  // Digital input
#define LED     3  // Digital output
#define BLINK   4  // Digital output

#define BLINK_LENGTH 500 // number of ticks the led stays on
#define DEBOUNCE_MAX 1000


// this array contains the handlers for the 16 pins in the board
extern unsigned int pinTypes[NPINS];
extern unsigned int pinStates[NPINS];
extern unsigned int pinStates1[NPINS];


void InitApp(void);         /* I/O and Peripheral Initialization */

/* Arduino like functions  */
void pinMode(int pin,int mode);
void digitalWrite(int pin,int value);
int digitalRead(int pin);
unsigned int analogRead(int pin);
void setAnalog(int pin,int mode);

void initializePins();
void processPin(unsigned char pin);
void setPinType(unsigned char pin,unsigned char type_);
unsigned int getPinValue(unsigned char pin);
void setPinValue(unsigned char pin,unsigned int value);