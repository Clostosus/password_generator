#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "evaluatepsw.h"

unsigned long calc_real_possibilities
        (smallu len, smallu digits, smallu spec_chars, smallu small_letters, smallu big_letters) {
    unsigned long long possibilities;
    smallu n_chars = 0;

    if (digits != 0) { n_chars += 10; }
    if (spec_chars != 0) { n_chars += 27; }
    if (small_letters != 0) { n_chars += 26; }
    if (big_letters != 0) { n_chars += 26; }

    if(pow(n_chars, len)>=(double)LONG_LONG_MAX){
        possibilities=(unsigned long long) LONG_LONG_MAX;
    }else{
        possibilities=(unsigned long long) pow(n_chars,len);
    }
    return possibilities;
}

void count_chars_of_type(
        const char *psw, smallu *digits, smallu *small_letters, smallu *big_letters, smallu *spec_chars) {
    smallu len = strlen(psw) - 1;
    for (smallu i = 0; i < len; i++) {
        if (psw[i] >= '0' && psw[i] <= '9') {
            (*digits)++;
        } else if (psw[i] >= 'a' && psw[i] <= 'z') {
            (*small_letters)++;
        } else if (psw[i] >= 'A' && psw[i] <= 'Z') {
            (*big_letters)++;
        } else if ((psw[i] >= ' ' && psw[i] <= '/') || (psw[i] >= ':' && psw[i] <= '@') ||
                   (psw[i] >= '[' && psw[i] <= '`') || (psw[i] >= '{' && psw[i] <= '~')) {
            (*spec_chars)++;
        }
    }
}

// rating the psw based on length,type and missing char_categories of charset
unsigned long long evaluate_password(const char *psw) {
    // score:  0-19=very bad,20-39=bad, 40-59=average,60-79=good,80-100=very good
    smallu len = strlen(psw) - 1;
    smallu digits = 0, spec_chars = 0, small_letters = 0, big_letters = 0;
    // count how many chars of each type are in the password
    count_chars_of_type(psw, &digits, &small_letters, &big_letters, &spec_chars);

    return calc_real_possibilities(len, digits, spec_chars, small_letters, big_letters);
}

void print_psw_score(unsigned long long possibilities) {
    // Score: 0-19=very bad, 20-39=bad, 40-59=average, 60-79=good, 80-100=very good
    printf("Trying out all possibilities takes %llu tries. ", possibilities);
    printf("Password Strength: ");

    if (possibilities <= 1000000) {
        printf("Very bad\n");
    } else if (possibilities <= 1000000000) {
        printf("Bad\n");
    } else if (possibilities <= 1000000000000) {
        printf("Average\n");
    } else if (possibilities <= 1000000000000000) {
        printf("Good\n");
    } else {
        printf("Very good\n");
    }
}

int action_rate_psw(char password[MAX_PSW]){
    printf("Enter a password that you want to get rated.\n");
    if (password != fgets(password, MAX_PSW, stdin)) {
        fprintf(stderr, "Invalid password input.");
        return 1;
    }

    unsigned long long possibilities = evaluate_password(password);
    print_psw_score(possibilities);

    return 0;
}