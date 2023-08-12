#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <new>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <mmsystem.h>

#pragma pack (1)
#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace std::chrono;

#define ii pair<int, int>
#define iii pair<ii, int>
#define f first
#define s second
#define mp make_pair
#define KeyUp 72
#define KeyDown 80
#define KeyLeft 75
#define KeyRight 77
#define Space 32
#define Esc 27

const char MSSV[] = " 22127174221273222212738822127441";

struct Point
{
    int x, y;
};

struct Snake
{
    vector<Point> body;
    Point head, tail;
    int direction;
    bool feed;
    bool turnRed = false;
};

struct Board
{
    string str;
    bool game_active;
    int** viewBoard;
    int hei, wid;
    int level;
    int hh, mm, ss;
    bool haveBigApple;
    int score;
    int scoreToPass;
    bool isWin;
    vector<iii> gate; // pair<<vị trí (x, y)>, giá trị>
    vector<iii> teleport;
    vector<Point> landMines;
    bool updated;
};

struct State
{
    int numRow, numCol;         // size of saved board (8bytes)
};

struct Player
{
    char account[20];			//20bytes
    char password[20];			//20bytes
};

struct User
{
    string fileName;
    // vector<pair<int, int>> bodyOfSnake;
    vector<Point> bodyOfSnake;
    int points;
    int level;
    int direct;
    Player player;
};

//244 = 15*16 + 4 red text white background
const int RW = 244;
//242 = 15*16 + 2 green text white background
const int GreenW = 242;
//240 = 15*16 + 0 black text white background
const int BlackW = 240;
const int boxColor = 2 * 16 + 15;
const int titleColor = 2 * 16 + 15;

//account
//Small Function
bool isExistAcc(string FileName, char username[99], unsigned int& index); //Check if account exists
bool isPasswordCorrect(string FileName, char password[99], unsigned int index);     //Check Password
void getInfo(string FileName, User& oldMan, unsigned int index);
//Big Function
void signUp(string FileName);  // sign up new account
void signIn(string FileName, User& oldMan, unsigned int& index);  //  log in game
void updateScore(string FileName, User& oldMan, unsigned int index, int newscore);
//Choice Sign in or Sign up
void selectAccChoice(int& roundSelect, int& Choice);
void printAccChoice(int Choice);
void generateAccScreen(int& roundSelect, int Choice, string FileName, User& oldMan, unsigned int& index);

//menu
//BIG FUNCTION
// exact menu
void generateMenu(int& roundSelect, int Choice, string FileName);

//SMALL FUNCTION
// function get orders from keyboard
void getEvents(int& roundSelect, int& Choice);
// split up from printMenu, make it easy to change later
void printCredit();
// function show interactive screen 
void printMenu(int roundSelect, int Choice, string FileName);


//printDesgin
//functions used to design screen
HWND WINAPI GetConsoleWindowNT(void);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void clearScreen();
void gotoxy(SHORT x, SHORT y);
void TextColor(int color);
void doTab(int n);

//functions for showing Menu Choice box
void title();
void printSignUpBoard(int directX, int directY);
void printSignInBoard(int directX, int directY);
void printChoiceBox(int directX, int directY);
void deleteChoiceBox(int directX, int directY);
void printMenuBox(int directX, int directY);
void deleteMenuBox(int directX, int directY);
void blinkText(int blinkCount, string str);
void loadingBar();