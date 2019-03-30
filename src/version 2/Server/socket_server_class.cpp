#include "service_socket.hpp"

Service_Socket::Service_Socket( void ){
  create_socket();
}

int Service_Socket::create_socket( void ){
  this->listening = socket(ADDR_FAMILY, SOCK_STREAM, IPPROTO_TCP); // IPV4, TCP, Protocolo
  return this->listening;
}

int Service_Socket::connect_socket( void ){
  memset((char*) &this->address, '0', sizeof(this->address));
  this->address.sin_family      = ADDR_FAMILY;
  this->address.sin_port        = htons(PORT); //convere um u_short para a ordem de Byte do host da rede TCP/IP
  this->address.sin_addr.s_addr = BIND_LC_INTF; //Conectar a porta em qualquer endereço do socket

  return bind(this->listening, (struct sockaddr*)&this->address, sizeof(this->address));
}

int Service_Socket::alert_socket ( void ){
  return listen(this->listening, MAXCONECTION);
}

int Service_Socket::wait_for_conection(void){
  this->client_size = sizeof(this->client);
  this->client_socket = accept(this->listening, (struct sockaddr*)&this->client, &this->client_size);
  return this->client_socket;
}

void Service_Socket::generate_name( void ){
  //Seta os primeiros numeros de bytes de um ponteiro de um bloco de memoria para um valor especifico (Unsigned char), neste caso esta setando 0 NI_MAXHOST
  memset(this->host, '0', NUM_MAX_HOST);
  memset(this->service, '0', NUM_MAX_SERV);

  //Verifica se consegue o nome do host que esta conectado se nao der, usamos o ip_address

  if(getnameinfo((sockaddr*)&this->client, sizeof(this->client), this->host, NUM_MAX_HOST, this->service, NUM_MAX_SERV, 0) == 0){
    cout << this->host << " conectado na porta: " << this->service << endl; // possivel nome
  }else{
    inet_ntop(ADDR_FAMILY,&this->client.sin_addr, this->host, NUM_MAX_HOST); //Gera o endereco IP da porta
    cout << this->host << "conectado na porta " << ntohs(this->client.sin_port) << endl;
  }
}

int Service_Socket::data_transference( void ){
  //While loop: aceitar e enviar a mensagem de volta para o cliente
  char buffer[SIZEBUFFER];

  //Esperar o cliente enviar dados
  while(RECEIVING){
    int bytes_rcv = recv(client_socket, buffer, SIZEBUFFER, 0);
    if(bytes_rcv == SOCKET_ERROR)
      return EXIT_FAILURE;
    if(bytes_rcv == 0){
      cout << "Cliente desconectado" << endl;
      break;
    }
    std::cout << "Message: " << buffer << endl;
    send(this->client_socket, buffer, bytes_rcv+1, 0);    //Mensagem de volta para o cliente, com o \0
  }
  return SUCESS;
}

int Service_Socket::get_socket_listening( void ){
  return this->listening;
}

int Service_Socket::get_socket_client( void ){
  return this->client_socket;
}

void Service_Socket::close_socket(const int& socket){
  close(socket);
}
