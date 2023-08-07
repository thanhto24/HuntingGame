#pragma once
#pragma pack(1)
#include "header.h"

//Small Function
bool isExistAcc(string FileName, char username[17], unsigned int &index); //Check if account exists
bool isPasswordCorrect(string FileName, char password[15], unsigned int index);     //Check Password
void getInfo(string FileName, Player &oldMan, unsigned int index);
//Big Function
void signUp(string FileName);  // sign up new account
void signIn(string FileName, Player& oldMan, unsigned int &index);  //  log in game
void updateScore(string FileName, Player &oldMan, unsigned int index, int newscore);
//Choice Sign in or Sign up
void selectAccChoice(int &roundSelect, int &Choice);
void printAccChoice(int Choice);
void generateAccScreen(int &roundSelect, int Choice, string FileName, Player &oldMan, unsigned int &index);
