#include "ordonnanceur.h"

task_t task[NB_TASK];
uint8_t currentTask=0;
uint8_t keyAscii = 'a';
int counter;

void scheduler (){
    for(int i=0; i<NB_TASK; i++){
        if(task[i].state == SLEEP && task[i].sleep.reason == DELAY_SLEEPING){
            
            // Récupérer la différence de temps
            uint16_t difftime_ms = 20;
            if(TCNT1 != 0){
                difftime_ms = TCNT1*200/OCR1A/10; // On multiplie par 10 pour ne pas avoir de problème avec les nombres flottants
                TCNT1 = 0;
            }
            task[i].sleep.data -= difftime_ms;
            
            if(task[i].sleep.data <= 0){
                task[i].state = AWAKE;
            }
        }
    }
    
    do{
        currentTask ++;
        if(currentTask >= NB_TASK) currentTask = 0; // Attention si tous les processus sont à l'arrêt
    }while(task[currentTask].state == SLEEP);
}

ISR(TIMER1_COMPA_vect,ISR_NAKED){

    // Sauvegarde du contexte de la tâche interrompue
    SAVE_REGISTER();
    task[currentTask].sp = SP;
    
    // Appel à l'ordonnanceur
    scheduler();
    
    // Récupération du contexte de la tâche ré-activée
    SP = task[currentTask].sp; 
    RESTORE_REGISTER();
    
    asm volatile("reti");
}

void wait(uint8_t reason, uint16_t data){
    cli();
    task[currentTask].state = SLEEP;
    sleep_t sleep;
    sleep.reason = reason;
    sleep.data = data;
    task[currentTask].sleep = sleep;
    TCNT1 = 0;
    sei();
    TIMER1_COMPA_vect();
}

void task0(){ // processus défault ne dort jamais
    while(1){
        _delay_ms(100);
    }
}

void readSerial(){
    initSerial();
    initDevice();
    while(1){
        cli();
        if(checkInterrupt(KEYBOARD)){
            uint8_t buffer_size = bufferSize();
            // uint8_t keyList[buffer_size];
            // grabKeys(keyList, buffer_size-1);
            // keyList[buffer_size - 1] = '\0';
            serialWrite(buffer_size+'0');
            serialWrite('\n');
            serialWrite('\r');
        }
        sei();
    }
}

void writeSerial(){
        while(1){
        _delay_ms(100);
    }
}

void WriteMatrice(){ 
    while(1){
        _delay_ms(100);
    }
}

void Write7Segment(){
    while(1){
        _delay_ms(100);
    }

    // counter = 0;
    // initSPI();
    // while(1){
    //     //Calcul
    //     counter++;
    //     if (counter > 9999) counter = 0;
    //     uint8_t digit1 = counter/1000;
    //     uint8_t digit2 = (counter - digit1*1000) / 100;
    //     uint8_t digit3 = (counter - digit1*1000 - digit2*100) / 10;
    //     uint8_t digit4 = (counter - digit1*1000 - digit2*100 - digit3*10);

    //     selectSlaveSPI(&PORTC, SS3);
    //     transferSPI(0x76);
    //     transferSPI(digit1);
    //     transferSPI(digit2);
    //     transferSPI(digit3);
    //     transferSPI(digit4);
    //     wait(DELAY_SLEEPING, 100);
    //     unselectSlaveSPI(&PORTC, SS3);
    // }
}


void initMinuteur(int diviseur,long periode){
    TCCR1A=0;                                     // Le mode choisi n'utilise pas ce registre
    TCCR1B=(1<<CTC1);                             // Réinitialisation du minuteur sur expiration
    switch(diviseur){
        case    8: TCCR1B |= (1<<CS11); break;
        case   64: TCCR1B |= (1<<CS11 | 11<<CS10); break;
        case  256: TCCR1B |= (1<<CS12); break;
        case 1024: TCCR1B |= (1<<CS12 | 1<<CS10); break;
    }
    // Un cycle prend 1/F_CPU secondes.
    // Un pas de compteur prend diviseur/F_CPU secondes.
    // Pour une periode en millisecondes, il faut (periode/1000)/(diviseur/F_CPU) pas
    // soit (periode*F_CPU)/(1000*diviseur)
    OCR1A= F_CPU/1000*periode/diviseur;          // Calcul du pas
    TCNT1=0;                                    // Compteur initialisé
    TIMSK1=(1<<OCIE1A);                         // Comparaison du compteur avec OCR1A
}

void initTask(uint8_t taskId){
    uint16_t save = SP;
    SP = task[taskId].sp;
    uint16_t address = (uint16_t)task[taskId].addr;
    asm volatile("push %0" : : "r" (address & 0x00ff) );
    asm volatile("push %0" : : "r" ((address & 0xff00)>>8) );
    SAVE_REGISTER();
    task[taskId].sp = SP;
    SP = save;
}

void setup(){
    
    // Setup des tâches
    task[0].addr = &task0;
    task[1].addr = &readSerial;
    task[2].addr = &writeSerial;
    task[3].addr = &WriteMatrice;
    task[4].addr = &Write7Segment;
    
    
    task[0].sp = 0x0300;
    task[1].sp = 0x0400;
    task[2].sp = 0x0500;
    task[3].sp = 0x0600;
    task[4].sp = 0x0700;

    for(uint8_t i = 0; i < NB_TASK; i++){
        initTask(i);
        task[i].state = AWAKE;
    }
 
    // Setup du minuteur 
    initMinuteur(1024,20);

    // On active les interruptions
    sei();
}

int main(){
    setup();
    SP = task[currentTask].sp; 
    task0();
}
