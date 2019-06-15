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
  this->create_socket(port);

  return this->listening_socket(port);
}

int Service_Socket::create_socket( const int port ){
  memset((char*) &this->address, '0', sizeof(this->address));
  this->address.sin_family      = ADDR_FAMILY;
  this->address.sin_port        = htons(port); //convere um u_short para a ordem de Byte do host da rede TCP/IP
  this->address.sin_addr.s_addr = BIND_LC_INTF; //Conectar a porta em qualquer endereço do socket
  inet_pton(ADDR_FAMILY, "127.0.0.1", &this->address.sin_addr);

  this->listening = socket(ADDR_FAMILY, SOCK_STREAM, IPPROTO_TCP); // IPV4, TCP, Protocolo
  bind(this->listening, (struct sockaddr*)&this->address, sizeof(this->address));

  return SUCESS;
}

int Service_Socket::listening_socket ( const int port ){

  listen(this->listening, MAXCONECTION);

  struct sockaddr_in clientAddress;
  socklen_t clientSize = sizeof(clientAddress);
  SOCKET clientSocket = INVALID_SOCKET;
  int clientCounter = 0;

  while(LISTENING){
    if(clientCounter == MAXCONECTION / NUM_PORT && port != PORT){
      std::cerr << "BREAKING: MAX CAPACITY " << '\n';
	  std::chrono::milliseconds dura(2000);
	  std::this_thread::sleep_for(dura);
    }

	if (clientCounter == MAXCONECTION && port == PORT) {
		std::cerr << "BREAKING: SOMETHING WRONG" << '\n';
		std::chrono::milliseconds dura(2000);
		std::this_thread::sleep_for(dura);
	}

    clientSocket = accept(this->listening, (struct sockaddr*)&clientAddress, &clientSize);
    if(clientSocket != INVALID_SOCKET){
	  cout << "ACEPTED CONECTION FROM CLIENT" << endl << endl;
      clientCounter++;
      thread clientThread (&Service_Socket::handle_connection, this, clientSocket, port);
      clientThread.detach();
    }
  }
  close_socket(clientSocket);

  return SUCESS;
}

int Service_Socket::handle_connection( SOCKET clientSocket, int port){
  if (port == PORT)
	{
		select_port(clientSocket,get_next_port(port)); //Seleciona uma porta nova sem que seja a base: 54000
	}

  //While loop: aceitar e enviar a mensagem de volta para o cliente
  char buffer[SIZEBUFFER];
  //Esperar o cliente enviar dados
  while(RECEIVING){
    int bytes_rcv = recv(clientSocket, buffer, SIZEBUFFER, 0);
    if(bytes_rcv == SOCKET_ERROR)
      return FAILED;
    if(bytes_rcv == 0){
		if (Boyer_Moore(buffer)) {
			char* temp = "FIND";
			send(clientSocket, temp, strlen(temp), 0);    //Mensagem de volta para o cliente, com o \0
		}
		else {
			char* temp = "NOT FIND";
			send(clientSocket, temp, strlen(temp), 0);    //Mensagem de volta para o cliente, com o \0
		}
		cout << "CLIENT DESCONNECTED" << endl;
	 // std::cout << "MESSAGE: " << buffer << endl;
      break;
    }
  }
  return SUCESS;
}

void Service_Socket::select_port(SOCKET clientInstance,int port)
{
	char buffer[SIZEBUFFER];
	int recvMsgSize;
	int iResult;


	recvMsgSize = recv(clientInstance, buffer, SIZEBUFFER, 0);
	if (recvMsgSize < 0){
		std::cerr << "RECEIVED FAILED\n";
	}

	sleep(1);
	iResult = shutdown(clientInstance, SHUT_RD);
	if (iResult == SOCKET_ERROR) {
		std::cerr << "ERRO SOCKET 1 IN PORT SELECTION \n";
		close(clientInstance);
	}
	std::string portS = std::to_string(port);

	iResult = send(clientInstance, portS.c_str(), (int)portS.size(), 0);
	if (iResult == SOCKET_ERROR) {
    std::cerr << "ERRO SOCKET 2 IN PORT SELECTION \n";
		close(clientInstance);
	}
	//Encerra a conexão ja que nao ira transmitir mais dados
	iResult = shutdown(clientInstance, SHUT_WR);
	if (iResult == SOCKET_ERROR) {
    std::cerr << "ERRO SOCKET 3 IN PORT SELECTION \n";
		close(clientInstance);
	}

	iResult = close(clientInstance); //Fecha o Socket
	if (iResult == SOCKET_ERROR) {
    std::cerr << "ERRO SOCKET 4 IN PORT SELECTION \n";
	}

  cout << "CLIENT " << clientID++ << " CONNECT ON PORT: " << port <<  endl;

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

