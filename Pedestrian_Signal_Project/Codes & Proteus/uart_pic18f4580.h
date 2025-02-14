/* 
 * File:   uart_pic18f4580.h
 * Version: 1.1
 * Author: Turky Abdulaziz Saderaldin
 * King Abdulaziz University, Jeddah 
 * 
 * Created on November 22, 2023, 5:14 PM
 */

#ifndef UART_PIC18F4580_H
#define UART_PIC18F4580_H

#define _XTAL_FREQ (8000000) // Define Internal Oscillator Frequency to 8-MHz
#include <xc.h>
#include <stdio.h>

/* hook for printf */
void putch(char Data)
{
    if (1 == RCSTAbits.OERR) {
        RCSTAbits.CREN = 0; // Disable continuous receive
        RCSTAbits.CREN = 1; // Enable continuous receive
    }
    while (0 == PIR1bits.TXIF) {}
    TXREG = Data; // Write data to transmit register
    PIR1bits.TXIF = 0; // Clear Transmit interrupt flag
}

void UART_Init(unsigned int baudrate) {
    BAUDCON = 0x00; // Disable 16-bit Baud Rate Generator (BRG16=0)
    RCSTA = 0x90;   // Enable Serial Port and Continuous Receive (SPEN=1, CREN=1)
    TXSTA = 0x24;   // Enable Transmit (TXEN=1), Async mode, High speed (BRGH=1)
    unsigned long UART_BRG_VALUE = ((_XTAL_FREQ / (baudrate * 16UL)) - 1UL);
    SPBRG = (unsigned char)(UART_BRG_VALUE);      // Set low byte of Baud Rate Generator
    SPBRGH = (unsigned char)(UART_BRG_VALUE >> 8); // Set high byte of Baud Rate Generator
}

// Wrapper function for printf
void UART_Write_Text(const char *format) {
    printf(format);
    __delay_ms(10);
}

void UART_Write(char Data) {
    putch(Data);
}

int UART_Data_Ready() {
    return PIR1bits.RCIF; // Check the receive interrupt flag
}

char UART_Read() {
    if (1 == RCSTAbits.OERR) {
        RCSTAbits.CREN = 0; // Disable continuous receive
        RCSTAbits.CREN = 1; // Enable continuous receive
    }
    return RCREG;  // Read stored data in receive register
}

#endif // UART_PIC18F4580_H
