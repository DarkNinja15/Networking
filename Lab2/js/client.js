const net = require('net');
const fs = require("fs");
const rl = require('readline').createInterface({ input: process.stdin, output: process.stdout });
const client = net.createConnection({ port: 3000, host: 'localhost' });
client.on('connect', () => {
  console.log('Connected to server');
  rl.question('Enter the File: ',ans => {
    console.log(`[Client]: ${ans}`);
        client.write(ans);
  })
});

const path = (file) => `./client/${file}`;
client.on('data', (data) => {
    try {
    const json = JSON.parse(data.toString());
    
    const { fileName, content } = json;
    const savePath = path(fileName);
    fs.writeFileSync(savePath,content);
    console.log("Successfully transferred file: ",fileName);
  } catch (e) {
    // console.error(e);g
    console.log("[Server]: "+data.toString());
  }
    rl.question('Enter the File: ',ans => {
    console.log(`[Client]: ${ans}`);
        client.write(ans);
  })
});
