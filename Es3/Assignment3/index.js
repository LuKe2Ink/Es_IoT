const serialport = require('serialport');
const SerialPort = require('serialport').SerialPort;
const Readline = require('@serialport/parser-readline');
const port = new SerialPort({path: 'COM3', baudRate: 9600 , parser:Readline});
const parser = port.pipe(new Readline.ReadlineParser({ delimiter: '\r\n' }))


port.on("open", function () {
  console.log('open');
  parser.on('data', function(data) {
  
    console.log(data);
  });
});