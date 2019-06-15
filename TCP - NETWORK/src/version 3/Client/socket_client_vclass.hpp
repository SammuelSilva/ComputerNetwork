#ifndef SOCKETCLIENT_HPP
#define SOCKETCLIENT_HPP

#include "socket_define.hpp"

class C_Socket{
public:
  virtual int create_socket( void )           = 0;
  virtual int initialize_socket( void )       = 0;
  virtual int connect_socket( void )          = 0;
  virtual int send_data( void )              = 0;
  virtual int receive_data( void )            = 0;
};

#endif
