const dgram = require('dgram');
const fs = require('fs');
const readline = require('readline');

const client = dgram.createSocket('udp4');
const rl = readline.createInterface({ input: process.stdin,output:process.stdout });
const PORT = 5000;
var fileName;

client.on('error', (err) => {
  console.log(`Client error:\n${err.stack}`);
  client.close();
});

client.on('message', (msg, rinfo) => {
  console.log(`Client received ${msg.length} bytes from ${rinfo.address}:${rinfo.port}`);
  if(msg=="-1"){
    console.log('File is not avaliable at the moment.');
    getFileName();
  }
  else{
    fs.writeFile(`recieved_files/${fileName}`, msg, (err) => {
      if (err) {
        console.error(`Error writing file: ${err.message}`);
      } else {
        console.log('File received and saved successfully.');
      }
      getFileName();
    });
  }
  function getFileName(){
    rl.question('Enter file name : ',(ans)=>{
      fileName=ans;
      client.send(ans,PORT,'127.0.0.1',(err)=>{
          if(err){
              console.log(err);
          }
          else{
              console.log( `Message sent to server` );
          }
      });
  });
  }
});






client.on('listening',()=>{
    
});

rl.question('Enter file name : ',(ans)=>{
  fileName=ans;
    client.send(ans,PORT,'127.0.0.1',(err)=>{
        if(err){
            console.log(err);
        }
        else{
            console.log( `Message sent to server` );
        }
    });
});
