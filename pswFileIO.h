#ifndef PSW_GENERATOR_PSWFILEIO_H
#define PSW_GENERATOR_PSWFILEIO_H

#include "main.h"

#define PSW_FILE "pswList.txt"
#define MAX_NR_PSWS 10000

short action_save_psw(char psw[MAX_PSW],char *filename);

short get_psws_from_file
(unsigned *nSavedPsws, unsigned *capacity_passwords, char ** pswList);

short print_passwords(unsigned nSavedPsws, char ** pswList, unsigned *capacity_pswlist);

#endif //PSW_GENERATOR_PSWFILEIO_H
