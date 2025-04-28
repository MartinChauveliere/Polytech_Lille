TARGET=Ordonnanceur

default: compile upload clean

compile:
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os $(TARGET).c -o $(TARGET).o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os SPI.c -o $ SPI.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os Serie.c -o $ Serie.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os Matrice.c -o $ Matrice.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os 7Seg.c -o $ 7Seg.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -c -Wall -I. -Os Taches.c -o $ Taches.o
	avr-gcc -mmcu=atmega328p -g -lm -Wl,--gc-sections -o $(TARGET).elf $(TARGET).o SPI.o Serie.o Matrice.o 7Seg.o Taches.o

upload:
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	stty -F /dev/ttyUSB0 hupcl
	avrdude -F -v -p atmega328p -c stk500v1 -b 115200 -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex


clean:
	rm -f *.a
	rm -f *.o
	rm -f *.elf
	rm -f *.hex
	
