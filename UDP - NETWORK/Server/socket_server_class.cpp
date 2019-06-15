#include "service_socket.hpp"
#include "Casamento.hpp"
#include<mutex>
#include<string>


std::mutex lock_variable;
std::mutex lock_couter;
std::recursive_mutex g_r_lock;
int port_counter = 1;
int clientID = 1;

Service_Socket::Service_Socket( void ){}


bool Service_Socket::run_socket(const int port){
  cout << "STARTING PORT:" << port << endl;
  create_socket(port);

  return listening_socket(port);
}

int Service_Socket::create_socket( const int port ){
  memset((char*) &address, '0', sizeof(address));
  address.sin_family      = ADDR_FAMILY;
  address.sin_port        = htons(port); //convere um u_short para a ordem de Byte do host da rede TCP/IP
  address.sin_addr.s_addr = BIND_LC_INTF; //Conectar a porta em qualquer endereço do socket
  inet_pton(ADDR_FAMILY, "127.0.0.1", &address.sin_addr);

  sockfd = socket(ADDR_FAMILY, SOCK_DGRAM, IPPROTO_UDP); // IPV4, TCP, Protocolo
  bind(sockfd, (struct sockaddr*)&address, sizeof(address));

  return SUCESS;
}

int Service_Socket::listening_socket ( const int port ){

  //listen(sockfd, MAXCONECTION);
  int clientCounter = 0;

  while(LISTENING){
    if(clientCounter == MAXCONECTION / NUM_PORT && port != PORT){
	  std::chrono::milliseconds dura(2000);
	  std::this_thread::sleep_for(dura);
    }

	if (clientCounter == MAXCONECTION && port == PORT) {
		std::chrono::milliseconds dura(2000);
		std::this_thread::sleep_for(dura);
	}

	std::chrono::milliseconds dura(500);
	std::this_thread::sleep_for(dura);
		client_size = sizeof(client);
		clientCounter++;
		//handle_connection(port);
		thread clientThread (&Service_Socket::handle_connection, this, port);
		clientThread.detach();
  
  }

  return SUCESS;
}

int Service_Socket::handle_connection( int port){
  if (port == PORT)
	{
		select_port(get_next_port(port)); //Seleciona uma porta nova sem que seja a base: 54000
	}

  //While loop: aceitar e enviar a mensagem de volta para o cliente
  char buffer[SIZEBUFFER];
  int bytes_rcv;

  //Esperar o cliente enviar dados
  while((bytes_rcv = recvfrom(sockfd, buffer, SIZEBUFFER, 0, (struct sockaddr*) & client, &client_size))){
	  cout << buffer << endl;

	if(bytes_rcv == SOCKET_ERROR)
      return FAILED;
	else{
		if (Boyer_Moore(buffer)) {
			char* temp = "FIND";
			sendto(sockfd, temp, sizeof(temp), 0, (struct sockaddr*) & client, sizeof(client));    //Mensagem de volta para o cliente, com o \0
		}
		else {
			char* temp = "NOT FIND";
			sendto(sockfd, temp, sizeof(temp), 0, (struct sockaddr*) & client, sizeof(client));    //Mensagem de volta para o cliente, com o \0
		}
		cout << "CLIENT DESCONNECTED" << endl;
	 // std::cout << "MESSAGE: " << buffer << endl;
      break;
    }
  }
  return SUCESS;
}

void Service_Socket::select_port(int port)
{
	char buffer[SIZEBUFFER];
	int recvMsgSize;
	int iResult;
	SOCKET clientSock;

	recvMsgSize = recvfrom(sockfd, buffer, SIZEBUFFER, 0, (struct sockaddr*) & client, &client_size);
	if (recvMsgSize < 0){
		std::cerr << "RECEIVED FAILED\n";
	}

	sleep(1);
	std::string portS = std::to_string(port);

	iResult = sendto(sockfd, portS.c_str(), (int)portS.size(), 0, (struct sockaddr*) & client, client_size);

	if(iResult == SOCKET_ERROR) {
		std::cerr << "ERRO SOCKET 2 IN PORT SELECTION \n";
		//close(clientInstance);
	}
	
  cout << "CLIENT " << clientID++ << " CONNECT ON PORT: " << port << " " << buffer <<  endl;
}

int Service_Socket::get_next_port(int port){
  std::lock_guard<std::mutex> lock(lock_variable); //Permite mudar o dado de uma variavel somente em uma thread bloqueando o acesso a seção critica da memoria.
	port += port_counter;
  port_counter++;
	if (port_counter == NUM_PORT)
		port_counter = 1;

	return port;
}

void Service_Socket::close_socket(const SOCKET& socket){ //Fecha o Socket
  close(socket);
}

