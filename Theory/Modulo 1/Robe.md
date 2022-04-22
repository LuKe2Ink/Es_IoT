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

## Asynchronous Serial

- Non viene utilizzato alcun clock per la comunicazione
- 2 linee TX tramsette RX riceve

La sincronizzazione si ottiene attraverso un protocollo, per garantire una trasmissione robusta ed a prova di errore.

I pin 0,1 di arduino sono associati a RX e TX rispettivamente.

### Parametri del protocollo

1. Baud Rate
   - la velocita' della transmissione [bits/seconds] , 9600 bps
2. data frame
3. Sync bits
4. bit di paritaà

## Synchronous Serial

- Clock utlizzato per sincronizzare la comunicazione tra le parti -> velocita' maggiore (es. I2C SPI)

### I2C

E' un protocollo bus standard, 2 pin richiesti, 2 linee (dati, clock), utilizza un architettura master-slave che include 1 o piu' slaves, tutti i dispositivi condividono le 2 linee:

1. di clock (SCL) per poter sincronizzare la comunicazione
2. di dati bidirezionali (SDA).

Il master inizia le comunicazioni e gli slaves possono solo rispondere al loro messaggio personale, possiedono un ID di 7 bit con cui il master puo indirizzare il comando, dopo la ricezione del messaggio lo slave risponde con un ACK e la fine della comunicazione e' sancita da un bit di STOP.

Un esempio del protocollo I2C e' la misurazione delle temperature del sensore TC74.

Per poter utilizzare il protocollo e' necessario utilizzare la libreria [Wire](http://arduino.cc/en/Reference/Wire) estensione di Stream

### SPI

Lo SPI bus implementa un protocollo seriale full-duplex che permette comunicazioni bidirezionali tra master e slave, utilizza linee diverse per trasmettere e ricevere (diversamente da I2C), anche questo protocollo e' sincrono ed utilizza uno shared clock.

1. linea dello shared clock (SCK)
2. linea shared del Master Out Slave (send data from master -> slave) (MOSI)
3. linea shared Master In Slave (send data from slave -> master) (MISO)
4. linea shared (SS) (selezionare il device)

Per poter utilizzare SPI e' necessario utilizzare la libreria [SPI](https://www.arduino.cc/en/Reference/SPI)

Metodo _transfer()_ per transferire dati, per comunicare con uno slave settiamo il pin dello slave a LOW e chiamiamo SPI.transfer() per passargli dati e poi il pin torna HIGH.

Un esempio e' l'uso del Microchip MCP4231.

## I2C vs SPI

Il primo protocollo funziona solo con 2 linee e la modalita' master-slave e' piu agile mentre SPI puo' lavorare a velocita' piu alte e non necessita di pull-up resistors.
