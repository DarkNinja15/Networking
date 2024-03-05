const dgram = require('dgram');
const readline = require('readline');

const server = dgram.createSocket('udp4');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

server.on('message', (message,rinfo) => {
    console.log(`[Client]: ${message}`);

    rl.question('Enter your message: ', (ans) => {
        server.send(ans, rinfo.port, rinfo.address, (err) => {
            if (err) {
                console.log(err);
            } else {
                console.log(`[Server]: ${ans}`);
            }
        });
    });
});

server.on('listening', () => {
    const address = server.address();
    console.log(`Listening on ${address.address}:${address.port}`);
});

server.bind(3000, '127.0.0.1');

server.on('error', (err) => {
    console.log(err);
    console.log('Some error occurred');
    server.close();
});

server.on('close', () => {
    console.log('Server closed');
});
