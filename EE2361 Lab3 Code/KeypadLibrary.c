#include "xc.h"

void initKeyPad(void){ //Connect RA<3:0> to the columns of your keypad
                        // (pins<4:1>) and RB<15:12> to the rows of your keypad (pins<5:8>).
    AD1PCFG |= 0xFFFF;   // All ports digital
    TRISA |= 0x000F;     // Sets RA0-RA3 to inputs
        
                        // pins 2,CN2 3,CN3 9,CN30 10,CN29
    CNPU1bits.CN2PUE = 1; // turn on pull up for pin 2
    CNPU1bits.CN3PUE = 1; // pull up for pin 3
    CNPU2bits.CN30PUE = 1; // pull up for pin 9
    CNPU2bits.CN29PUE = 1; // pull up for pin 10
}

// Scans if a button has been pressed and the direct position on the keypad
unsigned int readKeyPadRAW(void) {
    LATB |= 0xF000; // Set all rows HIGH
    unsigned int position = 0x0000;

    // Scan Row 0
    LATB &= ~(1 << 12); // Row 0 LOW
    delay(1);
    if (!(PORTA & 0x0001)) position |= (1 << 0); // Col 0 pressed
    if (!(PORTA & 0x0002)) position |= (1 << 1); // Col 1 pressed
    if (!(PORTA & 0x0004)) position |= (1 << 2); // Col 2 pressed
    if (!(PORTA & 0x0008)) position |= (1 << 3); // Col 3 pressed
    LATB |= 0xF000; // Reset rows

    // Scan Row 1
    LATB &= ~(1 << 13); // Row 1 LOW
    delay(1);
    if (!(PORTA & 0x0001)) position |= (1 << 4);
    if (!(PORTA & 0x0002)) position |= (1 << 5);
    if (!(PORTA & 0x0004)) position |= (1 << 6);
    if (!(PORTA & 0x0008)) position |= (1 << 7);
    LATB |= 0xF000; // Reset

    // Scan Row 2
    LATB &= ~(1 << 14); // Row 2 LOW
    delay(1);
    if (!(PORTA & 0x0001)) position |= (1 << 8);
    if (!(PORTA & 0x0002)) position |= (1 << 9);
    if (!(PORTA & 0x0004)) position |= (1 << 10);
    if (!(PORTA & 0x0008)) position |= (1 << 11);
    LATB |= 0xF000; // Reset

    // Scan Row 3
    LATB &= ~(1 << 15); // Row 3 LOW
    delay(1);
    if (!(PORTA & 0x0001)) position |= (1 << 12);
    if (!(PORTA & 0x0002)) position |= (1 << 13);
    if (!(PORTA & 0x0004)) position |= (1 << 14);
    if (!(PORTA & 0x0008)) position |= (1 << 15);
    LATB |= 0xF000;

    return position;
}

// Receives an int value that corresponds to a position on the map to get the specific character
unsigned int getButton(unsigned int key){
    unsigned int keypadLookup[16] = 
            {
             'a','3','2','1',
             'b','6','5','4',
             'c','9','8','7',
             'd','#','0','*'
            };  // needed to flip to account for inverse column value (when 1 was pressed A was shown)
    for (int i = 0; i < 16; i++) {
        if (key & (1 << i)) {     // checks if position was overflowed
            return keypadLookup[i];
        }
    }
    return '~';  // no key found
}