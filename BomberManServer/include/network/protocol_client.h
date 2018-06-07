#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

typedef struct  s_client_request
{
unsigned int  magic;                  /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
int           x_pos;                  /* La position x souhait?e par le client */
int           y_pos;                  /* La position y souhait?e par le client */
int           dir;                    /* La direction souhait?e par le client */
int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
int           speed;                  /* La vitesse du joueur */
int           checksum;               /* Un checksum simple */
}               t_client_request;

#endif // PROTOCOL_CLIENT_H

