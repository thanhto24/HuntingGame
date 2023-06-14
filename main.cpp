#include <iostream>
#include <windows.h> //color, gotoxy, ...
#include <conio.h>   //kbhit
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h> //random
#include <fstream>  // file
#include <ctime>

#define ii pair<int, int>
#define iii pair<ii, int>
#define f first
#define s second
#define mp make_pair

using namespace std;

// Dinh nghia: -1 la dau ran, -2, -3, -4, ... la than ran, 'a' la qua tao, 'A' la qua tao to, 1 la tuong |, 2 la tuong -
// 3->6 la huong xuat phat ban dau, lần lượt là trái phải trên dưới. Vd: ô a[5][6] = 4, có nghĩa là rắn được spawn ở ô (5,6) và đi sang phải
// Dinh nghia: 9 la tường của cổng, chỉ xuất hiện khi sắp qua màn. 10 -> 13 la cổng, chứa hướng cần đi để vào :V. ví dụ
// 00 00 00 00 00 00
// 00 09 09 09 09 00
// 00 00 00 00 11 00
// 00 09 09 09 09 00
// 00 00 00 00 00 00

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

void set_cursor(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

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
};

struct Board
{
    bool game_active;
    int **viewBoard;
    int hei, wid;
    int level;
    int hh, mm, ss;
    bool haveBigApple;
    int score;
    int scoreToPass;
    bool isWin;
    vector<iii> gate;
    bool updated;
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
            if (board.viewBoard[i][j] >= 3 && board.viewBoard[i][j] <= 6)
            {
                setValue(spawnPoint, mp(i, j));
                snake.direction = board.viewBoard[i][j] - 3;
            }
            if (board.viewBoard[i][j] >= 9 && board.viewBoard[i][j] <= 13)
            {
                board.gate.push_back(mp(mp(i, j), board.viewBoard[i][j]));
                board.viewBoard[i][j] = 0;
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
    snake.feed = false;

    time_t now = time('\0');
    tm *t = localtime(&now);
    board.mm = t->tm_min;
    board.ss = t->tm_sec;
    board.hh = t->tm_hour;

    board.haveBigApple = false;
    board.score = snake.body.size() * 100;
    board.isWin = false;
    board.scoreToPass = (board.hei + board.wid) * 20 * board.level;
    board.updated = false;
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
            if (direct != 2)
                direct = 3;
    }
    return direct;
}

void updateBoard(Board &board)
{
    for (int i = 0; i < board.gate.size(); i++)
    {
        int I = board.gate[i].f.f, J = board.gate[i].f.s;
        board.viewBoard[I][J] = board.gate[i].s;
    }
    board.updated = true;
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
    {
        snake.feed = true;
        board.score += 100;
    }
    if (board.viewBoard[snake.head.y][snake.head.x] == 'A')
    {
        snake.feed = true;
        board.haveBigApple = false;
        board.score += 500;
    }

    if (board.viewBoard[snake.head.y][snake.head.x] == 1 || board.viewBoard[snake.head.y][snake.head.x] == 2 || board.viewBoard[snake.head.y][snake.head.x] <= -1)
        return void(board.game_active = false);
    if (board.score >= board.scoreToPass || board.updated)
    {
        if (!board.updated)
            updateBoard(board);
        if (board.viewBoard[snake.head.y][snake.head.x] == 9)
            return void(board.game_active = false);
        if (board.viewBoard[snake.head.y][snake.head.x] >= 10 && board.viewBoard[snake.head.y][snake.head.x] <= 13)
        {
            if (board.viewBoard[snake.head.y][snake.head.x] % 10 == snake.direction)
                return void(board.isWin = true);
            return void(board.game_active = false);
        }
    }
    setValue(snake.body[0], snake.head);

    board.viewBoard[snake.head.y][snake.head.x] = -1;
}

const int snakeColor = 5;
const int appleColor = 4;
const int bigAppleColor = 6;
const int wallColor = 9;
const int gateColor = 3;
const int basicColor = 7;
const int backgroundColor = 10;

