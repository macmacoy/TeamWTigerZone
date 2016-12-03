# TeamWTigerZone

This is our TigerZone game base and ai implementation.  In order to run and compile the program follow these steps.  First, bring up the command line interface in a linux machine.  

## Compilation

### From the command line interface

+ `git clone https://github.com/macmacoy/TeamWTigerZone`

+ `cd TeamWTigerZone`

+ `git pull`

+ `g++ mainClient.cpp -std=c++11 -o mainClient`

## Running the Client

### From the command line interface (root directory)

`./mainClient`


## Issues Encountered
### Jungle Tiger Placement:
We had issues with debugging the checking mechanism for placing a jungle tiger.  We found that a jungle tiger is significantly more complex than checking completed road or lake.  Using imagery and diagrams we realized that the task of setting up jungle tigers can be ultimately removed for coding efficiency.  Thus, we deferred the development of this task until we had all other tasks complete.
### Client Issues:
We were unable for multiple days to get our client to properly function.  At first the issue was with translating the inputs that were given by the server, more about this in the next paragraph.  The second issue was a problem caused by an issue with our method that places tiles.  After using some debugging programs, we determined that the tiles that were being placed by the tile placer were empty.  Our workaround for this issue was to circumvent the place tile method and instead call the game board directly to get it to place the tile instead thus solving the problem.  Whilst solving this issue an invaluable tool in debugging the programs was gdb which is a linux debugging program.
### Translating the Server Outputs:
For a period, the information that was given to us by the server was completely unusable.  We had to create a method that would take that input and turn it into usable information.  Thus we made a translator.   However, this translator had issues with spaces that had worked around with various tricks, such as creating additional buffers which would allow us to take in the input better.
### Server Coding Logic:
Our program can create a connection between our client and the server.  However, the server side logic that allows the programs to function cooperatively is not working. Our ability to connect to the server is severed by the miscommunication between the server and the client.  The receive function is blocking the communication.  Our ability to receive the information given by the server is handicapped.


## Group Members
 * Mac Macoy (macmacoy)
 * Shen Jiantao (karthshen)
 * Nathan Marshall (narshall16)
 * Chesalon Taylor (chetaylo844)
 * Shawn Newsome (snewsome)
 * Michael Arena (mxiia)
