#include "server_client_link_list.h"

//display the list
void print_clients_list(client_ptr clntHead) {
	client_ptr clntpCurrClient = clntHead;
	printf("\n[ ");
	
	//start from the beginning
	while(clntpCurrClient != NULL) {
		printf("(sndIAm : %d, fdSocket : %d, id : %s, szName : %s), \n", clntpCurrClient->sndIAm, clntpCurrClient->fdSocket, clntpCurrClient->szId, clntpCurrClient->szName);
		clntpCurrClient = clntpCurrClient->clntNextClient;
	}
	printf(" ]\n");
}

//insert link at the first location
void insert_client(sender sndIAm, int fdSocket, char szId[], char szName[], client_ptr * clntHead) {
	//create a new client
	client_ptr clntpNewClient = (client_ptr) malloc(sizeof(client));
	
	//set info
	clntpNewClient->sndIAm = sndIAm;
	clntpNewClient->fdSocket = fdSocket;
	strcpy(clntpNewClient->szId, szId);
	strcpy(clntpNewClient->szName, szName);
	
	//point it to old first node
	clntpNewClient->clntNextClient = *clntHead;
	
	//point first to new first node
	*clntHead = clntpNewClient;
}

void remove_client(int fdSocketId, client_ptr * clntHead){
	//start from the first link
	client_ptr clntpCurrClient = * clntHead;
	client_ptr clntpPrevClient = NULL;
	
	//if list is empty
	if(clntHead == NULL) 
		return;

	// navigate through list
	while(clntpCurrClient->fdSocket != fdSocketId) {
		//if it is last node
		if(clntpCurrClient->clntNextClient == NULL) 
			return;
		else {
			//store reference to current link
			clntpPrevClient = clntpCurrClient;
			//move to next link
			clntpCurrClient = clntpCurrClient->clntNextClient;
		}
	}
	//found a match, update the link
	if(clntpCurrClient == *clntHead) 
		//change first to point to next link
		*clntHead = (*clntHead)->clntNextClient;
	else 
		//bypass the current link
		clntpPrevClient->clntNextClient = clntpCurrClient->clntNextClient;
}