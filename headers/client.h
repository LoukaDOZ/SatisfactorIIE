#ifndef CLIENT_H
#define CLIENT_H

/*
* @return : -1 en cas d'erreur
*/
int envoyer_message_serveur(int socket, int msg);

/*
* @return : -1 en cas d'erreur
*/
int lire_message_serveur(int socket, int* msg);

void close_socket_client(int socket);

int lancer_client(char* adresse, int port);

#endif
