#include "header.h"
/*

// Dinh nghia: -1 la dau ran, -2, -3, -4, ... la than ran, 'a' la qua tao, 'A' la qua tao to, 1 la tuong |, 2 la tuong -
// 3->6 la huong xuat phat ban dau, lần lượt là trái phải trên dưới. Vd: ô a[5][6] = 4, có nghĩa là rắn được spawn ở ô (5,6) và đi sang phải
// Dinh nghia: 9 la tường của cổng, chỉ xuất hiện khi sắp qua màn. 10 -> 13 la cổng, chứa hướng cần đi để vào :V. ví dụ
// 00 00 00 00 00 00
// 00 09 09 09 09 00
// 00 00 00 00 11 00
// 00 09 09 09 09 00
// 00 00 00 00 00 00

const char MSSV[] = " 22127174221273222212738822127441";
*/
/*void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    RECT windowRect;
    GetWindowRect(consoleWindow, &windowRect);

    int width = 1080;
    int height = 500;

    MoveWindow(consoleWindow, windowRect.left, windowRect.top, width, height, TRUE);
}*/

void set_cursor(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void setValue(Point& a, ii b)
{
    a.x = b.s;
    a.y = b.f;
    return;
}

void setValue(Point& a, const Point b)
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

User getUser(string line, bool accountLogedIn, User oldman)
{
    User user;
    stringstream s(line);
    string buf;

    if (accountLogedIn) {
        getline(s, buf, ',');
        if (oldman.player.account != buf.c_str())
            return user;
    }
    getline(s, buf, ',');
    user.fileName = buf;

    getline(s, buf, '(');
    getline(s, buf, ')');
    string coordinates = buf;
    stringstream _s(coordinates);
    int len = coordinates.length();

    Point temp;
    while (len)
    {
        getline(_s, buf, '{'); len--;
        getline(_s, buf, ','); len--; len -= buf.length();
        temp.x = atoi(buf.c_str());
        getline(_s, buf, '}'); len--; len -= buf.length();
        temp.y = atoi(buf.c_str());
        user.bodyOfSnake.push_back(temp);
        temp = { 0, 0 };
    }

    getline(s, buf, ',');
    getline(s, buf, ',');
    user.points = atoi(buf.c_str());
 
    getline(s, buf, ',');
    user.level = atoi(buf.c_str());

    getline(s, buf, '\n');
    user.direct = atoi(buf.c_str());

    return user;
}

void init(Snake& snake, Board& board, Point& startPoint, int Direct)
{
    Point spawnPoint;
    //string address = "Level/";
    string address = intToString(board.level);
    address += ".txt";
    ifstream fin(address.c_str());
    fin >> board.hei >> board.wid;
    board.viewBoard = new int* [board.hei];
    for (int i = 0; i < board.hei; i++)
        board.viewBoard[i] = new int[board.wid];

    for (int i = 0; i < board.hei; i++)
    {
        for (int j = 0; j < board.wid; j++)
        {
            fin >> board.viewBoard[i][j];
            if (board.viewBoard[i][j] >= 3 && board.viewBoard[i][j] <= 6)
            {
                if (startPoint.x != -1 && startPoint.y != -1)
                {
                    snake.direction = Direct;
                    if (Direct == 0)
                        setValue(spawnPoint, mp(startPoint.y, startPoint.x + 1));
                    else if (Direct == 1)
                        setValue(spawnPoint, mp(startPoint.y, startPoint.x - 1));
                    else if (Direct == 2)
                        setValue(spawnPoint, mp(startPoint.y + 1, startPoint.x));
                    else if (Direct == 3)
                        setValue(spawnPoint, mp(startPoint.y - 1, startPoint.x));
                }
                else
                {
                    setValue(spawnPoint, mp(i, j));
                    snake.direction = board.viewBoard[i][j] - 3;
                }
            }
            if (board.viewBoard[i][j] >= 9 && board.viewBoard[i][j] <= 13)
            {
                board.gate.push_back(mp(mp(i, j), board.viewBoard[i][j]));
                board.viewBoard[i][j] = 0;
            }
            if (board.viewBoard[i][j] >= 29 && board.viewBoard[i][j] <= 33)
            {
                board.teleport.push_back(mp(mp(i, j), board.viewBoard[i][j]));
            }
            if (board.viewBoard[i][j] == 99)
            {
                Point temp; temp.x = i; temp.y = j;
                board.landMines.push_back(temp);
            }
        }
    }
    fin.close();
    board.game_active = true;
    setValue(snake.head, spawnPoint);
    snake.body.push_back(snake.head);

    Point nextPoint;
    int x_direct[4] = { -1, 1, 0, 0 };
    int y_direct[4] = { 0, 0, -1, 1 };
    for (int i = 1; i <= 5; i++)
    {
        setValue(nextPoint, mp(spawnPoint.y - i * y_direct[snake.direction], spawnPoint.x - i * x_direct[snake.direction]));
        snake.body.push_back(nextPoint);
    }

    board.viewBoard[snake.head.y][snake.head.x] = -1;

    for (int i = 1; i < snake.body.size(); i++)
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    setValue(snake.tail, snake.body[snake.body.size() - 1]);
    snake.feed = false;

    time_t now = time(NULL);
    tm* t = localtime(&now);
    board.mm = t->tm_min;
    board.ss = t->tm_sec;
    board.hh = t->tm_hour;

    board.haveBigApple = false;
    board.score = snake.body.size() * 100;
    board.isWin = false;
    board.scoreToPass = 100;
    // board.scoreToPass = 100;
    board.updated = false;
}

vector<User> displayFiles(bool accountLogedIn, User& user)
{
    ifstream ifs("out.txt");
    vector<User> users;

    if (ifs.fail())
    {
        cout << "Error opening file: out.txt" << endl;
        return users;
    }
    else if (!ifs.eof())
    {
        string line;
        while (getline(ifs, line))
        {
            users.push_back(getUser(line, accountLogedIn, user));
            if (users[users.size() - 1].points == -858993460 && users[users.size() - 1].level == -858993460)
                users.pop_back();
        }
    }
    for (int i = 0; i < users.size(); i++) {
            cout << "PLAYER NAME: " << users[i].fileName << " - Scores: " << users[i].points << " - Level: " << users[i].level << endl;
    }
    ifs.close();
    return users;
}

void saveFiles(Snake snake, Board board, User& user, bool accountLogedIn)
{
    bool beFound = false;
    int position = 0;
    string temp_name = user.fileName;
    vector<string> allUsersFromFile;

    ifstream ifs("out.txt");

    if (ifs.fail())
    {
        cout << "Error opening file: out.txt" << endl;
        return;
    }
    if (!ifs.eof())
    {
        string line;
        while (getline(ifs, line))
        {
            allUsersFromFile.push_back(line);
            stringstream ss(line);
            string buf;
            getline(ss, buf, ',');
            if (buf == temp_name)
                beFound = true;
            if (!beFound)
                position++;
        }
    }
    ifs.close();

    int size = allUsersFromFile.size();

    if (!beFound)
        size++;

    ofstream ofs;
    ofs.open("out.txt");

    if (ofs.fail())
    {
        cout << "Error opening file: out.txt" << endl;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (i != position)
            ofs << allUsersFromFile[i] << endl;
        else
        {
            //if (accountLogedIn)
                //AI DO TIM CACH KHI CO TAI KHAON DANG NHAP THI LUU RA .TXT LA AKILE,akiLe,({12,17}{11,17}),140,5,1 VOI AKILE LA TEN TAI KHOAN DI
                //TEN TAI KHOAN LUU O user.player.account dang char[20]
                //ofs << user.player.account;
            ofs << user.fileName << ",(";
            for (int i = 0; i < snake.body.size(); i++)
                ofs << "{" << snake.body[i].x << "," << snake.body[i].y << "}";

            ofs << ")," << board.score << "," << board.level << "," << snake.direction << endl;
        }
    }
    ofs.close();
}

void pauseGame()
{
    for (int i = 0; i < 20; i++)
    {
        gotoxy(35, i + 6);
        for (int j = 0; j < 50; j++)
        {
            TextColor(227);
            cout << ".";
        }
        cout << endl;
    }
    TextColor(14);
    gotoxy(35, 6);
    cout << "Press (Z) to save file, or press WASD to continue.";
}

int getDirection(Snake snake, bool isPausing, Board board, User user, bool accountLogedIn)
{
    int direct = snake.direction;
    if (snake.body.size() == 1)
        saveFiles(snake, board, user, accountLogedIn);
    if (kbhit()) // Kiem tra nhan keyboard
    {
        char key = getch(); // Lay key

        if (tolower(key) != 'p')
        {
            if (toupper(key) == 'A' || key == 75 || key == 37)// Di chuyển trái
            {
                PlaySound(TEXT("soundtrack\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (direct != 1)
                    direct = 0;
            }
            if (toupper(key) == 'D' || key == 77 || key == 39) // Di chuyển phải
            {
                PlaySound(TEXT("soundtrack\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (direct != 0)
                    direct = 1;
            }
            if (toupper(key) == 'W' || key == 72 || key == 38) // Di chuyển lên
            {
                PlaySound(TEXT("soundtrack\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (direct != 3)
                    direct = 2;
            }
            if (toupper(key) == 'S' || key == 80 || key == 40) // Di chuyển xuống
            {
                PlaySound(TEXT("soundtrack\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (direct != 2)
                    direct = 3;
            }
        }
        if (tolower(key) == 'p' && !isPausing) // Nh?n p d? pause game
        {
            pauseGame();
            char _key = getch();
            if (toupper(_key) == 'Z')
            {
                PlaySound(TEXT("soundtrack\\enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                saveFiles(snake, board, user, accountLogedIn);
            }
            direct = 112;
        }
    }
    return direct;
}

void updateBoard(Board& board)
{
    for (int i = 0; i < board.gate.size(); i++)
    {
        int I = board.gate[i].f.f, J = board.gate[i].f.s;
        if (board.viewBoard[I][J] != 0)
            return;
    }
    for (int i = 0; i < board.gate.size(); i++)
    {
        int I = board.gate[i].f.f, J = board.gate[i].f.s;
        board.viewBoard[I][J] = board.gate[i].s;
    }
    board.updated = true;
}

void move(Snake& snake, Board& board, Point& startPoint)
{

    board.viewBoard[snake.body[snake.body.size() - 1].y][snake.body[snake.body.size() - 1].x] = 0;
    setValue(snake.tail, snake.body[snake.body.size() - 1]);

    for (int i = snake.body.size() - 1; i > 0; i--)
    {
        setValue(snake.body[i], snake.body[i - 1]);
        board.viewBoard[snake.body[i].y][snake.body[i].x] = -1 * (i % (strlen(MSSV) - 1) + 1);
    }

    int x_direct[4] = { -1, 1, 0, 0 };
    int y_direct[4] = { 0, 0, -1, 1 };

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

    // Teloport Gate
    if (board.viewBoard[snake.head.y][snake.head.x] == 29)
        return void(board.game_active = false);
    if (board.viewBoard[snake.head.y][snake.head.x] >= 30 && board.viewBoard[snake.head.y][snake.head.x] <= 33)
    {
        if (board.viewBoard[snake.head.y][snake.head.x] % 10 == snake.direction)
        {
            // cout << snake.direction << " " << board.viewBoard[snake.head.y][snake.head.x] % 10 << endl;
            // return;
            if (snake.direction >= 0 && snake.direction <= 1)
            {
                // cout << "hhh!" << endl;
                if (snake.head.x == board.teleport[2].first.second)
                {
                    snake.head.x = board.teleport[7].first.second + 1;
                    snake.head.y = board.teleport[7].first.first;
                }
                else if (snake.head.x == board.teleport[7].first.second)
                {
                    snake.head.x = board.teleport[2].first.second - 1;
                    snake.head.y = board.teleport[2].first.first;
                }
            }
            else if (snake.direction >= 2 && snake.direction <= 3)
            {
                if (snake.head.y == board.teleport[2].first.first)
                {
                    // cout << "YYY" << endl;
                    snake.head.x = board.teleport[7].first.second - 1;
                    snake.head.y = board.teleport[7].first.first + 1;
                }
                else if (snake.head.y == board.teleport[7].first.first)
                {
                    // cout << "NNN" << endl;
                    snake.head.x = board.teleport[2].first.second + 1;
                    snake.head.y = board.teleport[2].first.first - 1;
                }
            }
        }
        else
        {
            return void(board.game_active = false);
        }
    }
    // dinh boom
    if (board.viewBoard[snake.head.y][snake.head.x] == 99)
    {
        int len = snake.body.size() / 2;
        snake.turnRed = true;

        PlaySound(TEXT("soundtrack\\wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
        for (int i = 0; i <= len; i++)
        {
            board.viewBoard[snake.body[snake.body.size() - 1].y][snake.body[snake.body.size() - 1].x] = 0;
            board.score -= 100;
            snake.body.pop_back();
        }
    }
    if (board.score >= board.scoreToPass || board.updated)
    {
        startPoint = { -1, -1 };
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

int snakeColor = 14;
const int appleColor = 221;
const int bigAppleColor = 238;
const int wallColor = 68;
const int gateColor = 3;
const int basicColor = 7;
const int backgroundColor = 114;
const int teleportGateColor = 176;
const int landMineColor = 16;

void draw(const Snake snake, const Board board)
{
    gotoxy(0, 0);
    for (int i = 0; i < board.hei; i++)
    {
        for (int j = 0; j < board.wid; j++)
        {
            //  cout << board.viewBoard[i][j] << ' ';
            if (board.viewBoard[i][j] < 0)
            {
                if (snake.turnRed)
                    TextColor(wallColor);
                else
                    TextColor(snakeColor);
                cout << MSSV[board.viewBoard[i][j] * -1] << ' ';
            }
            else if (board.viewBoard[i][j] == 'a')
            {
                TextColor(appleColor);
                cout << "  ";
            }
            else if (board.viewBoard[i][j] == 'A')
            {
                TextColor(bigAppleColor);
                cout << "  ";
            }
            else if (board.viewBoard[i][j] == 1)
            {
                TextColor(wallColor);
                SetConsoleOutputCP(65001);
                cout << "║║";
            }
            else if (board.viewBoard[i][j] == 2)
            {
                TextColor(wallColor);
                SetConsoleOutputCP(65001);
                cout << "══";
            }
            else if (board.viewBoard[i][j] >= 9 && board.viewBoard[i][j] <= 13)
            {
                TextColor(gateColor);
                cout << "O ";
            }
            else if (board.viewBoard[i][j] >= 29 && board.viewBoard[i][j] <= 33)
            {
                TextColor(teleportGateColor);
                cout << "  ";
            }
            else if (board.viewBoard[i][j] == 99)
            {
                TextColor(landMineColor);
                cout << "  ";
            }
            else
            {
                TextColor(backgroundColor);
                cout << "W ";
            }
            TextColor(basicColor);
        }
        cout << endl;
    }
    SetConsoleOutputCP(65001);
    TextColor(15 * 16 + 0);
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                      VIETNAM NATIONAL UNIVERSITY IN HO CHI MINH CITY                                 ║" << endl;
    cout << "║                                              HO CHI MINH UNIVERSITY OF SCIENCE                                       ║" << endl;
    cout << "║                                               PROGRAMMING TECHNIQUES COURSES                                         ║" << endl;
    cout << "║                                                 HUNTING SNAKE GAME PROJECT                                           ║" << endl;
    cout << "║                                             PRODUCED BY STUDENTS FROM GROUP 02                                       ║" << endl;
    cout << "║                                                      * * * * * * * * *                                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
    gotoxy(120, 0);
    cout << "╔══════════════════════════════════╗" << endl;
    gotoxy(120, 1);
    cout << "║                                  ║" << endl;
    gotoxy(120, 2);
    cout << "║            ";
    gotoxy(135, 2);
    TextColor(15 * 16 + 12);
    cout << "GROUP 02";
    gotoxy(143, 2);
    TextColor(15 * 16 + 0);
    cout << "            ║" << endl;
    gotoxy(120, 3);
    cout << "║                                  ║" << endl;
    gotoxy(120, 4);
    cout << "║     22127174: NGO VAN KHAI       ║" << endl;
    gotoxy(120, 5);
    cout << "║     22127322: LE PHUOC PHAT      ║" << endl;
    gotoxy(120, 6);
    cout << "║     22127388: TO QUOC THANH      ║" << endl;
    gotoxy(120, 7);
    cout << "║     22127441: THAI HUYEN TUNG    ║" << endl;
    gotoxy(120, 8);
    cout << "║                                  ║" << endl;
    gotoxy(120, 9);
    cout << "╠══════════════════════════════════╣" << endl;
    gotoxy(120, 10);
    cout << "║                                  ║" << endl;
    gotoxy(120, 11);
    cout << "║           " << endl;
    gotoxy(133, 11);
    TextColor(15 * 16 + 12);
    cout << "INSTRUCTIONS";
    TextColor(15 * 16 + 0);
    gotoxy(144, 11);
    cout << "           ║" << endl;
    gotoxy(120, 12);
    cout << "║                                  ║" << endl;
    gotoxy(120, 13);
    cout << "║         W  or  ↑ : GO UP         ║" << endl;
    gotoxy(120, 14);
    cout << "║         A  or  → : TURN LEFT     ║" << endl;
    gotoxy(120, 15);
    cout << "║         S  or  ↓ : GO DOWN       ║" << endl;
    gotoxy(120, 16);
    cout << "║         D  or  ← : TURN RIGHT    ║" << endl;
    gotoxy(120, 17);
    cout << "║                                  ║" << endl;
    gotoxy(120, 18);
    cout << "╠══════════════════════════════════╣" << endl;
    gotoxy(120, 19);
    cout << "║                                  ║" << endl;
    gotoxy(120, 20);
    cout << "║        ";
    gotoxy(129, 20);
    TextColor(15 * 16 + 12);
    cout << "CACULATING  SCORES";
    gotoxy(147, 20);
    TextColor(15 * 16 + 0);
    cout << "        ║" << endl;
    gotoxy(120, 21);
    cout << "║                                  ║" << endl;
    gotoxy(120, 22);
    cout << "║    TOTAL SCORES: 100 / 100       ║" << endl;
    gotoxy(120, 23);
    cout << "║                                  ║" << endl;
    gotoxy(120, 25);
    cout << "║                                  ║" << endl;
    gotoxy(120, 26);
    cout << "╠══════════════════════════════════╣" << endl;
    gotoxy(120, 27);
    cout << "║                                  ║" << endl;
    gotoxy(120, 28);
    cout << "║              ";
    gotoxy(135, 28);
    TextColor(15 * 16 + 12);
    cout << "RESULT";
    gotoxy(141, 28);
    TextColor(15 * 16 + 0);
    cout << "              ║" << endl;
    gotoxy(120, 29);
    cout << "║                                  ║" << endl;
    gotoxy(120, 31);
    cout << "║                                  ║" << endl; 
    gotoxy(120, 32);
    cout << "╠══════════════════════════════════╣" << endl;
    gotoxy(120, 33);
    cout << "║                                  ║" << endl;
    gotoxy(120, 36);
    cout << "║                                  ║" << endl;
    gotoxy(120, 37);
    cout << "╚══════════════════════════════════╝" << endl;
    gotoxy(0, 33);
}

bool outRangeGate(int y, int x, const Board board)
{
    int sz = board.gate.size();
    int minX = board.gate[0].f.s, minY = board.gate[0].f.f;
    int maxX = board.gate[sz - 1].f.s, maxY = board.gate[sz - 1].f.f; // sua lai tu .f.s -> .f.f
    if (y >= minY - 1 && y <= maxY + 1)
        if (x >= minX - 1 && x <= maxX + 1)
            return false;
    return true;
}

bool outRangeTeleport(int y, int x, const Board board)
{
    int minX_1 = board.teleport[0].f.s, minY_1 = board.teleport[0].f.f;
    int maxX_1 = board.teleport[4].f.s, maxY_1 = board.teleport[4].f.f;
    int minX_2 = board.teleport[5].f.s, minY_2 = board.teleport[5].f.f;
    int maxX_2 = board.teleport[9].f.s, maxY_2 = board.teleport[9].f.f;
    if ((y >= minY_1 - 1 && y <= maxY_1 + 1) || (y >= minY_2 - 1 && y <= maxY_2 + 1))
        if ((x >= minX_1 - 1 && x <= maxX_1 + 1) || (x >= minX_2 - 1 && x <= maxX_2 + 1))
            return false;
    return true;
}

bool outRangeLandmine(int y, int x, const Board board)
{
    int sz = board.landMines.size();
    for (int i = 0; i < sz; i++)
        if (y == board.landMines[i].y || x == board.landMines[i].x)
            return false;
    return true;
}

void spawnApple(Board& board, bool isBigApple)
{
    int tmpX = 0, tmpY = 0;
    tmpX = rand() % board.wid;
    tmpY = rand() % board.hei;
    while (board.viewBoard[tmpY][tmpX] != 0 || !outRangeGate(tmpY, tmpX, board) && outRangeTeleport(tmpY, tmpX, board) && outRangeLandmine(tmpX, tmpY, board))
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

void eatAndGrown(Snake& snake, const Board board)
{
    if (snake.feed)
    {
        snake.body.push_back(snake.tail);
        PlaySound(TEXT("soundtrack\\Hint.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    snake.feed = false;
}

int secondPassed(int h, int m, int s, int& preS, int& score)
{
    int h1, m1, s1;
    time_t now = time(NULL);
    tm* t = localtime(&now);
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

void deleteObj(Snake& snake, Board& board)
{
    for (int i = 0; i < board.hei; i++)
        delete[] board.viewBoard[i];
    delete[] board.viewBoard;

    snake.body.clear();

    board.gate.clear();
}

void process(Snake& snake, Board& board, User user, Point& startPoint, bool accountLogedIn)
{
    int preS = board.ss;
    bool isPausing = false;

    while (board.game_active)
    {
        snake.direction = getDirection(snake, isPausing, board, user, accountLogedIn);
        if (snake.direction != 112)
        {
            gotoxy(120, 30);
            cout << "║         STILL WAITING ...        ║" << endl;
            isPausing = false;
            move(snake, board, startPoint);
            if (!board.game_active || board.isWin)
                break;
            draw(snake, board);
            snake.turnRed = false;
            if (secondPassed(board.hh, board.mm, board.ss, preS, board.score) % frequencyOfApple == 0)
                if (snake.body.size() >= 3 * numToSpawnBigApple / 2 && snake.body.size() % numToSpawnBigApple == 0 && !board.haveBigApple)
                    spawnApple(board, 1);
                else
                    spawnApple(board, 0);
            if (!board.score)
                break;
            eatAndGrown(snake, board);
            gotoxy(120, 24);
            if (board.score >= 0 && board.score < 10)
                cout << "║    CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "       ║" << endl;
            else if (board.score >= 10 && board.score <= 99)
                cout << "║    CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "      ║" << endl;
            else if (board.score >= 100 && board.score <= 999)
                cout << "║    CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "     ║" << endl;
            else if (board.score >= 1000 && board.score <= 9999)
                cout << "║    CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "    ║" << endl;
            else if (board.score >= 10000 && board.score <= 99999)
                cout << "║    CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "   ║" << endl;
            else
                cout << "║   CURRENT SCORES: " << board.score << " / " << board.scoreToPass << "   ║" << endl;
        }
        else
        {
            gotoxy(120, 30);
            cout << "║         STILL WAITING ...        ║" << endl;
            isPausing = true;
        }
    }
    gotoxy(120, 30);
    if (board.isWin)
    }
        cout << "║         YOU ARE A WINNER         ║" << endl;
        PlaySound(TEXT("soundtrack\\win.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    else
    {
        
        // for (int i = 0; i < 10; i++)
        // {
        //     Sleep(10);
        //     snakeColor = 20;
        //     draw(snake, board);
        //     snakeColor = 14;
        //     draw(snake, board);
        // }
        // startPoint = {-1, -1};
        string str = "║         YOU ARE A LOSER          ║";
        // blinkText(5, str);
        cout << str << endl;
        board.level = 1;
        board.score = 0;
        while (user.bodyOfSnake.size() != 0)
            user.bodyOfSnake.pop_back();

        //Khi chet thi lam board trong
        string address = intToString(board.level);
        address += ".txt";
        ifstream fin(address.c_str());
        int trash1, trash2, temp;
        fin >> trash1 >> trash2;
        for (int i = 0; i < board.hei; i++)
        {
            for (int j = 0; j < board.wid; j++)
            {
                fin >> temp;
                board.viewBoard[i][j] = temp;
            }
        }
        fin.close();

        while (snake.body.size() != 0)
            snake.body.pop_back();
        snake.head = { 5, 5 };
        snake.body.push_back({ 5, 5 });
        startPoint = snake.head;
        user.direct = 1; 
        saveFiles(snake, board, user, accountLogedIn);
        PlaySound(TEXT("soundtrack\\lose.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    }
    deleteObj(snake, board);
}

int main() {
    int roundSelect = 1, Choice = 1;
    int* pChoice = &Choice;
    User user;
    bool accountLogedIn = true;
    string FileName = "SaveFile.dat";
    unsigned int index = 0;
    Board board;
    Snake snake;
    Point startPoint = { -1,  -1 };
    loadingBar();
    clearScreen();

    system("color f0");
    TextColor(BlackW);
    gotoxy(79, 38);
    cout << "Use arrow key to move.";
    gotoxy(78, 39);
    cout << "Press ENTER for choosing.";
    generateAccScreen(roundSelect, Choice, FileName, user, index);

    if (roundSelect == -1)
        accountLogedIn = false;

    //Truong hop khong dang nhap
    if (!accountLogedIn) {
        board.level = 1;
        board.score = 0;
        snake.head = { 5, 5 };
        snake.body.push_back({ 5, 5 });
        startPoint = snake.head;
        user.direct = 1;
    }
    //Truong hop tao tai khoan
    else if (accountLogedIn && user.bodyOfSnake.size() == 0) {
        board.level = user.level = 1;
        board.score = user.points = 0;
        snake.head = { 5, 5 };
        snake.body = user.bodyOfSnake;
        startPoint = snake.head;
        user.direct = 1;
    }
    //Truong hop da choi tu truoc
    else {
        board.level = user.level;
        board.score = user.points;
        snake.head = user.bodyOfSnake[0];
        user.bodyOfSnake.erase(user.bodyOfSnake.begin());
        snake.body = user.bodyOfSnake;
        startPoint = snake.head;
    }

    //bien dat ra de tranh bug
    bool firstTime = true;

    while (1) {
        system("color f0");
        int scoreWhenOutGame = 0;
        generateMenu(roundSelect, Choice, FileName);

        //Thanh To
        clearScreen();
        system("color f0");
        bool isNewUser = true;
        vector<User> users = displayFiles(accountLogedIn, user);
        User user;
        cout << "Nhap ten FILE: "; getline(cin, user.fileName);

        set_cursor(false);

        ifstream ifs("out.txt");
        if (ifs.fail())
            return 0;
        else if (!accountLogedIn)
        {
            int n = users.size();
            for (int i = 0; i < n; i++)
            {
                if (user.fileName == users[i].fileName)
                {
                    isNewUser = false;
                    user = users[i];
                    break;
                }
            }
            if (!isNewUser)
            {
                board.level = user.level;
                board.score = user.points;
                snake.head = user.bodyOfSnake[0];
                user.bodyOfSnake.erase(user.bodyOfSnake.begin());
                snake.body = user.bodyOfSnake;
                startPoint = snake.head;
            }
            else {
                firstTime = true;
                board.level = 1;
                board.score = 0;
                snake.head = { 5, 5 };
                snake.body.push_back({ 5, 5 });
                startPoint = snake.head;
                user.direct = 1;
            }
            ifs.close();
        }
        else if (accountLogedIn)
        {
            int n = users.size();
            for (int i = 0; i < n; i++)
            {
                if (user.fileName == users[i].fileName)
                {
                    isNewUser = false;
                    user = users[i];
                    break;
                }
            }
            if (!isNewUser)
            {
                board.level = user.level;
                board.score = user.points;
                snake.head = user.bodyOfSnake[0];
                user.bodyOfSnake.erase(user.bodyOfSnake.begin());
                snake.body = user.bodyOfSnake;
                startPoint = snake.head;
            }
            else {
                firstTime = true;
                board.level = 1;
                board.score = 0;
                snake.head = { 5, 5 };
                snake.body.push_back({ 5, 5 });
                startPoint = snake.head;
                user.direct = 1;
            }
            ifs.close();
        }
        while (1) {
            clearScreen();
            system("color f0");
            board.game_active = true;
            SetConsoleOutputCP(65001);
            gotoxy(120, 34);
            cout << "║            ";
            gotoxy(134, 34);
            TextColor(15 * 16 + 12);
            cout << "CURRENT LEVEL";
            gotoxy(147, 34);
            TextColor(15 * 16 + 0);
            cout << "        ║" << endl;
            gotoxy(120, 35);
            if (board.level < 10)
                cout << "║                  0" << board.level << "              ║" << endl;
            else
                cout << "║                  " << board.level << "               ║" << endl;
            init(snake, board, startPoint, user.direct);
            process(snake, board, user, startPoint, accountLogedIn);

            //Neu choi thang
            if (board.isWin)
                board.level++;

            //Neu choi dang Guest thi luc moi vao choi chtr se thong bao thua chu ko chay chuong trinh choi nen lam dieu kien tranh
            else if (!board.isWin && firstTime && isNewUser)
                firstTime = false;
            //else if (!board.isWin && !firstTime){
            //Neu choi thua
            else {
                if (!accountLogedIn)
                    board.level = 1;
                gotoxy(120, 34);
                cout << "║      Press (Z) to SAVE FILE      ║" << endl;
                gotoxy(120, 35);
                cout << "║      Other keys to BACK MENU     ║" << endl;
                char _key = getch();
                if (toupper(_key) == 'Z')
                {
                    PlaySound(TEXT("soundtrack\\enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    saveFiles(snake, board, user, accountLogedIn);
                }
                break;
            }
        }
    }
    return 0;
}