const dgram = require('dgram');
const fs = require('fs');

const server = dgram.createSocket('udp4');

server.on('error', (err) => {
    console.log(`Server error:\n${err.stack}`);
    server.close();
});

server.on('message', (msg, rinfo) => {
    console.log('Request for : '+msg);
    fs.readFile(`server_files/${msg}`, (err, data) => {
        if (err) {
            // console.error(`Error reading file: ${err.message}`);
            server.send("-1",rinfo.port, rinfo.address, (err)=>{
                if(err){
                    console.log(err);
                }
                else{
                    console.log('File was not found');
                }
            });
        }
        else{
            server.send(data, 0, data.length, rinfo.port, rinfo.address, (err) => {
                if (err) {
                    console.error(`Error sending file: ${err.message}`);
                } else {
                    console.log('File sent successfully.');
                }
            });
        }
        
    });

    
});

server.on('listening', () => {
    const address = server.address();
    console.log(`Server listening on ${address.address}:${address.port}`);
});

server.bind(5000,'127.0.0.1');
