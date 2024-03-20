#include <stdio.h>

#include "pswFileIO.h"

unsigned n_saved_passwords;
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
    size_t len = 0;// number of tokens read from current input line

    // open the input file for reading
    FILE *file = fopen(PSW_FILE, "r");
    if (file == NULL) {
        fprintf(stderr,"Inventarliste kann nicht gelesen werden");
        return 1;
    }

    len=fscanf(file,"%s",read_psw);
    if(len!=1){return 0;}

    do{
        len=fscanf(file,"%s",read_psw);
        n_saved_passwords++;
        saved_passwords[n_saved_passwords]=read_psw;
    }while(len==1 && (n_saved_passwords<=MAX_NR_PSWS));

    fclose(file);
    return 0;
}
