/* 
 * File:   DisplayLibrary.h
 * Author: jonathanip
 *
 * Created on October 16, 2025, 2:22 PM
 */

#ifndef SEVSEGDISP_H
#define	SEVSEGDISP_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif

void init7seg(void);
void showChar7seg(char myChar, int myDigit);
void delay(int delay_in_ms);


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAYLIBRARY_H */

