#ifndef SERVICESCK_HPP
#define SERVICESCK_HPP

#include "socket_server_vclass.hpp"

class Service_Socket : public S_Socket{
private:
  socklen_t client_size;
  struct sockaddr_in address, client;
  int listening, client_socket;
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];
public:
  Service_Socket( void );
  virtual ~Service_Socket(){};
  virtual int create_socket( void );
  virtual int connect_socket( void );
  virtual int alert_socket ( void );
  virtual int wait_for_conection( void );
  virtual void generate_name( void );
  virtual int data_transference( void );
  virtual void close_socket( const int& );
  virtual int get_socket_listening( void );
  virtual int get_socket_client( void );
};

#endif
