#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_TRANSACTION_SIZE 10
struct facture{
  int Reference_Agence;
  float Somme_a_payer;
};
struct reservation {
    int ReferenceVol;
    int Agence;
    char Transaction[MAX_TRANSACTION_SIZE];
    int Valeur;
};
int main() {
int choix;
    int sockfd;
     int a;
    char msg[50] = "consultation";
    char buffer[50] = { 0 };
    int bytes;
    struct facture fact;
    struct reservation r;
    struct sockaddr_in server_addr;

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET,"192.168.74.131", &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }       
    //Dashboard client 
     printf("Tapez le choix qui vous voulez : \n  1-Consulter Ma facture \n 2-Annuler une réservation  \n 3-Ajouter une reservation \n  4-Quittez \n");
     scanf("%d",&choix);
    switch(choix)
    {
    case 1 :
    {
     printf(" \n Donner le Numéro de votre Agence\n");  
     scanf("%d",&a);
     send(sockfd,"consultation",strlen("consultation"),0);
     send(sockfd,&a,sizeof(a),0);
     bytes = read(sockfd, &fact, sizeof(fact));
     printf("\n %d  %f",fact.Reference_Agence,fact.Somme_a_payer);
    break;
    }
       case 2:
    {
    send(sockfd,"Demande",strlen("Demande"),0);
    printf(" \n Pour effectuer cette Annulation : Pouvez vous me donner  \n");   
    printf("la Référence de votre Agence :");
    scanf("%d",&r.ReferenceVol);
     printf("Le numero de votre agence:");
    scanf("%d",&r.Agence);
     printf("le nombre de places que vous voulez annuler :");
    scanf("%d",&r.Valeur);
    strcpy(r.Transaction,"Annulation");
    send(sockfd, &r, sizeof(r), 0);
    bytes = read(sockfd, buffer,BUFFER_SIZE  );
    printf("%s",buffer);
    break;
    }
    case 3:
    {
        send(sockfd,"Demande",strlen("Demande"),0);
    printf(" \n Pour effectuer cette Demande : Pouvez vous me donner\n");   
    printf("la Référence de votre Agence :");
    scanf("%d",&r.ReferenceVol);
     printf("Le numero de votre agence:");
    scanf("%d",&r.Agence);
     printf("le nombre de places que vous voulez reservées :");
    scanf("%d",&r.Valeur);
    strcpy(r.Transaction,"Demande");
    send(sockfd, &r, sizeof(r), 0);
    bytes = read(sockfd, buffer,BUFFER_SIZE  );
    printf("%s",buffer);
    break;
    }
    default:
    {
    break;
    }
}
      bytes = read(sockfd, buffer,BUFFER_SIZE );
    // Print response from server
    printf("\n Response from server: %s \n", buffer);

    // Close socket
    close(sockfd);
    return 0;
    
    }
