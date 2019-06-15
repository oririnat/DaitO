#include "server_connection.h"

int opt = true; 
int i;

void initialize_connection(){		
	//create a master socket
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
		
	//set master socket to allow multiple connections, this is just a good habit, it will work without this
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
		
	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
		
	//bind the socket
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Listener on port %d \n", PORT); 
		
	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(master_socket, 3) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}
	//accept the incoming connection, waiting for connections
	addrlen = sizeof(address);
		
}
void add_child_sockets_to_set(client_ptr * client_list){
	client_ptr curr_client = *client_list;
	while(curr_client){
		//socket descriptor 
		socket_descriptor = curr_client->socket_fd;
	
		//if valid socket descriptor then add to read list 
		if(socket_descriptor > 0)
			FD_SET(socket_descriptor , &readfds); 
			
		//highest file descriptor number, need it for the select function 
		if(socket_descriptor > max_socket_descriptor) 
			max_socket_descriptor = socket_descriptor; 
		
		curr_client = curr_client->next_client;
	}
}