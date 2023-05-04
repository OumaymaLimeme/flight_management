#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct facture {
    int ReferenceAgence;
    float Somme_payer;
};
void liste_factures(){
  FILE*f=fopen("facture.txt","r");
  char line[100];
  if (f== NULL) {
        printf("Error opening the file\n");
        exit(1);
    } 
    // Read and display the file line by line
   while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line);
    }
    // Close the file
    fclose(f);
}
struct facture get_factureById(int agence_id){
    struct facture fact;
    int i=0;
    int nb;
    char line[100];
    char subbuff[50];
    char subbuff2[50];
    FILE*f=fopen("facture.txt","r");
     if (f== NULL) {
        printf("Error opening the file\n");
        exit(1);
    }
     // Read and find id  
      while (fgets(line,sizeof(line), f) != NULL) {
            for(i=0;i<strlen(line);i++){
              if (line[i]==' ') nb=i;
              }
        strncpy(subbuff,line,nb);
        strncpy(subbuff2,line+nb,strlen(line)-nb);   
        fact.ReferenceAgence=atoi(subbuff);
        fact.Somme_payer=atof(subbuff2);         
        if(fact.ReferenceAgence==agence_id) {fclose(f); return fact;}
        }
      printf(" \n Error : Pas de facture \n");
      exit(1);    
        }         