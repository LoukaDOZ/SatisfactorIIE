#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>
#include <signal.h>

#include <sys/mman.h>
#include <sys/wait.h>

#include "../headers/client.h"

/*
* @return : -1 en cas d'erreur
*/
int envoyer_message_serveur(int socket, int msg) {
  return write(socket, &msg, sizeof(int));
}

/*
* @return : -1 en cas d'erreur
*/
int lire_message_serveur(int socket, int* msg) {
  return read(socket, msg, sizeof(int));
}

void close_socket_client(int socket) {
  shutdown(socket, SHUT_RDWR);
  close(socket);
}

int lancer_client(char* adresse, int port) {
  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(adresse);

  int sc = socket(AF_INET, SOCK_STREAM, 0);
  if(sc == -1) { 
    perror("error socket()"); 
    exit(1); 
  }

  int ok = connect(sc, (struct sockaddr *) &addr, sizeof(addr) );
  if (ok == -1) { 
    perror("error connect()"); 
    exit(1); 
  }

  return sc;
}