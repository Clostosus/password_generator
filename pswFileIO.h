#ifndef PSW_GENERATOR_PSWFILEIO_H
#define PSW_GENERATOR_PSWFILEIO_H

#include "main.h"

#define PSW_FILE "saved_passwords.txt"
#define MAX_NR_PSWS 10000

short action_save_psw(char psw[MAX_PSW],char *filename);

short read_psws_from_file(void);

#endif //PSW_GENERATOR_PSWFILEIO_H
