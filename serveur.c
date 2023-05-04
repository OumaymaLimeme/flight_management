#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dashboard.h"
#define MAX_CLIENTS 3
// function to handle client connections
void *handle_client(void *arg) {
    int client_fd = *(int*) arg;
    char buffer[50] = {0};
    struct reservation r;
    int a;
    char* message;
    char *response = "Demande terminée avec succés";
    int bytes;
    // read data from the client socket
    while (1) {
      //memset(&buffer, 0, sizeof(buffer));
      bytes = read(client_fd, buffer, sizeof(buffer));
      printf("\n Received message from client: %s\n", buffer);
    // Process the data from the client
    if (strcmp(buffer, "consultation") == 0) {
        bytes = read(client_fd, &a, sizeof(a));
        struct facture  fact=get_factureById(a);
        write(client_fd, &fact, sizeof(fact));
    } 
    else if (strcmp(buffer,"Demande") == 0) {  
      bytes =read(client_fd,&r,sizeof(r));
        printf("%d",sizeof(r.Transaction));
      printf("%s",r.Transaction);
      message=traiter_demande(r);
      write(client_fd, message, strlen(message)+1); 
    }
     else {
        response = " \n unknown command \n";
         }
    // Send response back to the client
     write(client_fd, response, strlen(response) + 1);
     // Close the sockets
    close(client_fd);
    return NULL;
    }
    return 0;    
}


// function to start the server and handle incoming client connections
void start_server(int port) 
{
    int nbClients=0;
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t tid[MAX_CLIENTS];

    // create a socket for the server
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    // bind the socket to the specified port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    // accept incoming connections and handle client requests
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &addr_len)) < 0) {
            perror("accept");
            continue;
        }

        // handle each client connection in a separate thread
        pthread_create(&tid[nbClients], NULL, handle_client, &client_fd);
        nbClients ++;
    }

    close(server_fd);
}
// function to start the admin dashboard

int main(int argc, char *argv[]) 
{
    int port = 8080;
    // start the server in a separate thread
    pthread_t server_tid;
    pthread_create(&server_tid, NULL, start_server, port);
    // start the admin dashboard in the main thread
   while(1){ 
   start_dashboard();
           }
   pthread_join(server_tid,NULL);
    
}
