#include <stdio.h>

#include "main.h"
#include "generate.h"
#include "evaluatepsw.h"
#include "pswFileIO.h"

char ask_for_action(){
    char action;
    printf("Enter an action(q=quit, g=generate_psw, r=rate_psw, s=save_psw):\n");
    action= (char) fgetc(stdin);
    fgetc(stdin);// remove newline character from stdin-buffer
    return action;
}

int main() {
    unsigned length = 0;// The length of the password
    char password[MAX_PSW];
    char user_choice; // q=quit; g=generate_psw ; r=rate_psw ; s= save_psw

    do {
        user_choice=ask_for_action();

        switch (user_choice) {
            case 'g':
                if (action_generate_passwords(&length, password) != 0) { return 1; }
                break;
            case 'r':
                if (action_rate_psw(password) != 0) { return 1; }
                break;
            case 'q':
                printf("Program ends.");
                break;
            case 's':// work in progress
                if(action_save_psw(password,PSW_FILE)!=0){return 1;}
                break;
            default:
                return 1;
        }

    }while(user_choice!='q');
    return 0;
}
