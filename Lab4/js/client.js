const dgram = require('dgram');
const readline = require('readline');

const client = dgram.createSocket('udp4');
const rl = readline.createInterface({
  input:process.stdin,
  output:process.stdout,
});

client.on('message',(msg)=>{
  console.log(`[Server]: ${msg}`);
  rl.question('Enter message to send : ',(ans)=>{
    client.send(ans,3000,'127.0.0.1',(err)=>{
      if(err){
        console.log(err);
      }
      else{
        console.log('Message sent');
      }
    });
  });
});

client.on('error', (err) => {
  console.error(`UDP client error:\n${err.stack}`);
  client.close();
});

client.on('close', () => {
  console.log('UDP client closed.');
});

rl.question('Enter message to send : ',(ans)=>{
  client.send(ans,3000,'127.0.0.1',(err)=>{
    if(err){
      console.log(err);
    }
    else{
      console.log('Message sent');
    }
  });
});