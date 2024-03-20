#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "generate.h"
#include "main.h"

char generate_random_char(const char *charset) {
    unsigned index = rand() % (strlen(charset)); // pick char from set
    return charset[index];
}

short copy_selected_charset(const char charset_all[], char *chosen_charset, const enum charset_type ctype) {
    char *copy_set = NULL;

    switch (ctype) {
        case ALL:
            strcpy(chosen_charset, charset_all);
            break;
        case DIGITS:
            copy_set = "0123456789";
            strcpy(chosen_charset, copy_set);
            break;
        case ONLY_CHARACTERS:
            copy_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            strcpy(chosen_charset, copy_set);
            break;
        default:
            chosen_charset = NULL;
            fprintf(stderr, "Invalid charset type.");
            return 1;
    }
    return 0;
}

void generatePassword(unsigned psw_length, char *password, enum charset_type ctype) {
    const char charset_all[] =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?@#$%^&*()-_=+{}[]|,;:<>.";
    char chosen_charset[CHARSET_ALL_LEN];

    if (copy_selected_charset(charset_all, chosen_charset, ctype) != 0) { return; }

    for (int i = 0; i < psw_length; i++) {
        // print into buffer because stdout is not efficient
        snprintf(&password[i], 2, "%c", generate_random_char(chosen_charset));
    }
    password[psw_length] = '\0';
}

int choose_pswconfig(unsigned *length, unsigned *reps, enum charset_type *chosen_set) {
    char length_input[5];
    char reps_input[5];
    char set_input[5];
    char *trash;

    printf("Enter password length:");
    if (length_input != fgets(length_input, 4, stdin)) { return 1; }
    length_input[4] = '\0';
    *length = strtoul(length_input, &trash, 10);

    if (*length >= MAX_PSW) {
        printf("Length is too big.\n");
        return 1;
    } else if (*length <= 0) {
        printf(" Please enter a positive length.\n");
        return 1;
    }

    printf("How many you want to generate:");
    if (reps_input != fgets(reps_input, 4, stdin)) { return 1; }
    reps_input[4] = '\0';
    *reps = strtoul(reps_input, &trash, 10);

    if (*reps <= 0) {
        printf("Please enter a positive number of repetitions.\n");
        return 1;
    } else if (*reps >= MAX_REPS) {
        printf("Too many passwords at once!\n");
        return 1;
    }

    printf("Which charset you want to use?\n");
    printf("(1)All; (2) Digits(0-9); (3)Characters:");
    if (set_input != fgets(set_input, 4, stdin)) { return 1; }
    set_input[4] = '\0';
    *chosen_set = strtoul(set_input, &trash, 10);

    if (*chosen_set <= 0) {
        printf("Please enter a positive number for a set.\n");
        return 1;
    } else if (*chosen_set > N_SETS) {
        printf("Too big set number!\n");
        return 1;
    }

    return 0;
}

int action_generate_passwords(unsigned *length, char password[MAX_PSW]) {
    enum charset_type chosen_set;
    unsigned reps = 1;// The number of generating repetitions

    // let user input length and repetitions
    if (choose_pswconfig(length, &reps, &chosen_set) != 0) { return 1; }

    /* pick seed for pseudo random generator.
     * system time & processID & user-input correlates to seed but combination of all 3 is pretty unpredictable
     * But there remains a pattern in each sequence, that is why I want to replace it with a more random function.  */
    srand((time(NULL) + getpid() + reps) / 3);

    {
        char again; // To ask the user, if he wants (reps) passwords more n=no, y=yes.
        do {

            for (unsigned i = 0; i < reps; i++) {
                generatePassword(*length, password, chosen_set);
                printf("%s\n", password);
            }
            printf("Generate again(y/n)?");
            again = (char) fgetc(stdin);
            fgetc(stdin);// remove newline character from stdin-buffer
        } while (again == 'y');
    }
    return 0;
}
