#include "HD44780.h"

static void HD44780_WriteNibble(const uint8_t nib)
{
  LCD_EN_PORT &= ~(1<<LCD_EN_PIN);
  if(nib&0x08) LCD_D7_PORT |= (1<<LCD_D7_PIN);
  else LCD_D7_PORT &= ~(1<<LCD_D7_PIN);
  if(nib&0x04) LCD_D6_PORT |= (1<<LCD_D6_PIN);
  else LCD_D6_PORT &= ~(1<<LCD_D6_PIN);
  if(nib&0x02) LCD_D5_PORT |= (1<<LCD_D5_PIN);
  else LCD_D5_PORT &= ~(1<<LCD_D5_PIN);
  if(nib&0x01) LCD_D4_PORT |= (1<<LCD_D4_PIN);
  else LCD_D4_PORT &= ~(1<<LCD_D4_PIN);
  _delay_us(1);
  LCD_EN_PORT |= (1<<LCD_EN_PIN);
  _delay_us(1);
  LCD_EN_PORT &= ~(1<<LCD_EN_PIN);
  _delay_us(100);
}

static void HD44780_WriteByte(const uint8_t c)
{
  HD44780_WriteNibble(c>>4);
  HD44780_WriteNibble(c&0x0F);
}

static void HD44780_PowerUp4Bit(void)
{
  /* Wait for more than 40 ms after VCC rises to 2.7 V */
  _delay_ms(40);
  HD44780_WriteNibble(0x03);        // FN_SET 8-bit

  /* Wait for more than 4.1 ms */
  _delay_ms(5);
  HD44780_WriteNibble(0x03);        // FN_SET 8-bit

  /* Wait for more than 100 µs */
  _delay_us(100);
  HD44780_WriteNibble(0x03);        // FN_SET 8-bit

  /* From now on we must allow 40us for each command */
  _delay_us(50);
  HD44780_WriteNibble(0x02);        // FN_SET 4-bit

  /* The LCD is now in 4-bit mode so we can continue
     using the 4-bit API */
  _delay_us(50);
}

void HD44780_Initialize(void)
{
  LCD_D4_DDR |= (1<<LCD_D4_PIN);
  LCD_D5_DDR |= (1<<LCD_D5_PIN);
  LCD_D6_DDR |= (1<<LCD_D6_PIN);
  LCD_D7_DDR |= (1<<LCD_D7_PIN);
  LCD_RS_DDR |= (1<<LCD_RS_PIN);
  LCD_RW_DDR |= (1<<LCD_RW_PIN);
  LCD_EN_DDR |= (1<<LCD_EN_PIN);
  LCD_D4_PORT &= ~(1<<LCD_D4_PIN);
  LCD_D5_PORT &= ~(1<<LCD_D5_PIN);
  LCD_D6_PORT &= ~(1<<LCD_D6_PIN);
  LCD_D7_PORT &= ~(1<<LCD_D7_PIN);
  LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
  LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
  LCD_EN_PORT &= ~(1<<LCD_EN_PIN);
  HD44780_PowerUp4Bit();
  _delay_ms(50);
}

void HD44780_WriteCommand(const uint8_t c)
{
  LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
  HD44780_WriteByte(c);
  _delay_us(50);
}

void HD44780_WriteData(const uint8_t c,int delay)
{
  LCD_RS_PORT |= (1<<LCD_RS_PIN);
  HD44780_WriteByte(c);
  LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
  if (delay) _delay_ms(200);
  _delay_us(50);
}

int HD44780_XY2Adrr(int nbrows,int nbcols,int row,int col)
{
  int row_offsets[]={0x00,0x40};
  if(row>=nbrows) row=nbrows-1;
  if(col>=nbcols) col=nbcols-1;
  return row_offsets[row]+col;
}

void HD44780_EmptyLine1(char line1[], int size)
{
    for (int i = 0; i < size; i++) {
        line1[i] = '\0';
    }
}

void HD44780_CopyLine1in0(char line1[], int nbrows, int nbcols, int ind_line1) {
    for (int i = 0; i < ind_line1; i++) {
        int address_ligne0 = HD44780_XY2Adrr(nbrows, nbcols, 0, i);
        HD44780_WriteCommand(LCD_ADDRSET | address_ligne0);
        HD44780_WriteData(line1[i],0);
    }
    HD44780_EmptyLine1(line1,nbcols);
}


void HD44780_EraseLine(int nbrows, int nbcols, int line) {
    int address_line1;
    char espace = ' ';
    for (int i = 0; i < nbcols; i++) {
    	address_line1 = HD44780_XY2Adrr(nbrows, nbcols, line, i);
    	HD44780_WriteCommand(LCD_ADDRSET | address_line1);
	    HD44780_WriteData(espace,0);
    }
}


