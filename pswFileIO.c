#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pswFileIO.h"

unsigned n_saved_passwords;
unsigned capacity_passwords;
char ** saved_passwords=NULL;

short action_save_psw(char psw[MAX_PSW],char *filename){

    printf("Enter a password:");
    if(psw!=fgets(psw,MAX_PSW,stdin)){
        fprintf(stderr,"Invalid password input");return 1;
    }

    FILE *file= fopen(filename,"a"); // append mode
    if(file==NULL){
        fprintf(stderr,"File to save password was not found or corrupted.");
        return 1;
    }

    fprintf(file,"%s",psw);

    fclose(file);
    printf("Password saved.\n");
    return 0;
}

short read_psws_from_file(void){
    char read_psw[MAX_PSW];
    n_saved_passwords=0;
    size_t len=0;// number of tokens read from current input line
    capacity_passwords=25;
    saved_passwords=NULL;
    saved_passwords=(char**)calloc(capacity_passwords,sizeof(char *));
    if(saved_passwords==NULL){return 1;}

    // open the input file for reading
    FILE *file = fopen(PSW_FILE, "r");
    if (file == NULL) { fprintf(stderr,"Password file opening error."); return 1; }

    while(fgets(read_psw,MAX_PSW,file)!=NULL){
        // Replace newline by \0 char from end of read password
        unsigned read_len = strlen(read_psw);
        if (read_len > 0 && read_psw[len - 1] == '\n') {read_psw[read_len - 1] = '\0'; }

        saved_passwords[n_saved_passwords]=strdup(read_psw);
        if (saved_passwords[n_saved_passwords] == NULL) {
            fprintf(stderr, "Error saving a read password."); return 1;}
        n_saved_passwords++;

        // If needed, give saved passwords array more capacity
        if (n_saved_passwords >= capacity_passwords) {
            capacity_passwords *= 2;
            saved_passwords = (char **)realloc(saved_passwords, capacity_passwords * sizeof(char *));
            if (saved_passwords == NULL) {
                fprintf(stderr, "Speicherplatzfehler."); return 1; }
        }
    }

    for(int i=0;i<n_saved_passwords;i++){
        printf("psw(%i)=%s",i,saved_passwords[i]);
    }
    printf("\n");

    fclose(file);
    free(saved_passwords);
    return 0;
}
