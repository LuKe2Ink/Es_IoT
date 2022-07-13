const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
var bodyParser = require('body-parser');
const { Server } = require("socket.io");

const serialport = require('serialport');
const SerialPort = require('serialport').SerialPort;
const Readline = require('@serialport/parser-readline');


var gardenObject={
  "led1" : 1,
  "led2" : 1,
  "led3" : 0,
  "led4" : 0,
  "water" : 0,
  "state" : "bella pe te"
};


// const port = new SerialPort({path: 'COM3', baudRate: 9600 , parser:Readline});
// const parser = port.pipe(new Readline.ReadlineParser({ delimiter: '\r\n' }))

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
    gardenObject["temp"] = input.temp;
    gardenObject["bright"] = input.bright;
    res.send("ok")
    sendOnSerial()
});

//da testare
//Get perché deve richiede esclusivamente i dati, non andandoli a modificare
app.get('/garden/dashboard', async function(req, res) { 
  res.send(gardenObject);
});

//da testare
//Pathc perché andrà a modificare parzialmente l'oggetto gardenObject
app.patch('/garden/app/update', async function(req, res) { 
    var input = req.body;
    gardenObject = input;
});
//Get per andare a ritirare i dati necessari
app.get('/garden/app/getData', async function(req,res){
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
    console.log('message written')
  })
}


//serial data

// port.on("open", function () {
//   //console.log('open');
//   parser.on('data', function(data) {
//    console.log(data);
//     // var g = data;
//      //gardenObject = JSON.parse(g);
//      //console.log(gardenObject);
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