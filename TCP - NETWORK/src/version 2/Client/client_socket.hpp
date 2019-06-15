#ifndef CLIENTSCK_HPP
#define CLIENTSCK_HPP

#include "socket_client_vclass.hpp"

class Client_Socket : public C_Socket{
private:
  socklen_t client_size;
  struct sockaddr_in server_address, server_client;
  int listening;
  char* message;
  char buffer[1024] = {'0'};
public:
  Client_Socket( void );
  virtual ~Client_Socket(){};
  virtual int create_socket( void );
  virtual int initialize_socket( void );
  virtual int connect_socket( void );
  virtual void send_data( void );
  virtual int receive_data( void );

};

#endif
