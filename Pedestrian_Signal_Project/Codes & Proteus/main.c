#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "uart_pic18f4580.h"
#include "lcd.h"

#define _XTAL_FREQ (8000000) // Define Internal Oscillator Frequency to 8-MHz.
#define BAUD_RATE (9600)     // Define UART baud rate to be 9600.

volatile char command; // Define volatile variable to store incoming command

// Function prototypes
void debugPrint(const char *message);
void displayDefaultMessage(void);
void updateCountdown(const char *label, int seconds);

void debugPrint(const char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        while (!TXIF); // Wait for TX buffer to be empty
        TXREG = message[i]; // Send character
    }
}

void displayDefaultMessage(void) {
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Not Allowed");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("For Walking");
}

void updateCountdown(const char *label, int seconds) {
    char buffer[16];
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String(label);
    sprintf(buffer, "  %2d sec", seconds);
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String(buffer);
}




void main(void) {
    TRISC = 0x80;  // Set PORTC pins as outputs (LEDs and RX) (TX is input)
    TRISB = 0X00;
    OSCCON = 0x70; // Adjust Internal Oscillator to 8-MHz
    CMCON = 0x07;  // Disable Comparator
    ADCON1 = 0x0F; // All Digital I/O
    LATB = 0x14;   // Initialize LATC with default value
    PIR1bits.RCIF = 0; // Clear receive interrupt flag
    UART_Init(BAUD_RATE); // Initialize UART at 9600 bps
    Lcd_Init();  // Initialize LCD
    // Display default message
    displayDefaultMessage();
    // Enable UART receive interrupt
    RCIE = 1;  // Enable UART receive interrupt
    PEIE = 1;  // Enable peripheral interrupt
    GIE = 1;   // Enable global interrupt
    while (1) {
    }
}

void __interrupt() ISR(void) {
    if (PIR1bits.RCIF) {  // Check if UART receive interrupt flag is set
        command = UART_Read();  // Read the received command
        PIR1bits.RCIF = 0;
        if (command == 'G') {
            debugPrint("G");
            LATB = 0x12;  // Update LATC for green signal
            for (int i = 5; i >= 0; i--) {
                updateCountdown("Allowed after : ", i);
                __delay_ms(1000); // Delay for 1 second
            }
            LATB = 0x09;
            for (int i = 20; i >= 0; i--) {
                updateCountdown("Allowed For : ", i);
                __delay_ms(1000); // Delay for 1 second
            }
            LATB = 0x14;       // Reset LATC to default
            // Display default message
            displayDefaultMessage();
        } else {
            debugPrint("N");
        }
    }
}
