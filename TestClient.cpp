#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <vector>
#include "Engine.h"


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

    Engine* engine = NULL;
    string game1 = "";
    string game2 = "";
    int move = 1;
    string tile = "";
    string response = "";
	string playerID = "";
	string opponentID = "";
	string challengeID = "";
	string round = "";
	string roundID = "";

	string startX = "";
	string startY = "";
	string orientation = "";

    bool moreMessages = true;

    while(!isExit)
    {
		//NEED A WAY TO RECIEVE MULTIPLE MESSAGES FROM SERVER
		//currently only is set up for 1 send and 1 recieve at a time
        cout << "Server: ";
        while(*buffer != '\n' && *buffer != '\r')
        {
            while(moreMessages){
                if(recv(client, buffer, bufsize, 0) == 0){
                    moreMessages = false;
                    break;
                }
                //append message to string
                recieved.append(buffer[0], buffer[bufsize]);

                //if checks for each possible incoming message
                if(recieved.compare(0, 4, "MAKE") == 0)
                {
    				//make move with given game id
                    size_t pos = 0;
                    std::string delimiter = " ";
                    std::vector<string> v;
                    while ((pos = recieved.find(delimiter)) != std::string::npos) {
                        v.push_back(recieved.substr(0, pos));
                        recieved.erase(0, pos + delimiter.length());
                    }
                    if(move == 1)
                        game1 = v[5];
                    if(move == 2)
                        game2 = v[5];
                    tile = v[12];
                    std::vector<string> r;
                    if(v[5].compare(game1) == 0){
                        r = engine->DoTurn(1);
                        if(r[0].compare("UNPLACEABLE PASS") == 0){
                            response.append("GAME ");
                            response.append(game1);
                            response.append(" MOVE ");
                            response.append(std::to_string(move));
                            response.append(" PLACE ");
                            response.append(tile);
                            response.append(" UNPLACEABLE PASS");
                        }
                        else{
                            response.append("GAME ");
                            response.append(game1);
                            response.append(" MOVE ");
                            response.append(std::to_string(move));
                            response.append(" PLACE ");
                            response.append(tile);
                            response.append(" AT ");
                            response.append(v[0]);
                            response.append(" ");
                            response.append(v[1]);
                            response.append(" ");
                            response.append(v[2]);
                            response.append(" ");
                            response.append(v[3]);
                            if(v[3].compare("TIGER"))
                                response.append(v[4]);
                            response.append("\r\n");
                        }
                    }
                    else if(v[5].compare(game2) == 0){
                        r = engine->DoTurn(2);
                        if(r[0].compare("UNPLACEABLE PASS") == 0){
                            response.append("GAME ");
                            response.append(game2);
                            response.append(" MOVE ");
                            response.append(std::to_string(move));
                            response.append(" PLACE ");
                            response.append(tile);
                            response.append(" UNPLACEABLE PASS");
                        }
                        else{
                            response.append("GAME ");
                            response.append(game2);
                            response.append(" MOVE ");
                            response.append(std::to_string(move));
                            response.append(" PLACE ");
                            response.append(tile);
                            response.append(" AT ");
                            response.append(v[0]);
                            response.append(" ");
                            response.append(v[1]);
                            response.append(" ");
                            response.append(v[2]);
                            response.append(" ");
                            response.append(v[3]);
                            if(v[3].compare("TIGER"))
                                response.append(v[4]);
                            response.append("\r\n");
                        }
                    }
                    move++;
    			}
    			else if(recieved.compare(0, 4, "GAME") == 0)
                {
    				//Check for every game statement from opponent and change
    				// our board accordingly
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}
					game1 = v[1];
					game2 = v[1];
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
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}
					playerID = v[1];
					
    			}
    			else if(recieved.compare(0, 4, "NEW ") == 0)
                {
    				//store challenge id?
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}
					v[2] = challengeID;
					v[6] = round;
    			}
    			else if(recieved.compare(0, 4, "BEGI") == 0)
                {
    				//store round id?
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}

					roundID = v[2];
					round = v[4];

    			}
    			else if(recieved.compare(0, 4, "YOUR") == 0)
                {
    				//store opponent id?
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}

					opponentID = v[4];
    			}
    			else if(recieved.compare(0, 4, "STAR") == 0)
                {
    				//create two engines, place starting tile in each
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}
					tile = v[3];
					startX = v[5];
					startY = v[6];
					orientation = v[7];
					
    			}
    			else if(recieved.compare(0, 4, "THE ") == 0)
                {
    				//store remaining tiles IN ORDER as decks for each game
                    size_t pos = 0;
                    std::string delimiter = "[";
                    std::vector<string> v;
                    while ((pos = recieved.find(delimiter)) != std::string::npos) {
                        v.push_back(recieved.substr(0, pos));
                        recieved.erase(0, pos + delimiter.length());
                    }
                    string tiles = v[1];

                    engine = new Engine(tiles);
    			}
    			else if(recieved.compare(0, 4, "MATC") == 0)
                {
    				//need to do anything with countdown for match?
                    //don't think so

    			}
    			else if(recieved.compare(0, 4, "END") == 0)
                {
    				//check if end of round or challenge
					size_t pos = 0;
					std::string delimiter = " ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}

					roundID = v[3];
					round = v[5];
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
            }
            
            
            
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '\n';
                isExit = true;
            }

            cout << "Player: ";
            while(*buffer != '\n' && *buffer != '\r')
            {
                //send out messages
                cin >> buffer;
                send(client, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(client, buffer, bufsize, 0);
                    *buffer = '\n';
                    isExit = true;
                }
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
