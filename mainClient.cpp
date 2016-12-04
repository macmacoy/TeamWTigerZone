#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <string.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <netdb.h>
#include <vector>
#include "Engine.h"

#include <winsock2.h>
#include <Windows.h>
//#include <network>
#include <ws2tcpip.h>
#include <stdio.h>



using namespace std;

int main123()
{
	// fill in at tounament
	string serverPass = "TIGERZONE!";
	string username = "TEAMW";
	string userPass = "IAMW";
	// char* ip = "127.0.0.3";
	char* ip = "192.168.1.19";
	// char* ip = "10.136.67.123";
	// char* ip = "10.136.28.60";
    
    int client;
    // int portNum = 1500;
    int portNum = 4444;
    bool quit = false;
    int bufsize = 1024;
	char buffer[1024] = {};
    
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

	string startX = "";
	string startY = "";
	string orientation = "";
	
	string testmessage = "";
	string recieved = "";
	bool playerturn = false;
	bool serverturn = true;

    struct sockaddr_in server_addr;

	//create socket
    client = socket(AF_INET, SOCK_STREAM, 0);
	/*
    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }*/

    cout << "\n=> Socket client has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server " << inet_ntoa(server_addr.sin_addr) << " with port number: " << portNum << endl;

	// //connect to server
 //    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
 //        cout << "=> Connection to the server port number: " << portNum << endl;


    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";

    cout << "\n\n=> Enter # to end the connection\n" << endl;

    string last = "";
    do {
		// cout << "Server: ";
        while(serverturn){
            recv(client, buffer, bufsize, MSG_WAITALL);
            testmessage = buffer;
            cout << "\n Server: " + testmessage << endl;
            // cout << buffer << " ";
			
			recieved = testmessage;
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
				v.push_back(recieved);
				if(move == 1){
					game1 = v[5];
				}
				// if(move == 2)
				// 	game2 = v[5];
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
						response.append(r[0]);
						response.append(" ");
						response.append(r[1]);
						response.append(" ");
						response.append(r[2]);
						response.append(" ");
						response.append(r[3]);
						if(r[3].compare("TIGER") == 0){
							response.append(" ");
							response.append(r[4]);
						}
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
						response.append(r[0]);
						response.append(" ");
						response.append(r[1]);
						response.append(" ");
						response.append(r[2]);
						response.append(" ");
						response.append(r[3]);
						if(r[3].compare("TIGER") == 0){
							response.append(" ");
							response.append(r[4]);
						}
						response.append("\r\n");
					}
				}
				move++;
				
				strcpy(buffer, response.c_str());
				send(client, buffer, bufsize, 0);
				
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
				v.push_back(recieved);
				if(move == 2)
					game2 = v[1];
				// 	game1 = v[1];
				// if(move == 1)
				// 	game2 = v[1];
				std::vector<string> m;
				m.push_back(v[9]);
				m.push_back(v[10]);
				m.push_back(v[11]);
				if(v[12].compare("TIGER") == 0){
					m.push_back(v[13]);
				}
				else if(v[12].compare("CROCODILE") == 0){
					m.push_back("-1");
				}
				else{
					m.push_back("0");
				}
				if(username.compare(v[5]) != 0){
					if(v[1].compare(game1) == 0){
						engine->OpponentTurn(m, 1);
					}
					if(v[1].compare(game2) == 0){
						engine->OpponentTurn(m, 2);
					}
				}
			}
			else if(recieved.compare(0, 4, "THIS") == 0)
			{
				std::cout << "IN THIS\n";
				//do join message
				response.append("JOIN ");
				response.append(serverPass);
				response.append("\r\n");

				
				strcpy(buffer, response.c_str());
				send(client, buffer, bufsize, 0);

			}
			else if(recieved.compare(0, 4, "HELL") == 0)
			{
				response = "I AM " + username + " " + userPass + "\r\n";

				strcpy(buffer, response.c_str());
				send(client, buffer, bufsize, 0);

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
				v.push_back(recieved);
				username = v[1];
				
			}
			else if(recieved.compare(0, 4, "NEW ") == 0)
			{
				//store challenge id?
				// size_t pos = 0;
				// std::string delimiter = " ";
				// std::vector<string> v;
				// while ((pos = recieved.find(delimiter)) != std::string::npos) {
				// 	v.push_back(recieved.substr(0, pos));
				// 	recieved.erase(0, pos + delimiter.length());
				// }
				// v[2] = challengeID;
				// v[6] = round;
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
				v.push_back(recieved);
				roundID = v[2];
				round_ = v[4];

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
				v.push_back(recieved);

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
				v.push_back(recieved);
				tile = v[3];
				startX = v[5];
				startY = v[6];
				orientation = v[7];
				
			}
			else if(recieved.compare(0, 4, "THE ") == 0)
			{
				if(move == 1){
					//store remaining tiles IN ORDER as decks for each game
					size_t pos = 0;
					std::string delimiter = "[ ";
					std::vector<string> v;
					while ((pos = recieved.find(delimiter)) != std::string::npos) {
						v.push_back(recieved.substr(0, pos));
						recieved.erase(0, pos + delimiter.length());
					}
					v.push_back(recieved);
					string tiles = v[1];

					engine = new Engine(tiles);
				}
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
				v.push_back(recieved);
				roundID = v[3];
				round_ = v[5];

				// set move equal to 1 to start new game
				move = 1;
			}
			else if(recieved.compare(0, 4, "PLEA") == 0)
			{
				//do anything while waiting for next challenge to begin?
			}
			
			if (testmessage.compare(0,4,"THAN") == 0) {
                    send(client, buffer, bufsize, 0);
                    testmessage = "MAKE";
                    quit = true;
                    serverturn = false;
            }

            // clear response string
            response = "";

            // for(int i=0; i<1024; i++)
            // 	buffer[i] = '\0';

        }
        
        /*cout << "Client: ";
        while(playerturn){
            cin.getline(buffer, bufsize);
            testmessage = buffer;
            //cout << "\n Test: " + testmessage << endl;
            send(client, buffer, bufsize, 0);

            playerturn = false;
            serverturn = true;
        }*/

        cout << endl;

    } while (!quit);


    cout << "\n=> Connection terminated.\nGoodbye...\n";

    closesocket(client);
    return 0;
}
