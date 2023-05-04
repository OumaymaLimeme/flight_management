#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 100
#define MAX_LINE_LENGTH 100
#define MAX_TRANSACTION_SIZE 10
struct reservation {
    int ReferenceVol;
    int Agence;
    char Transaction[MAX_TRANSACTION_SIZE];
    int Valeur;
};
// fuction that update a line in file
void update_file(char*file,int line_number_to_update ,char new_line[]){
    FILE* fp;
    int current_line_number = 1;
    char line[MAX_LINE_LENGTH];
    // Open the file for reading and writing
    fp = fopen(file, "r+");
    // Check if the file was opened successfully
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Check if this is the line we want to update
        if (current_line_number == line_number_to_update) {
            // Move the file pointer back to the beginning of the line
            fseek(fp, -(strlen(line)), SEEK_CUR);
            // Write the updated line to the file
            fputs(new_line, fp);
        }
        current_line_number++;
    }
    // Close the file
    fclose(fp);
    }
    //This function takes a line and split in in words by a  delimiter  // the output is a table of  words  
void split_line(char line[100], char *delimiter, char (*tokens)[MAX_TOKEN_LEN], int *num_tokens) {
    char *token;
    *num_tokens = 0;
    token = strtok(line, delimiter);
    while (token != NULL && *num_tokens < MAX_TOKENS) {
        strncpy(tokens[*num_tokens], token, MAX_TOKEN_LEN - 1);
        (*num_tokens)++;
        token = strtok(NULL, delimiter);
    }
}
void list_reservations(){
  FILE*f=fopen("histo.txt","r");
  char chaine[100];
  if (f== NULL) {
        printf("Error opening the file\n");
        exit(1);
    }
     // Read and display the file line by line
   while (fgets(chaine, sizeof(chaine), f) != NULL) {
        printf("%s", chaine);
    }

    // Close the file
    fclose(f);
}
char* traiter_demande(struct reservation r){
    char* msg;
    int a;
    float b;
    int nb;
    int i;
    int x,y;
    int s=0;
    char str[50]="";
    char str1[50];
    char str3[50];
    char chaine[50];
    char chaine1[50];
    char line[100];
    char subbuff[50];
    char subbuff2[50];
    char* new_line;
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens = 0;
    int line_number_to_update=0;
    char delimiter[] = " ";
    int nbr_place;
    float prix_place;
      FILE*f=fopen("histo.txt","a");
      FILE*p=fopen("facture.txt","r+");
      FILE*t=fopen("vols.txt","r+");
      if (f== NULL) {
        printf("Error opening the file\n");
        exit(-1);
      }
       if (t== NULL) {
        printf("Error opening the file\n");
        exit(-1);
      }
      if (p== NULL) {
        printf("Error opening the file\n");
        exit(-1);
      }
       while (fgets(line, sizeof(line),t) != NULL) {
           s++;
          split_line(line, delimiter, tokens, &num_tokens);
          if(r.ReferenceVol==atoi(tokens[0])) goto flag;
          }        
      flag:      
      if (strcmp(r.Transaction, "Annulation") == 0){
      fprintf(f,"%d %d %s %d  Succès \n",r.ReferenceVol,r.Agence,r.Transaction,r.Valeur);
      fclose(f);
      while (fgets(line, sizeof(line), p) != NULL) {
      line_number_to_update+=1;
        for(i=0;i<strlen(line);i++){
              if (line[i]==' ') 
          { nb=i;       
        strncpy(subbuff,line,nb);  
        strncpy(subbuff2,line+nb,strlen(line)-nb);   
        a=atoi(subbuff);       
        b=atof(subbuff2);
        if(r.Agence==a){   
        b-=atof(tokens[3])*r.Valeur;  
        b+=(atof(tokens[3])*r.Valeur)*0.1;
        sprintf(str,"%d",a);
        sprintf(str1,"%d",(int)b);    
        strcat(str," ");   
        strcat(str,str1);
        update_file("facture.txt",line_number_to_update,str); 
        y=atoi(tokens[2]);
        y+=r.Valeur;
       strcat(str3,tokens[0]);
       strcat(str3," ");   
       strcat(str3,tokens[1]);
       strcat(str3," "); 
       sprintf(chaine1,"%d",y);
       strcat(str3,chaine1);  
       strcat(str3," ");   
       strcat(str3,tokens[3]);
        printf("%s",str3);
        update_file("vols.txt",s,str3); 
        return "Annulation terminée avec succée";            
        }   
        }
      }
}
}
  if (strcmp(r.Transaction,"Demande") == 0){
   if(atoi(tokens[2])<r.Valeur){
   fprintf(f,"\n %d %d %s %d  Impossible \n",r.ReferenceVol,r.Agence,r.Transaction,r.Valeur);
      fclose(f);
      return "Impossible : Nombre de places insuffisants";
   }
   else{
      fprintf(f," \n %d %d %s %d  Succès \n",r.ReferenceVol,r.Agence,r.Transaction,r.Valeur);
      fclose(f);
       x=atoi(tokens[2])-r.Valeur;
       strcat(str,tokens[0]);
       strcat(str," ");   
       strcat(str,tokens[1]);
       strcat(str," "); 
       sprintf(chaine,"%d",x);
       strcat(str,chaine);  
       strcat(str," ");   
       strcat(str,tokens[3]);
        printf("%s",str);
        update_file("vols.txt",s,str); 
        while (fgets(line, sizeof(line), p) != NULL) {
       line_number_to_update+=1;
        for(i=0;i<strlen(line);i++){
              if (line[i]==' ') 
          { nb=i;       
        strncpy(subbuff,line,nb);  
        strncpy(subbuff2,line+nb,strlen(line)-nb);   
        a=atoi(subbuff);       
        b=atof(subbuff2);
        if(r.Agence==a){   
        b+=(atof(tokens[3])*r.Valeur);
        sprintf(str,"%d",a);
        sprintf(str1,"%d",(int)b);    
        strcat(str," ");   
        strcat(str,str1);
        update_file("facture.txt",line_number_to_update,str); 
        return "Demande terminée avec succés";            
        }   
        }
      }
}
        
   }
  
  }
       

}