#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP

#include "socket_define.hpp"

class S_Socket{
public:
  virtual int create_socket( const int )      = 0;
  virtual bool run_socket(const int)          = 0;
  virtual int listening_socket ( const int )  = 0;
//  static int handle_connection( const int )  = 0;
//  virtual void generate_name( void )          = 0;
  virtual void close_socket( const int& )     = 0;

};

#endif
