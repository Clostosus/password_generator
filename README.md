# psw_generator

This repository is copied from another repository, but I not cloned/forked it, because there was my real name in the commit history. 

In this repository, there is a password-generator. 
- The main.c files purpose is to let the user choose and to coordinate the other functions.
- The generate.c file is there to provide functions which generate passwords, and functions which ask the user what password configuration he wants. It is Pseudo-Random, but still **NOT** cryptographically **SECURE**.
- The evaluatepsw.c file provides functions that evaluate the strength of a password depending on the type of used characters and length. Maybe wordlists will be also a criterium in the future.
- The file "pswFileIO.c" is for saving the encrypted password into a file, and decrypting+reading it later.
