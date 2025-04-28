#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "HD44780_private.h"
#include <stdio.h> 

// Commands
#define LCD_CLEAR	0x01
#define LCD_HOME	0x02
#define LCD_ON		0x0c
#define LCD_OFF		0x08
#define LCD_INCR_LEFT	0x04
#define LCD_INCR_RIGHT	0x06
#define LCD_ADDRSET	0x80

// Scroll mode
#define SCROLL		0x01

// Cursor mode
#define CURSOR_NONE	0x00
#define CURSOR_BLINK	0x01
#define CURSOR_ULINE	0x02
#define CURSOR_FULL	0x03

//VT100
#define ESCAPE 0x1b
#define CURSOR_MODE 0x1c
#define CURSOR_UP 0x41
#define CURSOR_DOWN 0x42
#define CURSOR_RIGHT 0x43
#define CURSOR_LEFT 0x44

// Prototypes
void HD44780_Initialize(void);
void HD44780_WriteCommand(const uint8_t c);
void HD44780_WriteData(const uint8_t c,int delay);
int HD44780_XY2Adrr(int nbrows,int nbcols,int row,int col);
void HD44780_CopyLine1in0(char ligne2[], int nbrows, int nbcols, int ind_ligne2);
void HD44780_EraseLine(int nbrows, int nbcols, int ligne);
void HD44780_WriteChar(char car, char ligne2[], int* ind, int nbrows, int nbcols, int* row, int* col);
void VT100_Traitement(char car, int nbrows, int nbcols, int* row, int* col, int* vt100_mode);
void HD44780_Traitement(char car, char ligne2[], int* ind, int nbrows, int nbcols, int* row, int* col, int* vt100, int* vt100_mode);