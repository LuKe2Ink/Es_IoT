# cose

- Sulla seriale c'e' un limite di 64 bytes e tronca i messaggi

## App

## Controller

## Dash-Board

## Sensor-Board

Questa parte del assignment è svolta dall'esp, all'interno della funzione di setup l'esp si collega al wifi, successivamente abbiamo un server
per poter gestire alcune richieste HTTP grazie alla libreria **ESPAsyncWebServer** all'indirizzo IP dell'esp che viene stampato subito prima.

```cpp
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->getParam("led")->value() == "1"){
        digitalWrite(RED, HIGH);
        } else {
          digitalWrite(RED, LOW);
          }
      // request->send(200, "text/plain", "Led received state");
    });
```

Questa funzione asincrona permette di poter attivare il led in caso di ALARM direttamente dal service tramite una semplice GET con attributo led=1.

Il sensor board quindi si occupa di segnalare lo stato di ALARM che viene triggerato da alcuni parametri, uno dei quali viene rilevato dall'esp, come
la temperatura ed anche di rilevare la luce tramite l'apposito sensore.

Dopo avere eseguito una rilevazione, questa viene compattata all'interno di un file JSON e inviata al server di garden service, per fare ciò abbiamo
utilizzato ngrok in modo da poter eseguire una POST ad un indirizzo IP pubblico sul quale in realtà è in ascolto il nostro server.

## Service

Per la creazione del server di ascolto abbiamo deciso di utilizzare NodeJS, dato che in parte sapevamo come usarlo in parte volevamo imparare qualcosa
di nuovo.

La cosa più complicata è stata la gestione della seriale attraverso nodeJS ma alla fine ci siamo riusciti, si deve prima importare due moduli

```js
const SerialPort = require('serialport').SerialPort;
const Readline = require('@serialport/parser-readline');
```

Dichiare due oggetti che serviranno a parsare i messaggi con uno specifico delimitatore e una porta seriale con i classici parametri di arduino.

```js
const port = new SerialPort({path: 'COM3', baudRate: 9600 , parser:Readline});
const parser = port.pipe(new Readline.ReadlineParser({ delimiter: '\r\n' }))
```

Per poi definire la funzione che sarà in ascolto di tutti i messaggi sulla porta seriale, abbiamo fatto la scelta di usare il formato JSON per la comunicazione e questa funzione tenta di parsare ogni cosa che viene parsata sulla seriale come un JSON e si blocca quando vede ad esempio del
normale testo. Qui leggiamo anche il parametro *led_esp* è settato ad uno dall'arduino ossia ci troviamo in uno stato di ALARM e inviamo una GET
al server che sta runnando sull'esp.

```js
//serial data
port.on("open", async function () {
  parser.on('data', async function(data) {
   console.log(data);
    var g = data;
    var j = JSON.parse(g);
    gardenObject = jsonConcat(gardenObject, j);
    if(gardenObject["led_esp"] > 0){
      requestify.get('http://192.168.1.22/get?led=1')
      .then(function(response) {
          // Get the response body (JSON parsed or jQuery object for XMLs)
          // console.log(response.getBody());
      });
    } else {
      requestify.get('http://192.168.1.22/get?led=0')
      .then(function(response) {
          // Get the response body (JSON parsed or jQuery object for XMLs)
          // console.log(response.getBody());
      
});
}});
});
```

Utiizziamo una funzione scritta da noi (jsonConcat) per concatenare il JSON ricevuto da arduino a quello gia presente sul server, questo per risolvere uno dei problemi piu grandi che abbiamo incontrato durante lo sviluppo di questo assignment, ossia il troncamento di messaggi.
A quanto pare arduino, dopo un periodo variabile di tempo inviava messaggi troncati che bloccavano l'esecuzione del server e di tutto il processo, apparentemente il buffer della seriale ha una specie di limite di bytes e periodicamente deve svuotare questo buffer, all'inizio avevamo incluso tutti i parametri all'interno di uno stesso JSON direttamente dall'arduino ma questa cosa oltre a non essere precisa dava questo problema sporadicamente.

Perciò dopo la divisione dei JSON dell'esp e dell'arduino è stato più semplice lavorare e dopo la ricezione del JSON dal sensor-board(esp) abbiamo inserito la funzione per poter scrivere sulla seriale i dati appena ricevuti.

```js
//Get per andare a ritirare i dati necessari
app.get('/garden/app/getData', async function(req,res){
  while(gardenObject == null){
      return;
  }
  res.send(gardenObject);
})

function sendOnSerial() {
  var esp_obj = {
    "t" : gardenObject["t"],
    "b" : gardenObject["b"],
  }
  port.write(JSON.stringify(esp_obj), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    console.log('message written on serial')
    console.log(JSON.stringify(esp_obj))
  })
}
```
