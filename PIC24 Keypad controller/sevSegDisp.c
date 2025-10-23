#include "xc.h"
#include "Lab3 _Header.h"
enum direction {RIGHT,LEFT};

// Maps specific LED designs to certain characters and determines the direction its output to.
void showChar7seg(char myChar, int myDigit){
    unsigned long int num = 0xF3FF;
    LATB = 0xF000;
    if (myDigit == LEFT){
        num |= 0x800;
    }
    if (myDigit == RIGHT){
        num |= 0x400;
    }
    switch (myChar){  // my format structure for each case was cited from ChatGPT as it wouldn't work unless I have the bitwise NOT op
        case '0':
            num &= (unsigned long)(~(0b1111110000)); // ABCEDF 0
            break;
        case '1':
            num &= (unsigned long)(~(0b0110000000)); // BC 0 
            break;
        case '2':
            num &= (unsigned long)(~(0b1101101000)); // ABDEG 2
            break;
        case '3':
            num &= (unsigned long)(~(0b1111001000)); // ABCDG 3
            break;
        case '4':
            num &= (unsigned long)(~(0b0110011000)); // BCFG 4
            break;
        case '5':
            num &= (unsigned long)(~(0b1011011000)); // ACDFG 5
            break;
        case '6':
            num &= (unsigned long)(~(0b1011111000)); // ACDEFG 6
            break;
        case '7':
            num &= (unsigned long)(~(0b1110000000)); // ABC 7 
            break;
        case '8':
            num &= (unsigned long)(~(0b1111111000)); // ABCDEFG 8
            break;
        case '9':
            num &= (unsigned long)(~(0b1110011000)); // ABCEF 9
            break;
        case 'a': 
            num &= (unsigned long)(~0b1110111000); // ABCEFG a
            break;
        case 'b': 
            num &= (unsigned long)(~0b0011111000); // CDEFG b
            break;
        case 'c': 
            num &= (unsigned long)(~0b1001110000); // ADEF C
            break;
        case 'd': 
            num &= (unsigned long)(~0b0111101000); // BCDEG d
            break;
        case '*':
            num &= (unsigned long)(~0b0100101000); // BEG (squiggle)
            break;
        case '#':
            num &= (unsigned long)(~0b0110111000); // BCEFG (H))
            break;
        case '~':
            break;
        break;
    }
    LATB = num;
}

// Initializes the seven segment and registers 
void init7seg(void){ 
    AD1PCFG = 0xFFFF; // sets all pins to digital mode.
    TRISB = 0x0000;     // sets all B outputs
}

// Delay function in milliseconds 
void delay(int delay_in_ms) {
    int i;
    for (i = delay_in_ms; i > 0; i--){
        delay_1ms();
    }
}

// Scans for keypad input, places inputs shifting right to left on LED
void scan(void){ 
    unsigned int leftLED = 0;
    unsigned int rightLED = 0;
    unsigned int prevKey = '~'; // initial state
    while(1){
        unsigned int incomingKey = getButton(readKeyPadRAW()); // next input
        if (incomingKey != '~' && prevKey == '~'){
            leftLED = rightLED;
            rightLED = incomingKey; 
        }
        showChar7seg(rightLED, RIGHT);
        delay(5); 
        showChar7seg(leftLED, LEFT);
        delay(5); // added for a stronger LED light, also without this the left LED won't produce an output
        prevKey = incomingKey;
    }
}