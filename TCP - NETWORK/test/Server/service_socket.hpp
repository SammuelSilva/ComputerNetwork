#ifndef SERVICESCK_HPP
#define SERVICESCK_HPP

#include "socket_server_vclass.hpp"

class Service_Socket : public S_Socket{
private:
  struct sockaddr_in address;
  SOCKET listening;
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];
  
  virtual int handle_connection( const int );

public:
  Service_Socket( void );
  virtual ~Service_Socket(){};
  virtual int create_socket( const int );
  virtual bool run_socket(const int);
  virtual int listening_socket ( const int );
//  virtual void generate_name( void );
  virtual void close_socket( const int& );
};

#endif
