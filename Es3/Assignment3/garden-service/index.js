const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
var bodyParser = require('body-parser');
const { Server } = require("socket.io");

const serialport = require('serialport');
const SerialPort = require('serialport').SerialPort;
const Readline = require('@serialport/parser-readline');


var requestify = require('requestify');
const { Console } = require('console');


var gardenObject;

gardenObject={
  "temp" : 17,
  "bright": 3,
  "led1" : true,
  "led2" : true,
  "led3" : 0,
  "led4" : 3,
  "w" : 0,
  "state" : "bella pe te"
};

// setTimeout(() => {
//   gardenObject={
//     "temp" : 17,
//     "bright": 3,
//     "led1" : true,
//     "led2" : true,
//     "led3" : 0,
//     "led4" : 3,
//     "water" : 0,
//     "state" : "bella pe te"
//   };
// }, 7000);

// setTimeout(() => {
//   gardenObject["state"] = "ribella pe te"
// }, 20000);


const port = new SerialPort({path: 'COM3', baudRate: 9600 , parser:Readline});
const parser = port.pipe(new Readline.ReadlineParser({ delimiter: '\r\n' }))

server.listen(3000, () => {
  console.log('listening on *:3000');
});

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//app.use(parser)

//da testare
//Put perché andrà sempre a modificare i dati correnti
app.put('/garden/sensorboard', async function(req, res) { 
    var input = req.body;
    // console.log(input);
    gardenObject["temp"] = input.temperature;
    gardenObject["bright"] = input.luminosity;
    //res.send("ok sei forte")
    res.send("ok")

    sendOnSerial()
});

//da testare
//Get perché deve richiede esclusivamente i dati, non andandoli a modificare
app.get('/garden/dashboard', async function(req, res) { 
  res.send(gardenObject);
});

app.get('/garden/dashboard/getState', async function(req, res) { 
  res.send(gardenObject.state);
});


//da testare
//Pathc perché andrà a modificare parzialmente l'oggetto gardenObject
app.patch('/garden/app/update', async function(req, res) { 
    var input = req.body;
    gardenObject = input;
});

//Get per andare a ritirare i dati necessari
app.get('/garden/app/getData', async function(req,res){
  while(gardenObject == null){
      return;
  }
  res.send(gardenObject);
})

function sendOnSerial() {
 // console.log('from server')
 // console.log(JSON.stringify(gardenObject))
 // console.log('stop seriale');
  port.write(JSON.stringify(gardenObject), function(err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
    // console.log('message written')
  })
}

function jsonConcat(o1, o2) {
 for (var key in o2) {
  o1[key] = o2[key];
 }
 return o1;
}

//serial data
port.on("open", async function () {
  //console.log('open');
  parser.on('data', async function(data) {
   console.log(data);
    var g = data;
    var j = JSON.parse(g);
    gardenObject = jsonConcat(gardenObject, j);
    // console.log(gardenObject);
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


//serial data
// port.on("open", async function () {
//   //console.log('open');
//   parser.on('data', async function(data) {
//   //  console.log(data);
//     var g = data;
//     gardenObject = JSON.parse(g);
//     console.log(gardenObject);
//     if (gardenObject["state"] == 1){
//       console.log(gardenObject);
//     }
//     if(gardenObject["led_esp"] > 0){
//       requestify.get('http://192.168.1.22/get?led=1')
//       .then(function(response) {
//           // Get the response body (JSON parsed or jQuery object for XMLs)
//           console.log(response.getBody());
//       });
//     } else {
//       requestify.get('http://192.168.1.22/get?led=0')
//       .then(function(response) {
//           // Get the response body (JSON parsed or jQuery object for XMLs)
//           console.log(response.getBody());
// });

//     }
//   });
// });

/*

setInterval(()=> {

port.write("{\"sesso\" : \"bello\"}\n", function(err) {
  if (err) {
    return console.log('Error on write: ', err.message)
  }
  console.log('message written')
})
}, 1000);
*/