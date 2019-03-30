#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP

#include "socket_define.hpp"

class S_Socket{
public:
  virtual int create_socket( void )                                         = 0;
  virtual int connect_socket( void )                                        = 0;
  virtual int alert_socket ( void )                                         = 0;
  virtual int wait_for_conection( void )                                    = 0;
  virtual void generate_name( void )                                        = 0;
  virtual int data_transference( void )                                     = 0;
  virtual void close_socket( const int& )                                   = 0;
  virtual int get_socket_listening( void )                                  = 0;
  virtual int get_socket_client( void )                                     = 0;

};

#endif
