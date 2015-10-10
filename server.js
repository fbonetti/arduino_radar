var s = require("serialport");
var SerialPort = s.SerialPort;
var io = require('socket.io')(8050);

var serialPort = new SerialPort("/dev/cu.usbmodem1411", {
  baudrate: 115200,
  parser: s.parsers.readline("\r\n")
});

io.on('connection', function (socket) {
  serialPort.on('data', function(data) {
    var angle = parseInt(data.toString().split("|")[0], 10);
    var distance = parseInt(data.toString().split("|")[1], 10);
    console.log([angle, distance]);
    socket.emit('data', [angle, distance]);
  });
});

