/*!
 * Simple chat program (client side).cpp - http://github.com/hassanyf
 * Version - 2.0.1
 *
 * Copyright (c) 2016 Hassan M. Yousuf
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include "Engine.cpp"

using namespace std;

int main()
{


    int client;
    int portNum = 1500; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "127.0.0.3";
    
    Engine* engine = new Engine(0);
    string game1 = "";
    string game2 = "";
    int move = 1;
    string tile = "";
    string response = "";
    string opponentID = "";
	string challengeID = "";
	string round_ = "";
	string roundID = "";
	string serverPass = "";
	string username = "";
	string userPass = "";

	string startX = "";
	string startY = "";
	string orientation = "";
	
	string testmessage = "";
	bool playerturn = false;
	bool serverturn = true;
	
	

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

    do {
        cout << "Server: ";
        while(serverturn){
            recv(client, buffer, bufsize, 0);
            testmessage = buffer;
            //cout << "\n Test: " + testmessage << endl;
            cout << buffer << " ";
            if(testmessage.compare(0,4,"MAKE") == 0)
            {
				serverturn = false;
				playerturn = true;
			}
			if (testmessage.compare(0,4,"THAN") == 0) {
                    send(client, buffer, bufsize, 0);
                    testmessage = "MAKE";
                    isExit = true;
                    serverturn = false;
            }

        }
        
        cout << "Client: ";
        while(playerturn){
            cin.getline(buffer, bufsize);
            testmessage = buffer;
            //cout << "\n Test: " + testmessage << endl;
            send(client, buffer, bufsize, 0);

            playerturn = false;
            serverturn = true;
        }

        cout << endl;

    } while (!isExit);

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
