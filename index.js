var http = require('http').createServer(handler); //require http server, and create server with function handler()
var fs = require('fs'); //require filesystem module
var io = require('socket.io')(http) //require socket.io module and pass the http object (server)

http.listen(8080); //listen to port 8080

function handler (req, res) { //create server
  fs.readFile(__dirname + '/public/index.html', function(err, data) { //read file index.html in public folder
    if (err) {
      res.writeHead(404, {'Content-Type': 'text/html'}); //display 404 on error
      return res.end("404 Not Found");
    }
    res.writeHead(200, {'Content-Type': 'text/html'}); //write HTML
    res.write(data); //write data from index.html
    return res.end();
  });
}

const { SerialPort, ReadlineParser } = require('serialport')
const port = new SerialPort({
    path: '/dev/ttyACM0',
    baudRate: 9600 })
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
//parser.on('data', (data) => {
//    console.log(data)
//})

io.sockets.on('connection', function (socket) {
  // WebSocket Connection
  var secs=0;
  parser.on('data', (data) => {
      // recibo las variables del arduino y las separo
    const [hume, temp, sens, AutoFan, tiem] = data.split(',')

    console.log("\nParametros\n" + hume + "\n" + temp + "\n" + sens + "\n" + AutoFan + "\n" + tiem)
    socket.emit('humedad', hume); //manda el dato al cliente
    socket.emit('temperatura', temp); //manda el dato al cliente
    socket.emit('sensacion', sens); //manda el dato al cliente
    socket.emit('AutoFan', AutoFan); // si es 0 debe estar apagado el ventilador automatico
    socket.emit('tiempo', tiem); //manda el dato al cliente
  }) 
});

io.on('connection', (socket)=>{
  //Prender y apagar el L1
  console.log(socket.listeners());
  socket.on('encenderL1', ()=>{
    port.write('1\n')
  })
  socket.on('apagarL1', ()=>{
    port.write('2\n')
  })
  //Prender y apagar el L2
  socket.on('encenderL2', ()=>{
    port.write('3\n')
  })
  socket.on('apagarL2', ()=>{
    port.write('4\n')
  })
  //Prender y apagar el L3
  socket.on('encenderL3', ()=>{
    port.write('5\n')
  })
  socket.on('apagarL3', ()=>{
    port.write('6\n')
  })
  //Prender y apagar el L4
  socket.on('encenderL4', ()=>{
    port.write('7\n')
  })
  socket.on('apagarL4', ()=>{
    port.write('8\n')
  })
  //Prender y apagar Enchufe 1
  socket.on('encenderL5', ()=>{
    port.write('9\n')
  })
  socket.on('apagarL5', ()=>{
    port.write('10\n')
  })
  //Prender y apagar Enchufe 2
  socket.on('encenderL6', ()=>{
    port.write('11\n')
  })
  socket.on('apagarL6', ()=>{
    port.write('12\n')
  })
  //Prender y apagar Ventilador 1
  socket.on('encenderL7', ()=>{
    port.write('13\n')
  })
  socket.on('apagarL7', ()=>{
    port.write('14\n')
  })
  //Prender y apagar Ventilador 2
  socket.on('encenderL8', ()=>{
    port.write('15\n')
  })
  socket.on('apagarL8', ()=>{
    port.write('16\n')
  })
  //Prender y apagar el modo automatico de los ventiladores
  socket.on('encenderAutoFan', ()=>{
    port.write('21\n')
  })
  socket.on('apagarAutoFan', ()=>{
    port.write('20\n')
  })
});