void HD44780_WriteChar(char car, char line1[], int* ind_line1, int nbrows, int nbcols, int* row, int* col) {
    if ((*col) == nbcols) {
        (*col) = 0;
        if ((*row) <= 1) (*row)++;
        if ((*row) > 1) {
            (*row) = 1;
            HD44780_EraseLine(nbrows, nbcols,0);
            HD44780_EraseLine(nbrows, nbcols,1);
            HD44780_CopyLine1in0(line1, nbrows, nbcols,*ind_line1);
        }
        (*ind_line1) = 0;
    }

    int address = HD44780_XY2Adrr(nbrows, nbcols, *row, *col);
    HD44780_WriteCommand(LCD_ADDRSET | address);
    HD44780_WriteData(car,1);
    (*col)++;
    if ((*row) == 1) 
    {
        line1[*ind_line1] = car;
        (*ind_line1)++;
    }
}



void VT100_Traitement(char car, int nbrows, int nbcols, int* row, int* col, int* vt100_mode)
{
    if (*vt100_mode == 1) // CURSOR_MODE
    {
        int address;

        switch (car)
        {
            case CURSOR_UP:
                *row = (*row == 1) ? 0 : *row;
                break;

            case CURSOR_DOWN:
                *row = (*row == 0) ? 1 : *row;
                break;

            case CURSOR_RIGHT:
                *col = (*col < nbcols - 1) ? (*col + 1) : *col;
                break;

            case CURSOR_LEFT:
                *col = (*col > 0) ? (*col - 1) : *col;
                break;
        }

        address = HD44780_XY2Adrr(nbrows, nbcols, *row, *col);
        HD44780_WriteCommand(LCD_ADDRSET | address);
        HD44780_WriteCommand(LCD_ON | CURSOR_BLINK);
    }
}


void HD44780_Traitement(char car, char line1[], int* ind_line1, int nbrows, int nbcols, int* row, int* col, int* vt100, int* vt100_mode,)
{
    switch (car)
    {
        case '\n': //Retour à la ligne
            switch (*row)
            {
                case 0:
                    (*col) = 0;
                    (*row) = 1;
                    break;
                case 1:
                    *col = 0;
                    HD44780_EraseLine(nbrows, nbcols,0);
                    HD44780_EraseLine(nbrows, nbcols,1);
                    HD44780_CopyLine1in0(line1, nbrows, nbcols,*ind_line1); 
                    *ind_line1 = 0;
                    break;    
            }
            break;

        case '\r': // Retour chariot
            *col = 0;
            (*ind_line1) = 0;
            HD44780_EmptyLine1(line1,nbcols);
            break;

        case '\b': // Retour arrière
            switch (*row)
            {
                case 0:
                    if (*col > 0)
                    {
                        (*col)--;//Retourne sur le caractère précédent
                        char espace = ' ';
                        int address = HD44780_XY2Adrr(nbrows, nbcols, *row, *col);
                        HD44780_WriteCommand(LCD_ADDRSET | address);
                        HD44780_WriteData(espace, 1);//"L'efface"
                        _delay_ms(500);

                    }
                    break;
                case 1:
                    if (*col > 0)
                    {
                      (*col)--;
                      (*ind_line1) --;
                    }
                    else 
                    {
                      (*row) = 0;
                      (*col) = 15;
                    }
                    char espace = ' ';
                    int address = HD44780_XY2Adrr(nbrows, nbcols, *row, *col);
                    HD44780_WriteCommand(LCD_ADDRSET | address);
                    HD44780_WriteData(espace, 1);
                    break;
            }
            break;

        case '\t': // Tabulation de 4 caractères
            for (int i=0; i < 4; i++)
            {   
                char espace = ' ';
                HD44780_WriteChar(espace,line1,ind_line1,nbrows,nbcols,row,col);
            }
            break;

	case ESCAPE: //Instruction pour code VT100
		(*vt100) = 1;
		break;

	case CURSOR_MODE:
		if ((*vt100) == 1) (*vt100_mode) = 1;
		else (*vt100) = 0;
		break;
        default: 
	    	if ((*vt100_mode) != 0)
		{
			VT100_Traitement(car,nbrows,nbcols,row,col,vt100_mode);
			(*vt100) = 0;
			(*vt100_mode) = 0;
		}
		else
		{
            		HD44780_WriteChar(car,line1,ind_line1,nbrows,nbcols,row,col);
		}
           	break;
    }
}