void draw(const Snake snake, const Board board)
{
    gotoxy(0, 3);
    for (int i = 0; i < board.hei; i++)
    {
        for (int j = 0; j < board.wid; j++)
        {
            // cout << board.viewBoard[i][j] << ' ';
            if (board.viewBoard[i][j] < 0)
            {
                TextColor(snakeColor);
                cout << MSSV[board.viewBoard[i][j] * -1] << ' ';
            }
            else if (board.viewBoard[i][j] == 'a')
            {
                TextColor(appleColor);
                cout << "a ";
            }
            else if (board.viewBoard[i][j] == 'A')
            {
                TextColor(bigAppleColor);
                cout << "A ";
            }
            else if (board.viewBoard[i][j] == 1)
            {
                TextColor(wallColor);
                cout << "|";
            }
            else if (board.viewBoard[i][j] == 2)
            {
                TextColor(wallColor);
                cout << "- ";
            }
            else if (board.viewBoard[i][j] >= 9 && board.viewBoard[i][j] <= 13)
            {
                TextColor(gateColor);
                cout << "O ";
            }
            else
            {
                TextColor(backgroundColor);
                cout << "w ";
            }
            TextColor(basicColor);
        }
        cout << endl;
    }
    // gotoxy(0, 40);
    // for (int i = 0; i < snake.body.size(); i++)
    //     cout << snake.body[i].y << ' ' << snake.body[i].x << endl;
    // cout << snake.tail.y << ' ' << snake.tail.x << endl;
}

bool outRangeGate(int y, int x, const Board board)
{
    int sz = board.gate.size();
    int minX = board.gate[0].f.s, minY = board.gate[0].f.f;
    int maxX = board.gate[sz - 1].f.s, maxY = board.gate[sz - 1].f.s;
    if (y >= minY - 1 && y <= maxY + 1)
        if (x >= minX - 1 && x <= maxX + 1)
            return false;
    return true;
}

void spawnApple(Board &board, bool isBigApple)
{
    int tmpX = 0, tmpY = 0;
    tmpX = rand() % board.wid;
    tmpY = rand() % board.hei;
    while (board.viewBoard[tmpY][tmpX] != 0 && outRangeGate(tmpY, tmpX, board))
    {
        tmpX = rand() % board.wid;
        tmpY = rand() % board.hei;
    }
    if (!isBigApple)
        board.viewBoard[tmpY][tmpX] = 'a';
    else
    {
        board.viewBoard[tmpY][tmpX] = 'A';
        board.haveBigApple = isBigApple;
    }
}

void eatAndGrown(Snake &snake, const Board board)
{
    if (snake.feed)
        snake.body.push_back(snake.tail);
    snake.feed = false;
}

int secondPassed(int h, int m, int s, int &preS, int &score)
{
    int h1, m1, s1;
    time_t now = time('\0');
    tm *t = localtime(&now);
    h1 = t->tm_hour;
    m1 = t->tm_min;
    s1 = t->tm_sec;

    if (s1 != preS)
    {
        score -= 5;
        score = max(score, 0);
        preS = s1;
        return (h1 - h) * 3600 + (m1 - m) * 60 + (s1 - s);
    }
    return -1;
}

const int frequencyOfApple = 4;
const int numToSpawnBigApple = 4;

void deleteObj(Snake &snake, Board &board)
{
    for (int i = 0; i < board.hei; i++)
        delete[] board.viewBoard[i];
    delete[] board.viewBoard;

    snake.body.clear();

    board.gate.clear();
}

void process(Snake &snake, Board &board)
{
    int preS = board.ss;
    while (board.game_active)
    {
        snake.direction = getDirection(snake);
        move(snake, board);
        if (!board.game_active || board.isWin)
            break;
        draw(snake, board);
        if (secondPassed(board.hh, board.mm, board.ss, preS, board.score) % frequencyOfApple == 0)
            if (snake.body.size() >= 3 * numToSpawnBigApple / 2 && snake.body.size() % numToSpawnBigApple == 0 && !board.haveBigApple)
                spawnApple(board, 1);
            else
                spawnApple(board, 0);
        if (!board.score)
            break;
        eatAndGrown(snake, board);
        cout << board.score << " / " << board.scoreToPass << endl;
    }
    // system("cls");
    // gotoxy(5, 5);
    if (board.isWin)
        cout << "CONGRATULATION!";
    else
        cout << "You are loser!";
    deleteObj(snake, board);
}

int main()
{
    Board board;
    Snake snake;
    set_cursor(false);
    init(snake, board);
    process(snake, board);
    return 0;
}