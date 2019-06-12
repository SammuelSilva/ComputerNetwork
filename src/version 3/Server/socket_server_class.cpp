#include "service_socket.hpp"

Service_Socket::Service_Socket( void ){}

int Service_Socket::create_socket( const int port ){
  this->listening = socket(ADDR_FAMILY, SOCK_STREAM, IPPROTO_TCP); // IPV4, TCP, Protocolo

  memset((char*) &this->address, '0', sizeof(this->address));
  this->address.sin_family      = ADDR_FAMILY;
  this->address.sin_port        = htons(port); //convere um u_short para a ordem de Byte do host da rede TCP/IP
  this->address.sin_addr.s_addr = BIND_LC_INTF; //Conectar a porta em qualquer endereço do socket

  bind(this->listening, (struct sockaddr*)&this->address, sizeof(this->address));

  return SUCESS;
}

bool Service_Socket::run_socket(const int port){

  this->create_socket(port);

  return this->listening_socket(port);
}

int Service_Socket::listening_socket ( const int port ){

  listen(this->listening, MAXCONECTION);

  int clientCounter = 0;
  struct sockaddr_in clientAddress;
  socklen_t clientSize = sizeof(clientAddress);
  SOCKET clientSocket = INVALID_SOCKET;

  while(LISTENING){
    if(clientCounter == NUM_PORT && port == PORT){
      std::cerr << "BREAKING" << '\n';
      break;
    }

    clientSocket = accept(this->listening, (struct sockaddr*)&clientAddress, &clientSize);
    if(clientSocket != INVALID_SOCKET){
      thread clientThread (&Service_Socket::handle_connection, this, clientSocket);
      clientThread.detach();
    }
  }
  close_socket(clientSocket);
  return SUCESS;
}

int Service_Socket::handle_connection( const int clientSocket ){
  //While loop: aceitar e enviar a mensagem de volta para o cliente
  char buffer[SIZEBUFFER];
  //authenticate(clientSocket);
  //Esperar o cliente enviar dados
  while(RECEIVING){
    int bytes_rcv = recv(clientSocket, buffer, SIZEBUFFER, 0);
    if(bytes_rcv == SOCKET_ERROR)
      return FAILED;
    if(bytes_rcv == 0){
      cout << "Cliente desconectado" << endl;
      std::cout << "\nWAITING FOR CONNECTION. . .\n";
      break;
    }
    std::cout << "Message: " << buffer << bytes_rcv << endl;
    send(clientSocket, "Chegou", bytes_rcv+1, 0);    //Mensagem de volta para o cliente, com o \0
  }
  return SUCESS;
}

void Service_Socket::close_socket(const int& socket){
  close(socket);
}

//
// void Service_Socket::generate_name( void ){
//   //Seta os primeiros numeros de bytes de um ponteiro de um bloco de memoria para um valor especifico (Unsigned char), neste caso esta setando 0 NI_MAXHOST
//   memset(this->host, '0', NUM_MAX_HOST);
//   memset(this->service, '0', NUM_MAX_SERV);
//
//   //Verifica se consegue o nome do host que esta conectado se nao der, usamos o ip_address
//
//   if(getnameinfo((sockaddr*)&this->client, sizeof(this->client), this->host, NUM_MAX_HOST, this->service, NUM_MAX_SERV, 0) == 0){
//     cout << this->host << " conectado na porta: " << this->service << endl; // possivel nome
//   }else{
//     inet_ntop(ADDR_FAMILY,&this->client.sin_addr, this->host, NUM_MAX_HOST); //Gera o endereco IP da porta
//     cout << this->host << "conectado na porta " << ntohs(this->client.sin_port) << endl;
//   }
// }
