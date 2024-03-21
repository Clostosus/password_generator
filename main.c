#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "generate.h"
#include "evaluatepsw.h"
#include "pswFileIO.h"

unsigned nSavedPsws;
unsigned capacity_passwords;
char ** pswList=NULL;
char * masterPsw=NULL;

char ask_for_action(){
    char action;
    printf("Enter an action(q=quit, g=generate_psw, r=rate_psw, s=save_psw,p=print_psws):\n");
    action= (char) fgetc(stdin);
    fgetc(stdin);// remove newline character from stdin-buffer
    return action;
}

int main() {
    unsigned length = 0;// The length of the password
    char password[MAX_PSW];
    char user_choice; // q=quit; g=generate_psw ; r=rate_psw ; s= save_psw; p=print_saved_psws

    do {
        user_choice=ask_for_action();

     switch (user_choice) {
         case 'g':
             if (action_generate_passwords(&length, password) != 0) { return 1; }
             break;
         case 'r':
             if (action_rate_psw(password) != 0) { return 1; }
             break;
         case 's':
             if(action_save_psw(password,PSW_FILE)!=0){return 1;}
             break;
         case 'p':
             if(print_passwords(nSavedPsws, pswList, &capacity_passwords)!=0)
             {return 1;};
             break;
         default:
             user_choice='q';
             break;
        }

    }while(user_choice!='q');

    free(pswList);
    return 0;
}
