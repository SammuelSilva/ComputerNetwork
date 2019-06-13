#include <iostream>
#include "client_socket.hpp"
using std::cerr;
using std::cout;

void client_thread();

int main(int argc, char const *argv[]) {
  vector<std::thread> clientThreads;

  for(int i = 0; i < NUM_MAX_CLIENT; i++){
    cout << "PORT CLIENT: " << port_client << " CLIENT " << i << "\n";
    clientThreads.push_back(std::thread(client_thread));
    port_client++;
  }

  for (auto& clientThread : clientThreads) {
		clientThread.join();
	}

  return 0;
}

void client_thread(){

  Client_Socket *client_socket = new Client_Socket();

  if(client_socket->create_socket() == INVALID_SOCKET){
    cerr << ("ERROR: IMPOSSIBLE TO CREATE A SOCKET") << endl;
    exit(EXIT_FAILURE);
  }

  int check = client_socket->initialize_socket();

  if( check == SRC_INV_ADDR ){
    cerr << ("ERROR: INVALID SRC ADDRESS\n");
    exit(EXIT_FAILURE);
  }else if( check == AF_INV_ADDR ){
    cerr << ("ERROR: INVALID AF ADDRESS\n");
    exit(EXIT_FAILURE);
  }

  check = client_socket->connect_socket();

  if( check == CONNECTION_FAILED ){
    cerr << ("ERROR: FAILED TO CONNECT\n");
    exit(EXIT_FAILURE);
  }

  int send_counter = 0;
  while((send_counter < ATTEMPTS) && (client_socket->send_data() == SEND_ERROR))
    send_counter++;

  if(send_counter == ATTEMPTS){
    cerr << ("ERROR: FAILED TO SEND\n");
    exit(EXIT_FAILURE);
  }

  int read_counter = 0;

  while((read_counter < ATTEMPTS) && ( client_socket->receive_data() == READ_ERROR ))
    read_counter++;
}
