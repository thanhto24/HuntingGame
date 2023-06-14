<<<<<<< HEAD
#include <iostream>
#include <windows.h> //color, gotoxy, ...
#include <conio.h>   //kbhit
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h> //random
#include <fstream>  // file

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

using namespace std;

// Dinh nghia: -1 la dau ran, -1 la than ran, 'a' la qua tao, 1 la tuong |, 2 la tuong -

const char MSSV[] = " 388400414212";

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

struct Point
{
    int x, y;
};

struct Snake
{
    vector<Point> body;
    Point head, willHead, tail;
    int direction;
    int length;
    bool feed;
};

struct Board
{
    bool game_active;
    int **viewBoard;
    int hei, wid;
    int level;
};

void setValue(Point &a, ii b)
{
    a.x = b.s;
    a.y = b.f;
    return;
}

void setValue(Point &a, const Point b)
{
    a.x = b.x;
    a.y = b.y;
    return;
}

string intToString(int x)
{
    string res = "";
    while (x > 0)
    {
        char tmp = x % 10 + '0';
        res = tmp + res;
        x /= 10;
    }
    return res;
}

void init(Snake &snake, Board &board)
{
    Point spawnPoint;
    board.level = 1;
    string address = "Level/";
    address += intToString(board.level);
    address += ".txt";
    ifstream fin(address.c_str());
    fin >> board.hei >> board.wid;
    board.viewBoard = new int *[board.hei];
    for (int i = 0; i < board.hei; i++)
        board.viewBoard[i] = new int[board.wid];

    for (int i = 0; i < board.hei; i++)
        for (int j = 0; j < board.wid; j++)
        {
            fin >> board.viewBoard[i][j];
            if (board.viewBoard[i][j] > 2)
            {
                setValue(spawnPoint, mp(i, j));
                snake.direction = board.viewBoard[i][j] - 3;
            }
        }
    fin.close();
    board.game_active = true;

    setValue(snake.head, spawnPoint);
    snake.body.push_back(snake.head);

    setValue(spawnPoint, mp(5, 4));
    snake.body.push_back(spawnPoint);

    setValue(spawnPoint, mp(5, 3));
    snake.body.push_back(spawnPoint);

    setValue(spawnPoint, mp(5, 2));
    snake.body.push_back(spawnPoint);

    board.viewBoard[snake.head.y][snake.head.x] = -1;

    for (int i = 1; i < snake.body.size(); i++)
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    setValue(snake.tail, snake.body[snake.body.size() - 1]);
    snake.length = snake.body.size();
    snake.feed = false;
}

int getDirection(Snake snake)
{
    int direct = snake.direction;
    if (kbhit()) // Kiem tra nhan keyboard
    {
        char key = getch(); // Lay key

        if (toupper(key) == 'A' || key == 75) // Di chuyển trái
            if (direct != 1)
                direct = 0;
        if (toupper(key) == 'D' || key == 77) // Di chuyển phải
            if (direct != 0)
                direct = 1;
        if (toupper(key) == 'W' || key == 72) // Di chuyển lên
            if (direct != 3)
                direct = 2;
        if (toupper(key) == 'S' || key == 80) // Di chuyển xuống
            if (direct != 3)
                direct = 3;
    }
    return direct;
}

void move(Snake &snake, Board &board)
{

    board.viewBoard[snake.body[snake.body.size() - 1].y][snake.body[snake.body.size() - 1].x] = 0;
    setValue(snake.tail, snake.body[snake.body.size() - 1]);

    for (int i = snake.body.size() - 1; i > 0; i--)
    {
        setValue(snake.body[i], snake.body[i - 1]);
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    }

    int x_direct[4] = {-1, 1, 0, 0};
    int y_direct[4] = {0, 0, -1, 1};

    snake.head.x += x_direct[snake.direction];
    snake.head.y += y_direct[snake.direction];

    if (snake.head.x < 0)
        snake.head.x = board.wid - 1;
    if (snake.head.x > board.wid - 1)
        snake.head.x = 0;

    if (snake.head.y < 0)
        snake.head.y = board.hei - 1;
    if (snake.head.y > board.hei - 1)
        snake.head.y = 0;

    if (board.viewBoard[snake.head.y][snake.head.x] == 'a')
        snake.feed = true;
    if (board.viewBoard[snake.head.y][snake.head.x] == 1 || board.viewBoard[snake.head.y][snake.head.x] == 2 || board.viewBoard[snake.head.y][snake.head.x] <= -1)
        return void(board.game_active = false);

    setValue(snake.body[0], snake.head);

    board.viewBoard[snake.head.y][snake.head.x] = -1;
}

