# minitalk
#### Client-server interaction using user-defined signal SIGUSR1 and SIGUSR2
The server, after starting, prints its pid. The client using the pid of the server can send him a message. The server works with one client at a time. 
A new client connection does not require a server restart. 
The client is started like this ./client [serv_pid] [msg]

use the following command to clone along with the library:
```
git clone https://github.com/Talyx/minitalk --recurse-submodules
```
