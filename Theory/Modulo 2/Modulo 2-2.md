# Embedded systems con macchine a stati finiti

Gli stati finiti sono compatibili con macchine che hanno dinamiche concrete, con funzioni tipicamente legate al tempo in cui vengono eseguite o perdurano.  

Modello -> operare su un astrazione.

**FSM** (finite state machine) una macchina in cui il numero di stati e' finito, si muove attraverso transizioni azionate da eventi di input catturati e valutati.  

## differenza tra FSM sincrona e asincrona

- Asincrona
  - Event triggered, ogni evento nella macchina provoca una valutazione ed un eventuale cambiamento di stato
- Sincrona
  - Time-triggered, la valutazione degli input avviene ogni periodo _P_ di tempo (macchine piu' usate)

## Fac-Simile di FSM

```cpp
/* global vars used by the machine */
int a0, b0, ...
/* variable keeping track of the state */
enum States {...} state;
/* procedure implementing the step of the state machine */
void step(){
    switch(state) {
        case ...
        case ...
    }
}
loop(){
    step();
}
```

Quando si usano FSM Sincrone il loop deve essere eseguito con un periodo specificato.

## EFSM Extended FSM

Sono macchine in cui le variabili sono utlizzate per descrivere lo stato, cambiano anch'esse con lo stato (?)

Il numero totale degli stati in una EFSM si calcola con la formula |stati| = n * p^m.  

> n = n stati
> m = n variabili per descrivere lo stato
> p = possibili valori delle variabili

## Time-triggered (IMPORTANTE)

Gli embedded systems sono time-oriented generalmente, il tempo e' una parte fondamentale da gestire, le macchine sincrone sono state introdotte proprio per fornire la gestione del tempo in modo efficente e semplificarne l'uso.  

In queste macchine lo "step" di una macchina e' eseguito periodicamente ed e' scandito dal periodo _P_, come se le macchine FSM avessero un clock interno e le transizioni possano verificarsi solo al tick di quel clock. Solitamente i timer programmabili sono usati per implementare FSM Sincrone e generare un interrupt ad una frequenza che porti ad un (eventuale) cambiamento di stato della macchina

```cpp
volatile int timerFlag = 0;

void timerISR(){
    timerFlag = 1;
}
/* procedure implementing the step of the state machine */
void step(){...}

loop(){
    while (!timerFlag){}; /* wait for a tick for doing the next step */
    timerFlag = 0;
    step();
}
```

## INPUT Sampling (IMPORTTANTE)

Il sampling (saggiatura ??) e' il termine con il quale si indica la lettura periodica dei sensori con una precisa frequenza (-> con periodo). La scelta di questo periodo e' critica per il funzionamento della macchina sincrona FSM, non deve essere ne troppo piccolo (perdita di eventi) ne troppo grande (overrun exceptions).  

Maggiore la frequenza -> minore il periodo e quindi

- maggiore la reattivita'
- maggiore consumo del microcontrollore

Strategy: il periodo dovra' essere il miglior valore del range che garantisce di non perdere eventi e il corretto funzionamento del sistema.

Il MEST (minimum event separation time) e' il minor intervallo di tempo che puo' verificarsi tra 2 eventi di tipo input all'interno del sistema in cui il microcontrollore sta lavorando.

In una FSM Sincrona il **TEOREMA MEST** dice che scegliendo il _P_ minore del MEST si ha la certezza che tutti gli eventi saranno rilevati e non si perderanno.

Con il diminuire del periodo si diminuisce anche la latenza (ritardo con il quale dopo un input si ha un output), a volte interviene anche il condizionamento degli input per il quale si ha un piccolo ritardo anche a causa del HW ad esempio il bouncing del pulsante (si puo risolvere vis SW ad esemio scegliendo un periodo di Sampling < del periodo di rimbalzo del pulsante).

**Nelle slide ci sono molte pagine taggate importanti, sarebbe meglio darci un occchiata**
