# Mod 2.3

## Task based Arch

Un problema si puo' scomporre in piu' moduli che possono essere eseguiti da un ugual numero di taks concorrenti, il comportamento di ogni task puo essere descritto da una FSM.

> Es Led-show

1 led blinking

3 led che ON/OFF in sequenza con _P_ = 500ms

Si puo' modellare come un singolo task, ma e' piu comodo pensare a 2 task distinti che si occupano del led singolo e della tripletta.

![first task](https://imgur.com/4ByTy4D.png)

> fine

Ogni task e' indipendente dagli altri, riusabile, facilmente debuggabile e le interfacce possono essere scambiate con altri moduli ma i task sono anche concorrenti e potrebbero avere dipendenze.

## Task "Class"

- init method
- tick method (lo step nelle FSM)

## Scheduler

Per poter gestire task con differenti _P_ possiamo implementare un cooperative scheduler multi-tasking che terra' traccia di tutti i task da eseguire.

Utilizza la **Cooperative round-robin** strategy

- _P_ e' il massimo comune divisore dei periods dei tasks
- ad ogni _P_ chiama il proprio metodo tick e fa avanzare ogni task
- internamente usa un timer per poter realizzare il suo comportamento periodico

> Es led-show con Scheduler

![led-show-sheduler](https://imgur.com/FvAJzxr.png)

Un utilizzo diverso di timer e interrupts nei task comporta un'implementazione particolare dello step dello scheduler direttamente all'interno dell interrupt/timer -> interrupt-driven schedulers.  

## Tasks dependencies

Le dipendenze e le interazionin tra tasks sono gestite con l'uso di variabili condivise tra i tasks, normalmente queste variiabili potrebbero condurre verso race conditions (letture/scritture concorrenti) ma nel nostro caso essendo cooperative ogni task e' eseguito in sequenza ed il sistema e' atomico da fuori.

Se il _P_ dello scheduler e' abbastanza lungo e' possibiile utilizzare la sleep mode per poter risparmiare batteria.

## Overrun

Un overRun exception si verifica quando il tempo impiegato dalle azioni dei tasks supera il _P_ (diventa timer overRun quando lo scheduler utilizza interrupts). Queste overRun exceptions si possono individuare attraverso l'analisi del codice stimando la durata totale delle azioni e se il tempo impiegato supera il worst case scenario.

## tempo utilizzazione CPU

U = (time used for a task by the CPU / total time) * 100%

il WCET e' il tempo di esecuzione nel caso peggiore.  

Nel caso in cui dopo il calcolo di U scopriamo che e' maggiore del 100% esiste un overRun exception e si puo risolvere

- aumentando il period della FSM
- ottimizzando la sequenza di istruzioni per ridurre il WCET
- modulare blocchi di sequenze in azioni piu' piccole
- una MCU piu veloce
- disabilitare funzzionalita' dal sistema

Nel caso di task multipli il WCET e' la somma dei WCET dei singoli task, il WCET puo' essere calcolato come il minimo comune multiplo dei WCET (hyper-period)

## Jitter

Il tempo che aspetta un task pronto prima di poter essere effettivamente eseguito, differenti strategie di scheduling possono portare a diversi jitters.

## Deadline

Definita come l'intervallo di tempo in cui ogni task deve essere eseguito dopo essere diventato pronto per l'esecuzione, nel caso in cui questa deadline non sia rispettata abbiamo un missed-deadline-exception -> system failure.

## Static and dynamic priority

- Lo scheduler seleziona il task con priorita' piu' alta se ce ne sono piu' di uno pronti contemporaneamente
- priorit' statica -> assegnata durante la progettazione ed immutabile
- priorita' dinamica -> assegnata dinamicamente in base a strategie
  
## Task sporadici

Normalmente i task sono statici ossia non cambiano una volta che il sistema e' messo in moto ma esistono anche task che possono essere eseguiti arbitrariamente.
