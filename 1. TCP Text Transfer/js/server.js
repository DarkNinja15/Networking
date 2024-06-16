// create a tcp server using net module


const net = require('net');
const readline = require('readline');
const server = net.createServer();

server.listen(3000, () => {
    console.log('Server is listening on port 3000');
});


const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
  });

server.on('connection', (socket) => {
  socket.on('data', (data) => {
    console.log("[Client]: " + data.toString());
    // take input from user in console
  
    rl.question('Enter your message: ', (answer) => {
      console.log(`[Server]: ${answer}`);
      socket.write(answer);
    });
  });
  });
