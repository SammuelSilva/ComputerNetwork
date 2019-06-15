#include <iostream>
#include <chrono>
#include "client_socket.hpp"

using std::cerr;
using std::cout;

void client_thread( int );

int main(int argc, char const *argv[]) {
  vector<std::thread> clientThreads;

  for(int i = 0; i < NUM_MAX_CLIENT; i++){
	std::chrono::milliseconds duration(100);
	std::this_thread::sleep_for(duration);
    clientThreads.push_back(std::thread(client_thread, PORT));
  }
  
  for (auto& clientThread : clientThreads) {
		clientThread.join();
	}


  return 0;
}

void client_thread(int port){

  Client_Socket *client_socket = new Client_Socket();

  if(client_socket->create_socket() == INVALID_SOCKET){
    cerr << ("ERROR: IMPOSSIBLE TO CREATE A SOCKET") << endl;
    exit(EXIT_FAILURE);
  }

  int check = client_socket->initialize_socket( port );

  if( check == SRC_INV_ADDR ){
    cerr << ("ERROR: INVALID SRC ADDRESS\n");
    exit(EXIT_FAILURE);
  }else if( check == AF_INV_ADDR ){
    cerr << ("ERROR: INVALID AF ADDRESS\n");
    exit(EXIT_FAILURE);
  }

  std::chrono::milliseconds duration(700);
  std::this_thread::sleep_for(duration);
  int send_counter = 0;
  while((send_counter < ATTEMPTS) && (client_socket->send_data() == SEND_ERROR))
    send_counter++;

  if(send_counter == ATTEMPTS){
    cerr << ("ERROR: FAILED TO SEND\n");
	client_socket->close_socket();
    exit(EXIT_FAILURE);
  }

  int read_counter = 0;
  while((read_counter < ATTEMPTS) && ( client_socket->receive_data() == READ_ERROR ))
    read_counter++;

  if (read_counter != ATTEMPTS) {
	  int verification = client_socket->check_data();
	  if (verification != SUCESS) {
		  client_thread(verification);
	  }

  }
}
