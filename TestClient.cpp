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
    int client;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 4096;
    char buffer[bufsize];
    string recieved;
    char* ip = "198.0.1";

    struct sockaddr_in server_addr;

	//create socket
    client = socket(AF_INET, SOCK_STREAM, 0);

	//make sure socket was created
    if (client < 0) 
    {
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

	//connect to server
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)

    //recv(client, buffer, bufsize, 0);

	//begin communicating

    Engine* engine = NULL;
    string game1 = "";
    string game2 = "";
    int move = 1;
    string tile = "";
    string response = "";
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
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        v.push_back(s.substr(0, pos));
                        s.erase(0, pos + delimiter.length());
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
                    size_t pos = 0;
                    std::string delimiter = "[";
                    std::vector<string> v;
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        v.push_back(s.substr(0, pos));
                        s.erase(0, pos + delimiter.length());
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


    close(client);
    return 0;
}
