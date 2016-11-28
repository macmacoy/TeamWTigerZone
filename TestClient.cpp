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
    bool quit = false;
    int bufsize = 4096;
    char buffer[bufsize];
    string recieved;
    char* ip = "198.0.1";
    
    Engine* engine = new Engine(0);
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
	string serverPass = "";
	string username = "";
	string userPass = "";

	string startX = "";
	string startY = "";
	string orientation = "";
	bool moreMessages = true;
	bool serverTurn = true;
	bool playerTurn = true;
    

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

    while(!quit)
    {
		//NEED A WAY TO RECIEVE MULTIPLE MESSAGES FROM SERVER
		//currently only is set up for 1 send and 1 recieve at a time
        cout << "Server: ";
        while(serverTurn)
        {
            while(moreMessages){
                if(recv(client, buffer, bufsize, 0) == 0){
                    moreMessages = false;
                    break;
                }
                
                //store recieved buffer to a string
                if(recv(client, buffer, bufsize, 0) > 0)
                {
					recieved = buffer;
				}
				if(recieved.at(recieved.length()-1) == 'n')
				{
					serverTurn = false;
				}
				//split at any possible '/r/n' to separate any individual message
				//then split those at any spaces.
				

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
                    quit = true;
                }
                
                recieved = "";
            }
            

            cout << "Player: ";
            while(playerTurn)
            {
                //send out messages
                *buffer = response[0u];;
                send(client, buffer, bufsize, 0);
                playerTurn = false;
                response = "";
            }

        }
        cout << endl;

    }


    close(client);
    return 0;
}
