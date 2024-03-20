#ifndef PSW_GENERATOR_EVALUATEPSW_H
#define PSW_GENERATOR_EVALUATEPSW_H

#include "main.h"

unsigned long long evaluate_password(const char *psw);

void print_psw_score(unsigned long long possibilities);

int action_rate_psw(char psw[MAX_PSW]);

#endif //PSW_GENERATOR_EVALUATEPSW_H
