#include <iostream>
#include "service_socket.hpp"
int main(int argc, char const *argv[]) {
  Service_Socket *server = new Service_Socket();

  if (server->create_socket() == INVALID_SOCKET){
    cerr << "Impossivel Criar o Socket, erro " << endl;
    exit(EXIT_FAILURE);
  }

  if(server->connect_socket() != 0){
    cerr << "Erro " << " ao conectar a porta no socket"  << endl;
    exit(EXIT_FAILURE);
  }

  if(server->alert_socket() != 0){
    cerr << "Erro  " << " na espera de uma conexão" << endl;
    exit(EXIT_FAILURE);
  }

  if(server->wait_for_conection() == INVALID_SOCKET){
    cerr << "Impossivel Criar o Socket cliente, erro: " << endl;
    exit(EXIT_FAILURE);
  }

  server->generate_name();
  server->close_socket(server->get_socket_listening());
  if(server->data_transference() != SUCESS){
    cerr << "Erro na transferencia de dados " << endl;
    exit(EXIT_FAILURE);
  }
  server->close_socket(server->get_socket_client());

  return 0;
}
