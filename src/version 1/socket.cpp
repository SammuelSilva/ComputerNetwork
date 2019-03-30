#include "socket_define.hpp"

int main(int argc, char const *argv[]) {
//Inicialização do Socket
  socklen_t client_size;
  struct sockaddr_in address, client;

//Criar um socket

  int listening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPV4, TCP, Protocolo
  if(listening == INVALID_SOCKET){
    cerr << "Impossivel Criar o Socket, erro: " << endl;
    exit(EXIT_FAILURE);
  }

//Conectar o socket em um endereço de ip e porta
  memset((char*) &address, 0, sizeof(address));
  address.sin_family      = AF_INET;
  address.sin_port        = htons(PORT); //convere um u_short para a ordem de Byte do host da rede TCP/IP
  address.sin_addr.s_addr = INADDR_ANY; //Conectar a porta em qualquer endereço do socket

  if (bind(listening, (struct sockaddr*)&address, sizeof(address)) != 0){ //Precisa passar como segundo parâmetro o endereço do socket em forma de ponteiro
    cerr << "Erro " << " ao conectar a porta no socket"  << endl;
    exit(EXIT_FAILURE);
  }

//Avisar Winsock que o socket é para conectar

  if(listen(listening, MAXCONECTION) !=0 ){
    cerr << "Erro  " << " na espera de uma conexão" << endl;
    exit(EXIT_FAILURE);
  }
//Esperar por uma conexão

  client_size = sizeof(client);
  int client_socket = accept(listening, (struct sockaddr*)&client, &client_size);

  if(client_socket == INVALID_SOCKET){
    cerr << "Impossivel Criar o Socket cliente, erro: " << endl;
    exit(EXIT_FAILURE);
  }

  char host[NI_MAXHOST]; //Nome remoto do cliente
  char service[NI_MAXSERV]; // Service (i.e port) que o client esta conectado

//Seta os primeiros numeros de bytes de um ponteiro de um bloco de memoria para um valor especifico (Unsigned char), neste caso esta setando 0 NI_MAXHOST
  memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);

//Verifica se consegue o nome do host que esta conectado se nao der, usamos o ip_address

  if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
    cout << host << " conectado na porta: " << service << endl; // possivel nome
  }else{
    inet_ntop(AF_INET,&client.sin_addr, host, NI_MAXHOST); //Gera o endereco IP da porta
    cout << host << "conectado na porta " << ntohs(client.sin_port) << endl;
  }
//Fehar socket de escuta, devemos nao fechar ele se quisermos outros clientes
  close(listening);
//While loop: aceitar e enviar a mensagem de volta para o cliente
  char buffer[SIZEBUFFER];

  //Esperar o cliente enviar dados
  while(RECEIVING){
    int bytes_rcv = recv(client_socket, buffer, SIZEBUFFER, 0);
    if(bytes_rcv == SOCKET_ERROR){
      cerr << "Erro na funcao recv(). Saindo" << endl;
      exit(EXIT_FAILURE);
    }
    if(bytes_rcv == 0){
      cout << "Cliente desconectado" << endl;
      break;
    }
    //Mensagem de volta para o cliente, com o \0
    send(client_socket, buffer, bytes_rcv+1, 0);
  }

//Fechar o Socket
  close(client_socket);

  return 0;
}
