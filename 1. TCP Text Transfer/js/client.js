// write a tcp client using net module
//

const net = require('net');
const rl = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

const client = net.createConnection({
  port: 3000,
  host: 'localhost'
});

client.on('connect', () => {
  console.log('Connected to server');
  rl.question('Enter your message: ',ans => {
    console.log(`[Client]: ${ans}`);
    client.write(ans);
  })
  });

client.on('data', (data) => {
  console.log("[Server]: " + data.toString());
  rl.question('Enter your message: ', (answer) => {
  console.log(`[Client]: ${answer}`);
  client.write(answer);
    });
});
