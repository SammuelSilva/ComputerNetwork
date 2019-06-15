#include <iostream>
#include "client_socket.hpp"
using std::cerr;
using std::cout;

int main(int argc, char const *argv[]) {
  Client_Socket *client_socket = new Client_Socket();

  if(client_socket->create_socket() == INVALID_SOCKET){
    cerr << "Impossivel Criar o Socket, erro: " << endl;
    exit(EXIT_FAILURE);
  }
  client_socket->initialize_socket();
  cerr << ("ERRO 1");
  client_socket->connect_socket();
  cerr << ("ERRO 2");
  client_socket->send_data();
  cerr << ("ERRO 3");
  cout <<"\n"<< client_socket->receive_data() << std::endl;
  cerr << ("ERRO 4");

  return 0;
}
