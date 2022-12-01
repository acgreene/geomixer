const { SerialPort } = require('serialport');

const { ReadlineParser } = require('@serialport/parser-readline');

// documentation: https://expressjs.com
const express = require('express');

// initialize instance of express.
const app = express();
app.set('view engine', 'ejs');

// boilerplate code for whenever we make json requests with server.
app.use(express.json());

// update teensy serial port path here, Arduino IDE > Tools > Port menu 
let teensySerialPort = "/dev/cu.usbmodem118933801";

const port = new SerialPort({ 
    path: teensySerialPort, 
    baudRate: 9600 
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

// Read the port data
port.on("open", () => {
  console.log('serial port open');
});

// parser.on('data', data => {
//   console.log('got word from arduino:', data);
// });

app.use(express.static("public"));

port.write('node.js connected to teensy');

app.post('/mouse', async (req, res) => {
  let mixes = req.body;
  let serialMsg = '';
  for (let j = 0; j < mixes.length; j++) {
    serialMsg += mixes[j].name.toString().charAt(0) + ' ' + mixes[j].mix.toFixed(3).toString() + ', ';
  }

  console.log(serialMsg);

  res.send({});

  port.write(serialMsg);
})

app.listen(3000);