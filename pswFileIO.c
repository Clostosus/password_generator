#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pswFileIO.h"

short action_save_psw(char psw[MAX_PSW],char *filename){

    printf("Enter a password:");
    fgets(psw,MAX_PSW,stdin);

    short psw_len=(short)strlen(psw);
    for(short i=0;i<psw_len;i++){
        if((psw[i]>'~'||psw[i]<' ')&&(psw[i]!='\n')){printf("Forbidden characters used!\n");return 1;}
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

short get_psws_from_file(unsigned *nSavedPsws, unsigned *capacity_passwords, char ** pswList){
    char read_psw[MAX_PSW];
    *nSavedPsws=0;
    size_t len=0;// number of tokens read from current input line
    *capacity_passwords=25;
    pswList=NULL;
    pswList=(char**)calloc(*capacity_passwords, sizeof(char *));
    if(pswList == NULL){return 1;}

    // open the input file for reading
    FILE *file = fopen(PSW_FILE, "r");
    if (file == NULL) { fprintf(stderr,"Password file opening error."); return 1; }

    // read one password from the file
    while(fgets(read_psw,MAX_PSW,file)!=NULL){
        // Replace newline by \0 char from end of read password
        unsigned read_len = strlen(read_psw);
        if (read_len > 0 && read_psw[len - 1] == '\n') {read_psw[read_len - 1] = '\0'; }

        pswList[*nSavedPsws]=strdup(read_psw);
        if (pswList[*nSavedPsws] == NULL) {
            fprintf(stderr, "Error saving a read password."); return 1;}
        (*nSavedPsws)++;

        // If needed, give saved passwords List more capacity
        if (*nSavedPsws >= *capacity_passwords) {
            *capacity_passwords *= 2;
            if(*capacity_passwords>MAX_NR_PSWS){fprintf(stderr,"Too many passwords in the list.");return 1;}
            pswList = (char **)realloc(pswList, *capacity_passwords * sizeof(char *));
            if (pswList == NULL) {
                fprintf(stderr, "Error extending password list capacity."); return 1; }
        }
    }

    fclose(file);
    return 0;
}

short print_passwords(unsigned nSavedPsws, char ** pswList, unsigned *capacity_pswlist) {
    if (pswList == NULL) {
        if(get_psws_from_file(&nSavedPsws, capacity_pswlist, pswList) != 0)
        {return 1;}
    }

    if(pswList == NULL){printf("File is empty.");return 0;}

    for (int i = 0; i < nSavedPsws; i++) {
        printf("psw(%i)=%s", i, pswList[i]);
    }
    printf("\n");
    return 0;
}
