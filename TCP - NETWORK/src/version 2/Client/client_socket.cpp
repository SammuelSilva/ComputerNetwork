#include "client_socket.hpp"

Client_Socket::Client_Socket( void ){
  create_socket();
}

int Client_Socket::create_socket( void ){
  this->listening = socket(ADDR_FAMILY, SOCK_STREAM, IPPROTO_TCP); // IPV4, TCP, Protocolo
  return this->listening;
}

int Client_Socket::initialize_socket( void ){
  memset((char*) &this->server_address, '0', sizeof(this->server_address));
  this->server_address.sin_family      = ADDR_FAMILY;
  this->server_address.sin_port        = htons(PORT); //convere um u_short para a ordem de Byte do host da rede TCP/IP

  return inet_pton(ADDR_FAMILY, "127.0.0.1", &this->server_address.sin_addr);
}

int Client_Socket::connect_socket( void ){
  return connect(this->listening, (struct sockaddr *)&this->server_address, sizeof(this->server_address));
}

void Client_Socket::send_data( void ){
  this->message = "msg test";
  send(this->listening , "msg tst" , strlen(this->message) , 0 );
}

int Client_Socket::receive_data( void ){
  return read(this->listening , this->buffer, 1024);
}
