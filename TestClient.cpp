#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

int main()
{
    /* ---------- INITIALIZING VARIABLES ---------- */

    /*  
       1. client is a file descriptor to store the values 
       returned by the socket system call and the accept 
       system call.
       2. portNum is for storing port number on which
       the accepts connections
       3. isExit is bool variable which will be used to 
       end the loop
       4. The client reads characters from the socket 
       connection into a dynamic variable (buffer).
       5. A sockaddr_in is a structure containing an internet 
       address. This structure is already defined in netinet/in.h, so
       we don't need to declare it again.
        DEFINITION:
        struct sockaddr_in
        {
          short   sin_family;
          u_short sin_port;
          struct  in_addr sin_addr;
          char    sin_zero[8];
        };
        6. serv_addr will contain the address of the server
    */

    int client;
    int portNum = 1500; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 4096;
    char buffer[bufsize];
    string recieved;
    char* ip = "127.0.0.1";

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    /*
        The socket() function creates a new socket.
        It takes 3 arguments,
            a. AF_INET: address domain of the socket.
            b. SOCK_STREAM: Type of socket. a stream socket in 
            which characters are read in a continuous stream (TCP)
            c. Third is a protocol argument: should always be 0. The 
            OS will choose the most appropiate protocol.
            This will return a small integer and is used for all 
            references to this socket. If the socket call fails, 
            it returns -1.
    */

    cout << "\n=> Socket client has been created..." << endl;
    
    /* 
        The variable serv_addr is a structure of sockaddr_in. 
        sin_family contains a code for the address family. 
        It should always be set to AF_INET.
        htons() converts the port number from host byte order 
        to a port number in network byte order.
    */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    // this function returns returns 1 if the IP is valid
    // and 0 if invalid
    // inet_pton converts IP to packets
    // inet_ntoa converts back packets to IP
    //inet_pton(AF_INET, ip, &server_addr.sin_addr);

    /*if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server " << inet_ntoa(server_addr.sin_addr) << " with port number: " << portNum << endl;*/


    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;

    /* 
        The connect function is called by the client to 
        establish a connection to the server. It takes 
        three arguments, the socket file descriptor, the 
        address of the host to which it wants to connect 
        (including the port number), and the size of this 
        address. 
        This function returns 0 on success and -1 
        if it fails.
        Note that the client needs to know the port number of
        the server but not its own port number.
    */

    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";

    cout << "\n\n=> Enter # to end the connection\n" << endl;

    // Once it reaches here, the client can send a message first.

    while(!isExit)
    {
        cout << "Player: ";
        while(*buffer != 10 || *buffer != 13)
        {
			//send out messages
            cin >> buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = 13;
                isExit = true;
            }
        }

		//NEED A WAY TO RECIEVE MULTIPLE MESSAGES FROM SERVER
		//currently only is set up for 1 send and 1 recieve at a time
        cout << "Server: ";
        while(*buffer != 10 || *buffer != 13)
        {
            recv(client, buffer, bufsize, 0);
            //append message to string
            recieved.append(buffer[0], buffer[bufsize]);
            
            //if checks for each possible incoming message
            if(recieved.compare(0, 4, "MAKE") == 0)
            {
				//make move with given game id
			}
			else if(recieved.compare(0, 4, "GAME") == 0)
            {
				//Check for every game statement from opponent and change
				// our board accordingly
			}
			else if(recieved.compare(0, 4, "THIS") == 0)
            {
				//do join message
			}
			else if(recieved.compare(0, 4, "HELL") == 0)
            {
				//put password
			}
			else if(recieved.compare(0, 4, "WELC") == 0)
            {
				//store our player id?
			}
			else if(recieved.compare(0, 4, "NEW ") == 0)
            {
				//store challenge id?
			}
			else if(recieved.compare(0, 4, "BEGI") == 0)
            {
				//store round id?
			}
			else if(recieved.compare(0, 4, "YOUR") == 0)
            {
				//store opponent id?
			}
			else if(recieved.compare(0, 4, "STAR") == 0)
            {
				//create two engines, place starting tile in each
			}
			else if(recieved.compare(0, 4, "THE ") == 0)
            {
				//store remaining tiles IN ORDER as decks for each game
			}
			else if(recieved.compare(0, 4, "MATC") == 0)
            {
				//need to do anything with countdown for match?
			}
			else if(recieved.compare(0, 4, "END") == 0)
            {
				//check if end of round or challenge
			}
			else if(recieved.compare(0, 4, "PLEA") == 0)
            {
				//do anything while waiting for next challenge to begin?
			}
			else //message will be "THANK YOU FOR PLAYING! GOODBYE"
            {
				//end games
				//close connection
				isExit = true;
			}
            
            
            
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = 13;
                isExit = true;
            }

        }
        cout << endl;

    }

    /* ---------------- CLOSE CALL ------------- */
    /* ----------------- close() --------------- */

    /* 
        Once the server presses # to end the connection,
        the loop will break and it will close the server 
        socket connection and the client connection.
    */

    cout << "\n=> Connection terminated.\nGoodbye...\n";

    close(client);
    return 0;
}
