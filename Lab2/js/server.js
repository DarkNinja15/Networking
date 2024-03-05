const net = require("net");
const fs = require("fs");
const server = net.createServer();
server.listen(3000, () => {
  console.log("Server is listening on port 3000");
});
const path = (file) => `./server/${file}`;
const c = [];
server.on("connection", (socket) => {
  if(c.length) return;
  socket.on("data", (data) => {
    const fileName = data.toString();
    // console.log(path(fileName));
    if(!fs.existsSync((path(fileName)))) {
      socket.write("Invalid File Path Provided");
    } else {
      const content = fs.readFileSync(path(fileName)).toString();
     
      const json  = {
        fileName,
        content
      };
      socket.write(JSON.stringify(json));
      fs.unlinkSync(path(fileName));
    }
  });
});
