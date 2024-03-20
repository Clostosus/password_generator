#ifndef PSW_GENERATOR_GENERATE_H
#define PSW_GENERATOR_GENERATE_H

#include "main.h"

char generate_random_char(const char *charset);

short copy_selected_charset(const char charset_all[], char *chosen_charset, enum charset_type ctype);

void generatePassword(unsigned psw_length, char *password, enum charset_type ctype);

int choose_pswconfig(unsigned *length, unsigned *reps, enum charset_type *chosen_set);

int action_generate_passwords
        (unsigned *length, char password[MAX_PSW]);

#endif //PSW_GENERATOR_GENERATE_H
