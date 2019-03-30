#ifndef SOCKETDEFINE_H
#define SOCKETDEFINE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

#define PORT             54000
#define MAXCONECTION     SOMAXCONN // SOMAXCONN: Numero maximo de conexões
#define SIZEBUFFER       4096
#define RECEIVING        1
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR   (-1)
#define SUCESS           42
#define ADDR_FAMILY      AF_INET     //Address Family
#define BIND_LC_INTF     INADDR_ANY //Bind local interface
#define NUM_MAX_HOST     NI_MAXHOST //Number max of hosts
#define NUM_MAX_SERV     NI_MAXSERV //Number max of service
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#endif
