# Appunti

## 1.1

## 1.2

### CPU

La cpu segue possiede un architettura di tipo di Von Neumann _fetch-decode-execute_, gli interrupts sono abilitati in questa architettura.  
La velocita del clock del processore e' di 16Mhz -> 62.5 nanosecondi e la maggior parte delle istruzioni sono eseguite utilizzando 1/2 cicli di clock quindi in un tempo che puo' variare tra i 60 e 125 nanosecondi ciascuna.

### Super Loop

Composto da setup() ossia inizializzazione e loop(), esiste un main nascosto che chiama queste funzioni, il compilatore che crea gli eseguibili e' **avr-gcc**.

### GPIO

Arduino composta da:
  
  1. 14 pin **digitali**
  2. 6 pin **analogici**

Alcuni possono essere mulitplexed come lo 0 e 1 (trasmettono e ricevono bit).  

I pin comunicano con l' MCU (micro controller unit) tramite porte, che sono gestite da uno o piu' registri multi-purpose (srf).

### ATMega328P

Ha 23 I/O linee raggruppate in 3 porte da 8-bit B(0-7) C(pin analogici)  e D(8-13), ogni porta e' gestita da 3 registri

- DDRx
  - this register is both Read/Write and stores the configured direction for the pins (bit set to 0 => pin configured as INPUT; bit set to 1 => pin configured as OUTPUT)
- PORTx
  - this register is both Read/Write and stores the pin state, which changes depending on the pin configuration:
    1. for INPUT pins, then a bit set to 1 activates the PULL-UP resistor, while a bit set to 0 deactivates it;
    2. for OUTPUT pins, then a bit set to 1 represents a state set to HIGH on the corresponding pin, while a bit set to 0 represents a state set to LOW
- PINx
  - this register is read-only, and stores, for INPUT pins, the signal value read connected to the pin: 1 if the signal value is HIGH; 0 if the signal value is LOW

Quindi per poter configurare la modalita' OUTPUT e settare HIGH ad esempio un pin noi andiamo a scrivere il bit dei suoi registri DDRx e PORTx, in un ATMega328 i registri sono localizzati a partire dall' indirizzo 0x20, dopo i general purpose.

### delay()

La funzione di delay esegue un busy waiting per un numero di millisecondi, interferisce quando utilizziamo interrupts e simili poiche' a sua volta li utilizza, definita come

```cpp
/* wiring.c */
void delay(unsigned long ms){
    unsigned long start = millis();
    while (millis() - start <= ms)
        ;
}
```

### millis()

Return number of  milliseconds elapsed since the power on of the device.

### PULSE-WIDTH-MODULATION (PWM)

Metodo per generare un segnale analogico su pin digitali tramite la generazione di onde quadrate periodiche, che oscillano tra HIGH e LOW, il voltaggio (emulato) e' generato dal duty cycle del segnale ossia **la percentuale di tempo che il segnale e' HIGH rispetto a quando e' LOW**

### Analog pins

I pin possono assumere un qualsiasi valore di voltaggio entro i 0-5V, questo segnale deve essere convertito tramite l' **ADC** (analog to digital converter)    che mappa il voltaggio in un range discreto (0-1023) tramite la propria risoluzione.

### map()

to map a value from a range (e.g. 0...1023) into another application-level range (e.g. 0..255).

### Interrupt

#### Interrupt Requests

when an interrupt request is receive, the CPU suspends the execution of current instructions (e.g. the super-loop), it saves on a stack the address of the next instruction to be executed, and jumps (tranfers the control) to the routine (procedure) configured to react to the event - called interrupt handler o interrupt service routine (ISR).

```cpp
attachInterrupt(intNum, ISR, mode);
/*
    intNum: numero interruzione (int)
    
    ISR: puntatore all’interrupt handler (tipo: void (*func)(void))

    mode: quando deve essere generata l’interruzione: CHANGE/FALLING/RISING: ad ogni cambiamento, 1 -> 0, 0 -> 1 (logici) LOW/HIGH: quando è 0 o 1 (logici)
*/
```

#### Disable Interrupts

E' possibile disattivare e riattivare gli interrupt all'interno del programma per poter evitare i problemi di concorrenza.

```cpp
noInterrupts();
Interrupts();
```

Il sistema non e' piu' responsive se disattivati.

### Power Management

![power mode](https://i.imgur.com/iBfQrnw.png)