void draw(Snake snake, Board board)
{
    gotoxy(0, 3);
    for (int i = 0; i < board.hei; i++)
    {
        for (int j = 0; j < board.wid; j++)
        {
            if (board.viewBoard[i][j] < 0)
            {
                TextColor(5);
                // cout << board.viewBoard[i][j] * -1;
                cout << MSSV[board.viewBoard[i][j] * -1] << ' ';
                TextColor(7);
            }
            else if (board.viewBoard[i][j] == 'a')
            {
                TextColor(4);
                cout << "A ";
                TextColor(7);
            }
            else if (board.viewBoard[i][j] == 1)
                cout << "|";
            else if (board.viewBoard[i][j] == 2)
                cout << "- ";
            else
            {
                TextColor(10);
                cout << "w ";
                TextColor(7);
            }
        }
        cout << endl;
    }
    gotoxy(0, 40);
    // for (int i = 0; i < snake.body.size(); i++)
    //     cout << snake.body[i].y << ' ' << snake.body[i].x << endl;
    // cout << snake.tail.y << ' ' << snake.tail.x << endl;
    Sleep(10);
}

void spawnApple(Board &board)
{
    int tmpX = 0, tmpY = 0;
    tmpX = rand() % board.wid;
    tmpY = rand() % board.hei;
    while (board.viewBoard[tmpY][tmpX] != 0)
    {
        tmpX = rand() % board.wid;
        tmpY = rand() % board.hei;
    }
    board.viewBoard[tmpY][tmpX] = 'a';
}

void eatAndGrown(Snake &snake, Board board)
{
    if (snake.feed)
        snake.body.push_back(snake.tail);
    snake.feed = false;
}

void process(Snake &snake, Board &board)
{
    while (board.game_active)
    {
        snake.direction = getDirection(snake);
        move(snake, board);
        if (!board.game_active)
            break;
        draw(snake, board);
        spawnApple(board);
        eatAndGrown(snake, board);
    }
}

