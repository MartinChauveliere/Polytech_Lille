FILENAME = main
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = stk500v1
PORT = /dev/ttyACM0
BAUD = 19200

COMPILE = avr-gcc -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=c99
LIB_DIR = lib

default: compile upload clean

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o -I$(LIB_DIR)
	$(COMPILE) -c $(LIB_DIR)/HD44780.c -o HD44780.o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o HD44780.o
	avr-objcopy -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(MCU) $(FILENAME).elf

upload:
	avrdude -F -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm HD44780.o
	rm $(FILENAME).elf
	rm $(FILENAME).hex
