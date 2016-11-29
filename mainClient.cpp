#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include "Engine.cpp"

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
	string recieved = "";
	bool playerturn = false;
	bool serverturn = true;
	
	

    struct sockaddr_in server_addr;

	//create socket
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket client has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

	
	//connect to server
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;


    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";

    cout << "\n\n=> Enter # to end the connection\n" << endl;

    do {
		cout << "Server: ";
        while(serverturn){
            recv(client, buffer, bufsize, 0);
            testmessage = buffer;
            cout << "\n Server: " + testmessage << endl;
            cout << buffer << " ";
			
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
				if(move == 1){
					game1 = v[5];
				}
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
				if(move == 2)
					game1 = v[1];
				if(move == 1)
					game2 = v[1];
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
				//do join message
				response.append("JOIN");
				response.append(serverPass);
				response.append("\r\n");

	
				strcpy(buffer, response.c_str());
				send(client, buffer, bufsize, 0);

			}
			else if(recieved.compare(0, 4, "HELL") == 0)
			{
				std::cout << "here2\n";
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
				round_ = v[5];
			}
			else if(recieved.compare(0, 4, "PLEA") == 0)
			{
				//do anything while waiting for next challenge to begin?
			}
			
			if (testmessage.compare(0,4,"THAN") == 0) {
                    send(client, buffer, bufsize, 0);
                    testmessage = "MAKE";
                    isExit = true;
                    serverturn = false;
            }

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

    } while (!isExit);


    cout << "\n=> Connection terminated.\nGoodbye...\n";

    close(client);
    return 0;
}
