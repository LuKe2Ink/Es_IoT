const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
var bodyParser = require('body-parser');
const { Server } = require("socket.io");

const serialport = require('serialport');
const SerialPort = require('serialport').SerialPort;
const Readline = require('@serialport/parser-readline');

var gardenObject={};


const port = new SerialPort({path: 'COM3', baudRate: 9600 , parser:Readline});
const parser = port.pipe(new Readline.ReadlineParser({ delimiter: '\r\n' }))

server.listen(3000, () => {
  console.log('listening on *:3000');
});

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//app.use(parser)

// da testare
app.post('/garden/boardsensor', async function(req, res) { 
  
    var r = {
      "cacca" : "popo"
    }
    res.send(r)
  
    console.log(req.body)
});

// da testare
app.post('/garden/dashboard', async function(req, res) { 
  console.log(req.body)
  res.send(gardenObject)
});

// da testare
app.post('/garden/app', async function(req, res) { 
    console.log(req.body)
});

//serial data

port.on("open", function () {
  //console.log('open');
  parser.on('data', function(data) {
   console.log(data);
    var g = data;
    gardenObject = JSON.parse(g);
  });
});
