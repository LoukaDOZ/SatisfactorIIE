#ifndef SERVEUR_H
#define SERVEUR_H

/*
* @return : -1 en cas d'erreur
*/
int envoyer_message_client(int socket, int msg);

/*
* @return : -1 en cas d'erreur
*/
int lire_message_client(int socket, int* msg);

void close_socket_serveur(int socket);

int lancer_serveur(int port);

#endif