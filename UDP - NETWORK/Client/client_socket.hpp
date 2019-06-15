#ifndef CLIENTSCK_HPP
#define CLIENTSCK_HPP

#include "socket_client_vclass.hpp"

static int counter_message_received = 0;

class Client_Socket : public C_Socket{
private:
  socklen_t client_size, server_size;
  struct sockaddr_in server_address, server_client;
  int sockfd;
  char* message;
  char buffer[SIZEBUFFER] = {'0'};
public:
  Client_Socket( void );
  virtual ~Client_Socket(){};
  virtual int create_socket( void );
  virtual int initialize_socket( int );
  virtual int send_data( void );
  virtual int receive_data( void );
  virtual int check_data(void);
  virtual void close_socket(void);
  virtual void client_shutdown(void);
};

#endif
