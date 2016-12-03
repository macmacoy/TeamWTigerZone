#define _CRT_SECURE_NO_WARNINGS

/*

	Server is not getting the right message
	I am pretty sure the client is connected to the server.
	Wrong message is recieved
	Maybe never recieved this is sparta?

*/

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include "Engine.h"
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512          
//#define IP_ADDRESS "10.136.73.30"
//#define IP_ADDRESS "10.136.15.178"
#define IP_ADDRESS "192.168.0.8"
#define DEFAULT_PORT "4444"

struct client_type
{
	SOCKET socket;
	int id;
	char received_message[DEFAULT_BUFLEN];
};

int process_client(client_type &new_client);
int main();

int process_client(client_type &new_client)
{

	while (1)
	{
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);

		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);

			if (iResult != SOCKET_ERROR)
				//cout << new_client.received_message << endl;
			{
			}
			else
			{
				cout << "recv() failed: " << WSAGetLastError() << endl;
				break;
			}
		}
	}

	if (WSAGetLastError() == WSAECONNRESET)
		cout << "The server has disconnected" << endl;

	return 0;
}

int main()
{



	WSAData wsa_data;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	string sent_message = "";
	client_type client = { INVALID_SOCKET, -1, "" };
	int iResult = 0;
	string message;

	//GameVariables
	string serverPass = "TIGERZONE";
	string username = "TEAMW";
	string userPass = "IAMW";
	//char* ip = "10.136.73.30";
	;//"10.136.67.123";
#ifdef SELF_INPUT
	string ip_address;
	cout << "IP address" << endl;
	cin >> ip_address;
	//char *ip = "";
	const char *ip = ip_address.c_str();
	cout << "Port Number:" << endl;
	int portNum = 4444;
	cin >>portNum;
#endif
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
	//
#ifdef SELF_INPUT
	cout << "User name:" << endl;
	cin >> username;
	cout << "User password:" << endl;
	cin >> userPass;
	cout << "Server password" << endl;
	cin >> serverPass;
#endif

	cout << "Starting Client\n";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0) {
		cout << "WSAStartup() failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "Connecting\n";

	// Resolve the server address and port
	iResult = getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo() failed with error: " << iResult << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		client.socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (client.socket == INVALID_SOCKET) {
			cout << "socket() failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			system("pause");
			return 1;
		}

		// Connect to server.
		iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(client.socket);
			client.socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (client.socket == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	cout << "Successfully Connected" << endl;

	//Obtain id from server for this client;
	//recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);


	//message = client.received_message;

	//return 0; 
	//cout << endl<<"message returned" << endl;


		while (1) {
			
			recieved = "";
			
			recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
			//testmessage = buffer;
			cout << "\n Server: " << client.received_message << " " << endl;

			// cout << buffer << " ";
			
			recieved = client.received_message;
			//recieved.append(" ");
			//cout << "recieve = " << recieved << endl;
			
			//cout << recieved << " recieved" << endl;
			//if checks for each possible incoming message
			if (recieved.compare(0, 4, "MAKE") == 0)
			{
				//recieved = "";
				//make move with given game id
				size_t pos = 0;
				std::string delimiter = " ";
				std::vector<string> v;
				while ((pos = recieved.find(delimiter)) != std::string::npos) {
					v.push_back(recieved.substr(0, pos));
					recieved.erase(0, pos + delimiter.length());
				}
				v.push_back(recieved);
				if (move == 1) {
					game1 = v[5];
				}
				// if(move == 2)
				// 	game2 = v[5];
				tile = v[12];
				std::vector<string> r;
				if (v[5].compare(game1) == 0) {
					r = engine->DoTurn(1);
					if (r[0].compare("UNPLACEABLE PASS") == 0) {
						response.append("GAME ");
						response.append(game1);
						response.append(" MOVE ");
						response.append(std::to_string(move));
						response.append(" PLACE ");
						response.append(tile);
						response.append(" UNPLACEABLE PASS");
					}
					else {
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
						if (r[3].compare("TIGER") == 0) {
							response.append(" ");
							response.append(r[4]);
						}
						response.append("\r\n");
					}
				}
				else if (v[5].compare(game2) == 0) {
					r = engine->DoTurn(2);
					std::cout << "HERE!!!!!!\n";
					if (r[0].compare("UNPLACEABLE PASS") == 0) {
						response.append("GAME ");
						response.append(game2);
						response.append(" MOVE ");
						response.append(std::to_string(move));
						response.append(" PLACE ");
						response.append(tile);
						response.append(" UNPLACEABLE PASS");
					}
					else {
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
						if (r[3].compare("TIGER") == 0) {
							response.append(" ");
							response.append(r[4]);
						}
						response.append("\r\n");
					}
				}
				move++;

				strcpy(buffer, response.c_str());
				send(client.socket, buffer, bufsize, 0);

			}
			else if (recieved.compare(0, 4, "GAME") == 0)
			{
				recieved = "";
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
				if (move == 2)
					game2 = v[1];
				// 	game1 = v[1];
				// if(move == 1)
				// 	game2 = v[1];
				std::vector<string> m;
				m.push_back(v[9]);
				m.push_back(v[10]);
				m.push_back(v[11]);
				if (v[12].compare("TIGER") == 0) {
					m.push_back(v[13]);
				}
				else if (v[12].compare("CROCODILE") == 0) {
					m.push_back("-1");
				}
				else {
					m.push_back("0");
				}
				if (username.compare(v[5]) != 0) {
					if (v[1].compare(game1) == 0) {
						engine->OpponentTurn(m, 1);
					}
					if (v[1].compare(game2) == 0) {
						engine->OpponentTurn(m, 2);
					}
				}
			}
			else if (recieved.compare(0, 4, "THIS") == 0)
			{
				recieved = "";
				memset(client.received_message, 0, DEFAULT_BUFLEN);
				//do join message
				response.append("JOIN ");
				response.append(serverPass);
				response.append("\r\n");

			//	response = "JOIN TIGERZONE \r\n";



				//cout << response << endl;
				//cout << "TIGERZONE1234 SENT" << endl;

				strcpy(buffer, response.c_str());
				char b2[1024] = {};
				strcpy(b2, response.c_str());
				//cout << response << " Response sent" << endl;
				send(client.socket, b2, bufsize, 0);
				//wrong message is sent to server
			}
			else if (recieved.compare(0, 4, "HELL") == 0)
			{
				//recieved = "";
				response = "I AM "+username + " " + userPass + "\r\n";

				strcpy(buffer, response.c_str());
				send(client.socket, buffer, bufsize, 0);

			}
			else if (recieved.compare(0, 4, "WELC") == 0)
			{
				//recieved = "";
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
			else if (recieved.compare(0, 4, "NEW ") == 0)
			{
				recieved = "";
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
			else if (recieved.compare(0, 4, "BEGI") == 0)
			{
				//recieved = "";
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
			else if (recieved.compare(0, 4, "YOUR") == 0)
			{
				//recieved = "";
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
			else if (recieved.compare(0, 4, "STAR") == 0)
			{
				//recieved = "";
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
			else if (recieved.compare(0, 4, "THE ") == 0)
			{
				//recieved = "";
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
			else if (recieved.compare(0, 4, "MATC") == 0)
			{
				recieved = "";
				//need to do anything with countdown for match?
				//don't think so

			}
			else if (recieved.compare(0, 4, "END") == 0)
			{
				recieved = "";
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
			}
			else if (recieved.compare(0, 4, "PLEA") == 0)
			{
				recieved = "";
				//do anything while waiting for next challenge to begin?
			}

			if (testmessage.compare(0, 4, "THAN") == 0) {
				send(client.socket, buffer, bufsize, 0);
				testmessage = "MAKE";
				quit = true;
				serverturn = false;
			}

			// clear response string
			response = "";
			recieved = "";
		}



		cout << endl;
		//}

		//Shutdown the connection since no more data will be sent
		//my_thread.detach();

	cout << "Shutting down socket..." << endl;
	iResult = shutdown(client.socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown() failed with error: " << WSAGetLastError() << endl;
		closesocket(client.socket);
		WSACleanup();
		//system("pause");
		return 1;
	}

	closesocket(client.socket);
	WSACleanup();
	system("pause");
	return 0;
}
