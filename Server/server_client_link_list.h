//server_client_link_list.h

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define AES_KEY_LEN 16
#define HASH_LEN 34
#define MAX_USER_NAME_LEN 32

typedef enum {
	AGENT, 
	WANTED
} sender;

typedef struct client_node {
	sender sndIAm;
	int fdSocket;
	char szId[HASH_LEN];
	char szName[MAX_USER_NAME_LEN];	
	char szEncryptionKey[AES_KEY_LEN + 1];
	struct client_node * clntNextClient;
} client, * client_ptr;

// global list
//client_ptr clients;


void print_clients_list(client_ptr head);
void insert_client(sender sndIAm, int fdSocket, char szId[], char szName[], client_ptr * clntHead) ;
void remove_client(int fdSocketId, client_ptr * clntHead);
