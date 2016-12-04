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
We were unable for multiple days to get our client to properly function. We were finally able to play a game against our own test server, where we would send messages in the order of the test case on the class website. Our client would connect to the server. It would recieve "THIS IS SPARTA", and we would send "JOIN TIGERZONE". After that, no other messages were recieved or sent. The problem obviously lies on the client side. We are currently trying to fix our bugs by examining our while loop that busy waits until it recieves a message and the placement of recv() and send().

## Group Members
 * Mac Macoy (macmacoy)
 * Shen Jiantao (karthshen)
 * Nathan Marshall (narshall16)
 * Chesalon Taylor (chetaylo844)
 * Shawn Newsome (snewsome)
 * Michael Arena (mxiia)
