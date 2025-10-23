/* 
 * File:   KeypadLibrary.h
 * Author: jonathanip
 *
 * Created on October 16, 2025, 2:22 PM
 */

#ifndef KEYPADLIBRARY_H
#define	KEYPADLIBRARY_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif

unsigned int readKeyPadRAW(void);
unsigned int getButton(unsigned int);
void initKeyPad(void);


#ifdef	__cplusplus
}
#endif

#endif	/* KEYPADLIBRARY_H */

