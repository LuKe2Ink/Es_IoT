# Relazione Assignment 2

In questo progetto ci e' stato richiesto di realizzare una macchina del caffe utilizzando la scheda arduino e la programmazione di task asincroni.

[File con specifiche](https://docs.google.com/document/d/171kcL1d1lW2kN3RdDfdvIkdIngGn8EvuipJRH7uKnXo/edit?usp=sharing)

Abbiamo deciso di preparare subito un diagramma con il quale ci siamo chiariti le idee su come i vari task saranno poi stati divisi e progettati, la nostra intenzione e' stata quella di inserire nell loop solo ed esclusivamente la funzione schedule della Classe Scheduler, alla quale abbiamo aggiunto mano a mano i vari task.

```cpp
/* Scheduler.cpp*/

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){ 
  while (!timerFlag){}  
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}

```

# Machine

Per comodita' abbiamo deciso di creare una classe che chiudesse al proprio interno tutte i sensori e le funzionalita' della macchina, instanziandola solo una volta e' come se possedessimo una macchina del caffe e passassimo il riferimento a questo oggetto ai vari task.

```cpp
/* Machine.h */

#ifndef __MACHINE__
#define __MACHINE__

#include "Display.h"
#include "Product.h"
#include "ButtonImpl.h"
#include "ServoMotorImpl.h"
#include "Temp.h"
#include "Pir.h"


#define N_MAX_QUANTITY 50
#define T_OUT 5000L
#define T_MAKING 55

#define B_UP 2
#define B_DOWN 3
#define B_MAKE 4
#define PIR_PIN 5
#define TRIG_PIN 7
#define ECHO_PIN 8
#define SONAR_DISTANCE 40
#define SERVO_PIN 10
#define TEMP_PIN A0

#define PROD_NUM 3

enum stato{
  WELCOME,
  READY,
  SELECT,
  MAKING,
  WAITING_REMOVING,
  ASSISTANCE,
  SLEEP
};


class Machine {
  public:
    Machine();
    NewPing* sonar;
    Pir* pir;
    ServoMotor* servo ;
    Display* display_lcd ;
    Temp* temp;
    Product* coffee ;
    Product* tea ;
    Product* chocolate ;
    Button* bUp;
    Button* bDown ;
    Button* bMake ;
    stato state;
    int checkDone;
    bool lastMove;
};

#endif
```

# Selection Task

Il task Selection racchiude in se buona parte della logica della macchinetta, dalla selezione dei prodotti alla loro produzione e quindi ai vari controlli dei sensori di prossimita' e presenza.

![Selection Task Diagram](https://github.com/LuKe2Ink/Es_IoT/raw/main/Es2/SelectionTask.png)

# Check Task

Il Task di check effettua una routine per la quale la macchinetta controlla periodicamente che i suoi componenti funzionino correttamente, l'utlizzo di un contatore all'interno rende comodo effettuare il task ogni 180 secondi, tempo che altrimenti sarebbe stato difficilmente assegnabile come period nella dichiarazione della task.

![Check Task Diagram](https://github.com/LuKe2Ink/Es_IoT/raw/main/Es2/checkTask.png)


# Sugar Task

Terzo task da noi individuato, ad ogni tick questo task controlla che il selettore di zucchero (il potenziometro) non sia stato mosso, altrimenti se mosso oltre una certa soglia modifica e stampa a display la quantita' di zucchero che la nostra bevanda selezionata  dovra' contenere.