int main()
{
    Board board;
    Snake snake;
    init(snake, board);
    process(snake, board);
    return 0;
=======
#include <iostream>
#include <windows.h> //color, gotoxy, ...
#include <conio.h>   //kbhit
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h> //random
#include <fstream>  // file

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

using namespace std;

// Dinh nghia: -1 la dau ran, -1 la than ran, 'a' la qua tao, 1 la tuong |, 2 la tuong -

const char MSSV[] = " 388400414212";

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

struct Point
{
    int x, y;
};

struct Snake
{
    vector<Point> body;
    Point head, willHead, tail;
    int direction;
    int length;
    bool feed;
};

struct Board
{
    bool game_active;
    int **viewBoard;
    int hei, wid;
    int level;
};

void setValue(Point &a, ii b)
{
    a.x = b.s;
    a.y = b.f;
    return;
}

void setValue(Point &a, const Point b)
{
    a.x = b.x;
    a.y = b.y;
    return;
}

string intToString(int x)
{
    string res = "";
    while (x > 0)
    {
        char tmp = x % 10 + '0';
        res = tmp + res;
        x /= 10;
    }
    return res;
}

void init(Snake &snake, Board &board)
{
    Point spawnPoint;
    board.level = 1;
    string address = "Level/";
    address += intToString(board.level);
    address += ".txt";
    ifstream fin(address.c_str());
    fin >> board.hei >> board.wid;
    board.viewBoard = new int *[board.hei];
    for (int i = 0; i < board.hei; i++)
        board.viewBoard[i] = new int[board.wid];

    for (int i = 0; i < board.hei; i++)
        for (int j = 0; j < board.wid; j++)
        {
            fin >> board.viewBoard[i][j];
            if (board.viewBoard[i][j] > 2)
            {
                setValue(spawnPoint, mp(i, j));
                snake.direction = board.viewBoard[i][j] - 3;
            }
        }
    fin.close();
    board.game_active = true;

    setValue(snake.head, spawnPoint);
    snake.body.push_back(snake.head);

    setValue(spawnPoint, mp(5, 4));
    snake.body.push_back(spawnPoint);

    setValue(spawnPoint, mp(5, 3));
    snake.body.push_back(spawnPoint);

    setValue(spawnPoint, mp(5, 2));
    snake.body.push_back(spawnPoint);

    board.viewBoard[snake.head.y][snake.head.x] = -1;

    for (int i = 1; i < snake.body.size(); i++)
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    setValue(snake.tail, snake.body[snake.body.size() - 1]);
    snake.length = snake.body.size();
    snake.feed = false;
}

int getDirection(Snake snake)
{
    int direct = snake.direction;
    if (kbhit()) // Kiem tra nhan keyboard
    {
        char key = getch(); // Lay key

        if (toupper(key) == 'A' || key == 75) // Di chuyển trái
            if (direct != 1)
                direct = 0;
        if (toupper(key) == 'D' || key == 77) // Di chuyển phải
            if (direct != 0)
                direct = 1;
        if (toupper(key) == 'W' || key == 72) // Di chuyển lên
            if (direct != 3)
                direct = 2;
        if (toupper(key) == 'S' || key == 80) // Di chuyển xuống
            if (direct != 3)
                direct = 3;
    }
    return direct;
}

void move(Snake &snake, Board &board)
{

    board.viewBoard[snake.body[snake.body.size() - 1].y][snake.body[snake.body.size() - 1].x] = 0;
    setValue(snake.tail, snake.body[snake.body.size() - 1]);

    for (int i = snake.body.size() - 1; i > 0; i--)
    {
        setValue(snake.body[i], snake.body[i - 1]);
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    }

    int x_direct[4] = {-1, 1, 0, 0};
    int y_direct[4] = {0, 0, -1, 1};

    snake.head.x += x_direct[snake.direction];
    snake.head.y += y_direct[snake.direction];

    if (snake.head.x < 0)
        snake.head.x = board.wid - 1;
    if (snake.head.x > board.wid - 1)
        snake.head.x = 0;

    if (snake.head.y < 0)
        snake.head.y = board.hei - 1;
    if (snake.head.y > board.hei - 1)
        snake.head.y = 0;

    if (board.viewBoard[snake.head.y][snake.head.x] == 'a')
        snake.feed = true;
    if (board.viewBoard[snake.head.y][snake.head.x] == 1 || board.viewBoard[snake.head.y][snake.head.x] == 2 || board.viewBoard[snake.head.y][snake.head.x] <= -1)
        return void(board.game_active = false);

    setValue(snake.body[0], snake.head);

    board.viewBoard[snake.head.y][snake.head.x] = -1;
}

void draw(Snake snake, Board board)
{
    gotoxy(0, 3);
    for (int i = 0; i < board.hei; i++)
    {
        for (int j = 0; j < board.wid; j++)
        {
            if (board.viewBoard[i][j] < 0)
            {
                TextColor(5);
                // cout << board.viewBoard[i][j] * -1;
                cout << MSSV[board.viewBoard[i][j] * -1] << ' ';
                TextColor(7);
            }
            else if (board.viewBoard[i][j] == 'a')
            {
                TextColor(4);
                cout << "A ";
                TextColor(7);
            }
            else if (board.viewBoard[i][j] == 1)
                cout << "|";
            else if (board.viewBoard[i][j] == 2)
                cout << "- ";
            else
            {
                TextColor(10);
                cout << "w ";
                TextColor(7);
            }
        }
        cout << endl;
    }
    gotoxy(0, 40);
    // for (int i = 0; i < snake.body.size(); i++)
    //     cout << snake.body[i].y << ' ' << snake.body[i].x << endl;
    // cout << snake.tail.y << ' ' << snake.tail.x << endl;
    Sleep(10);
}

void spawnApple(Board &board)
{
    int tmpX = 0, tmpY = 0;
    tmpX = rand() % board.wid;
    tmpY = rand() % board.hei;
    while (board.viewBoard[tmpY][tmpX] != 0)
    {
        tmpX = rand() % board.wid;
        tmpY = rand() % board.hei;
    }
    board.viewBoard[tmpY][tmpX] = 'a';
}

void eatAndGrown(Snake &snake, Board board)
{
    if (snake.feed)
        snake.body.push_back(snake.tail);
    snake.feed = false;
}

void process(Snake &snake, Board &board)
{
    while (board.game_active)
    {
        snake.direction = getDirection(snake);
        move(snake, board);
        if (!board.game_active)
            break;
        draw(snake, board);
        spawnApple(board);
        eatAndGrown(snake, board);
    }
}

int main()
{
    Board board;
    Snake snake;
    init(snake, board);
    process(snake, board);
    return 0;
>>>>>>> f21f3d3 (first commit)
}