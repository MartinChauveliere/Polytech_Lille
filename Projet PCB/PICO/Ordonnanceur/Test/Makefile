FILENAME = test7
MCU= atmega328p
F_CPU= 16000000UL
PROGRAMMER = arduino
PORT= COM6
BAUD= 115200

COMPILE = avr-gcc -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=c99


default: compile upload clean


compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -O ihex $(FILENAME).elf $(FILENAME).hex 
	avr-size --format=avr --mcu=$(MCU) $(FILENAME).elf 

upload:
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex