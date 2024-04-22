/* SERVEUR. Lancer ce programme en premier (pas d'arguments). */

#include <stdio.h>                  /* fichiers d'en-tête classiques */
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/socket.h>             /* fichiers d'en-tête "réseau" */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>
#include <string.h>

#include <sys/select.h>
#include <sys/time.h>

#include "../headers/serveur.h"

#define MAX_CLIENTS  2           /* Nombre maximum de clients */

char* concat(const char *s1, const char *s2){
  char *result = malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

/*
* @return : -1 en cas d'erreur
*/
int envoyer_message_client(int socket, int msg) {
  return write(socket, &msg, sizeof(int));
}

/*
* @return : -1 en cas d'erreur
*/
int lire_message_client(int socket, int* msg) {
  return read(socket, msg, sizeof(int));
}

void close_socket_serveur(int socket) {
  shutdown(socket, SHUT_RDWR);
  close(socket);
}

int lancer_serveur(int port) {
  /* 3. On prépare l'adresse du serveur. */
  struct sockaddr_in saddr = {0};
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* 2. On crée la socket d'écoute. */
  int se = socket(AF_INET,SOCK_STREAM, 0);
  if (se == -1) { 
    perror("error socket()"); 
    exit(1); 
  }

  /* 4. On attache la socket a l'adresse du serveur. */
  int ok = bind(se, (struct sockaddr*) &saddr, sizeof(saddr));
  if (ok == -1) { 
    close_socket_serveur(se);
    perror("error bind()"); 
    exit(1); 
  }

  /* 5. Enregistrement auprès du système. */
  listen(se,MAX_CLIENTS);

  int maxs = se;
  int sockets[2];
  int ressources[2];
  int nb_client = 0;
  int tailleCarte;
  int quitter = 0;
  fd_set ensemble, temp;
  
  FD_ZERO(&ensemble);
  FD_SET(0,&ensemble);
  FD_SET(se, &ensemble);

  while(!quitter) {
    if(nb_client < MAX_CLIENTS) {
      sockets[nb_client] = accept(se,NULL,NULL);
      FD_SET(sockets[nb_client], &ensemble);
      if(maxs < sockets[nb_client])
        maxs = sockets[nb_client];
      nb_client++;

      if(nb_client == 1) {
        /* err ? = */lire_message_client(sockets[0], &tailleCarte);
      } else if(nb_client == 2) {
        /* err ? = */envoyer_message_client(sockets[1], tailleCarte);
        /* err ? = */lire_message_client(sockets[0], &ressources[0]);
        /* err ? = */lire_message_client(sockets[1], &ressources[1]);
        /* err ? = */envoyer_message_client(sockets[0], ressources[1]);
        /* err ? = */envoyer_message_client(sockets[1], ressources[0]);
      }
    } else {
      temp = ensemble;
      select(maxs + 1, &temp, NULL, NULL, NULL);
      
      for(int i = 0; i < 2; i++) {
        if(FD_ISSET(sockets[i], &temp)) {
          if (lire_message_client(sockets[i], &ressources[i]) <= 0){
            nb_client--;
            quitter = 1;

            envoyer_message_client(sockets[(i + 1) % 2], -3);
            break;
          } else {
            envoyer_message_client(sockets[i], ressources[(i + 1) % 2]);
          }
        }
      }

      for(int i = 0; i < 2; i++) {
        if(ressources[i] <= 0) {
          envoyer_message_client(sockets[i], -2);
          envoyer_message_client(sockets[(i + 1) % 2], -1);
        }
      }
    }
  }

  for(int i = 0; i < 2; i++) {
    FD_CLR(sockets[i], &ensemble);
    close_socket_serveur(sockets[i]);
  }
  FD_CLR(se, &ensemble);
  close_socket_serveur(se);

  return 1;
}