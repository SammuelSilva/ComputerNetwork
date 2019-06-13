#include <iostream>
#include "service_socket.hpp"

bool run_socket(int port);

int main(int argc, char const *argv[]) {
  vector<thread> portThreads;

	for (int i = 0; i <= NUM_PORT; i++)
	{
		portThreads.push_back(std::thread(run_socket, PORT + i));//create one thread per one port
  }

  int cont = 0;
	for (auto& portThread : portThreads) {
    if(portThread.joinable())
		  portThread.join();

    cont++;
	}

  return 0;
}

bool run_socket(int port){
    Service_Socket *server = new Service_Socket();
    return server->run_socket(port);
}
