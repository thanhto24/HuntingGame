#include "showing.h"

//https://www.codeincodeblock.com/2011/03/move-console-windows-using-codeblock.html
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib, TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

//https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
void ShowScrollbar(BOOL Show){
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

//https://cplusplus.com/forum/articles/10515/
void clearScreen(){
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

//https://nguyenvanquan7826.wordpress.com/2013/08/22/cc-gotoxy-trong-dev-c-gotoxy-in-dev-c/
void gotoxy(SHORT x, SHORT y){//y: row, x: col
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

//https://www.codespeedy.com/color-text-output-in-console-in-cpp/
/*
number =
0  : Black
1  : Blue
2  : Green
3  : Cyan
4  : Red
5  : Purple
6  : Yellow(dark)
7  : Default white
8  : Grey
9  : Bright blue
10 : Bright green
11 : Bright cyan
12 : Bright red
13 : Pink
14 : yellow
15 : Bright white

int color = number*16                  +       number
            (this is background color)       (and this is test color)
*/
void TextColor(int color){
    HANDLE colo;
    colo =  GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colo, color);
}

void level2(mainScreen &game){//blocks moving down
    int startCol = 1;
    if(game.col == 12)
        startCol = 5;
    else if(game.col == 18)
        startCol = 2;
    
    int endRow = 1;
    if(game.row == 6)
        endRow = 2;

    for(int j = startCol; j <= game.col + startCol; j++)
        for(int i = min(game.row + endRow - 1, 8); i >= endRow; i--){
            if(game.board[i][j] == -1)
                for(int key = i; key >= endRow; key--)
                    game.board[key][j] = game.board[key - 1][j];
            if(game.board[i][j] == -1)
                for(int key = i; key >= endRow; key--)
                    game.board[key][j] = game.board[key - 1][j];
        }
}

void level3(mainScreen &game){//blocks moving left
    int startCol = 1;
    if(game.col == 12)
        startCol = 5;
    else if(game.col == 18)
        startCol = 2;
    
    int startRow = 1;
    if(game.row == 6)
        startRow = 2;
    
    for(int i = startRow; i <= game.row + startRow - 1; i++)
        for(int j = startCol; j <= game.col + startCol - 1; j++){
            if(game.board[i][j] == -1)
                for(int key = j; key <= game.col + startCol - 1; key++)
                    game.board[i][key] = game.board[i][key + 1];
            if(game.board[i][j] == -1)
                for(int key = j; key <= game.col + startCol - 1; key++)
                    game.board[i][key] = game.board[i][key + 1];
        }
}

void level4(mainScreen &game){//blocks moving up
    int startCol = 1;
    if(game.col == 12)
        startCol = 5;
    else if(game.col == 18)
        startCol = 2;
    
    int startRow = 1;
    if(game.row == 6)
        startRow = 2;
    
    for(int j = startCol; j <= game.col + startCol - 1; j++)
        for(int i = startRow; i <= game.row + startRow - 1; i++){
            if(game.board[i][j] == -1)
                for(int key = i; key <= game.row + startRow - 1; key++)
                    game.board[key][j] = game.board[key + 1][j];
            if(game.board[i][j] == -1)
                for(int key = i; key <= game.row + startRow - 1; key++)
                    game.board[key][j] = game.board[key + 1][j];
        }
}

void level5(mainScreen &game){//blocks moving right
    int endCol = 1;
    if(game.col == 12)
        endCol = 5;
    else if(game.col == 18)
        endCol = 2;
    
    int startRow = 1;
    if(game.row == 6)
        startRow = 2;
    
    for(int i = startRow; i <= game.row + startRow - 1; i++)
        for(int j = min(game.col + endCol - 1, 20); j >= endCol; j--){
            if(game.board[i][j] == -1)
                for(int key = j; key >= endCol; key--)
                    game.board[i][key] = game.board[i][key - 1];
            if(game.board[i][j] == -1)
                for(int key = j; key >= endCol; key--)
                    game.board[i][key] = game.board[i][key - 1];
        }
}

void levelMove(mainScreen &game, int level, int roundSelect){
    if(roundSelect == -1){
        game.row-=2;
        game.col-=8;
    }
    else if(roundSelect == -2){
        game.row-=2;
        game.col-=2;
    }

    if(level == 1){
        //40 = 1*16 + 15 white text blue background
        TextColor(40);
    }
    else if(level == 2){
        //79 = 4*16 + 15 white text red background
        TextColor(79);
        level2(game);
    }
    else if(level == 3){
        //79 = 4*16 + 15 white text red background
        TextColor(79);
        level3(game);
    }
    else if(level == 4){
        //79 = 4*16 + 15 white text red background
        TextColor(79);
        level4(game);
    }
    else if(level == 5){
        //79 = 4*16 + 15 white text red background
        TextColor(79);
        level5(game);
    }
    
    if(roundSelect == -1){
        game.row+=2;
        game.col+=8;
    }
    else if(roundSelect == -2){
        game.row+=2;
        game.col+=2;
    }
}

void drawUnKey(mainScreen &game, int yr, int xr, char art[50][120], int y1, int x1){
    if(game.board[yr][xr] == -1){
		//15 = 0*16 + 15 white text black background
		TextColor(15);

	    gotoxy(xr*5 + 1, yr*3 + 2);
        cout << art[yr*3    ][xr*5] << art[yr*3    ][xr*5 + 1] << art[yr*3    ][xr*5 + 2] << art[yr*3    ][xr*5 + 3] << art[yr*3    ][xr*5 + 4];
        gotoxy(xr*5 + 1, yr*3 + 3);
        cout << art[yr*3 + 1][xr*5] << art[yr*3 + 1][xr*5 + 1] << art[yr*3 + 1][xr*5 + 2] << art[yr*3 + 1][xr*5 + 3] << art[yr*3 + 1][xr*5 + 4];
        gotoxy(xr*5 + 1, yr*3 + 4);
        cout << art[yr*3 + 2][xr*5] << art[yr*3 + 2][xr*5 + 1] << art[yr*3 + 2][xr*5 + 2] << art[yr*3 + 2][xr*5 + 3] << art[yr*3 + 2][xr*5 + 4];
    }
    else{
        if(yr == y1 && xr == x1)
            //240 = 15*16 + 0 black text white background
            TextColor(240);
        else
            //showing color from 8 to 14
            TextColor(game.board[yr][xr]%6 + 9);
        
        char show;
        if(game.board[yr][xr] >= 0 && game.board[yr][xr] < 26)
            show = (char)(game.board[yr][xr] + (int)'A');
        else if(game.board[yr][xr] >= 26)
            show = (char)(game.board[yr][xr] + (int)'a' - 26);

        gotoxy(xr*5 + 1, yr*3 + 2);
        cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
        gotoxy(xr*5 + 1, yr*3 + 3);
        cout << (char)(186) << " "         << show        << " "         << (char)(186);
        gotoxy(xr*5 + 1, yr*3 + 4);
        cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
    }
}

void drawKey(mainScreen &game, int yr, int xr, int y1, int x1){
    if(yr == y1 && xr == x1)
        //241 = 15*16 + 1 blue text white background
	    TextColor(241);
    else
        //31 = 1*16 + 15 white text blue background
        TextColor(16 + game.board[yr][xr]%6 + 9);
    
    char show;
    if(game.board[yr][xr] >= 0 && game.board[yr][xr] < 26)
        show = (char)(game.board[yr][xr] + (int)'A');
    else if(game.board[yr][xr] >= 26)
        show = (char)(game.board[yr][xr] + (int)'a' - 26);
    else{
        //31 = 1*16 + 15 white text blue background
	    TextColor(31);
        show = '_';
    }

	gotoxy(xr*5 + 1, yr*3 + 2);
	cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
	gotoxy(xr*5 + 1, yr*3 + 3);
    cout << (char)(186) << " "         << show        << " "         << (char)(186);
	gotoxy(xr*5 + 1, yr*3 + 4);
    cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
}

void drawHint(mainScreen &game, int y, int x){
    //175 = 10*16 + 15 white text bright green background
    TextColor(175);

    char show;
    if(game.board[y][x] >= 0 && game.board[y][x] < 26)
        show = (char)(game.board[y][x] + (int)'A');
    else if(game.board[y][x] >= 26)
        show = (char)(game.board[y][x] + (int)'a' - 26);
    
    gotoxy(x*5 + 1, y*3 + 2);
	cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
	gotoxy(x*5 + 1, y*3 + 3);
    cout << (char)(186) << " "         << show        << " "         << (char)(186);
	gotoxy(x*5 + 1, y*3 + 4);
    cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
}

/*
    Use for void drawingLine (block in board)
    0: line down
    1: line up
    2: line right
    3: line left
    4: 179: line |
    5: 196: line -
    6: 218: line down-right
    7: 191: line down-left
    8: 192: line up-right
    9: 217: line up-left
    
    Use for void drawingLine
*/

void drawingLine(mainScreen &game, int i, int j){
    //4 = 0*16 + 4 red text black background
    TextColor(4);
    gotoxy(j*5 + 1, i + 2);

    //mutiply i with 3 to draw the board

    //line down
    if(game.board[i/3][j] == (int)'0'){
        if(i%3 == 0)
            cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
        else if(i%3 == 1)
            cout << (char)(186) << " "         << (char)(179) << " "         << (char)(186);
        else if(i%3 == 2)
            cout << (char)(200) << (char)(205) << (char)(179) << (char)(205) << (char)(188);
    }
    //line up
    else if(game.board[i/3][j] == (int)'1'){
        if(i%3 == 0)
            cout << (char)(201) << (char)(205) << (char)(179) << (char)(205) << (char)(187);
        else if(i%3 == 1)
            cout << (char)(186) << " "         << (char)(179) << " "         << (char)(186);
        else if(i%3 == 2)
            cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
    }
    //line right
    else if(game.board[i/3][j] == (int)'2'){
        if(i%3 == 0)
            cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
        else if(i%3 == 1)
            cout << (char)(186) << " "         << (char)(196) << (char)(196) << (char)(196);
        else if(i%3 == 2)
            cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
    }
    //line left
    else if(game.board[i/3][j] == (int)'3'){
        if(i%3 == 0)
            cout << (char)(201) << (char)(205) << (char)(205) << (char)(205) << (char)(187);
        else if(i%3 == 1)
            cout << (char)(196) << (char)(196) << (char)(196) << " "         << (char)(186);
        else if(i%3 == 2)
            cout << (char)(200) << (char)(205) << (char)(205) << (char)(205) << (char)(188);
    }
    //line |
    else if(game.board[i/3][j] == (int)'4'){
        gotoxy(j*5 + 3, i + 2);
        cout                                   << (char)(179);
    }
    //line -
    else if(game.board[i/3][j] == (int)'5'){
        gotoxy(j*5 + 1, i + 2);
        if(i%3 == 1)
            cout << (char)(196) << (char)(196) << (char)(196) << (char)(196) << (char)(196);
    }
    //line down-right
    else if(game.board[i/3][j] == (int)'6'){
        gotoxy(j*5 + 3, i + 2);
        if(i%3 == 1)
            cout                               << (char)(218) << (char)(196) << (char)(196);
        else if(i%3 == 2)
            cout                               << (char)(179);
    }
    //line down-left
    else if(game.board[i/3][j] == (int)'7'){
        if(i%3 == 1){
            gotoxy(j*5 + 1, i + 2);
            cout << (char)(196) << (char)(196) << (char)(191);
        }
        else if(i%3 == 2){
            gotoxy(j*5 + 3, i + 2);
            cout                               << (char)(179);
        }
    }
    //line up-right
    else if(game.board[i/3][j] == (int)'8'){
        gotoxy(j*5 + 3, i + 2);
        if(i%3 == 0)
            cout                               << (char)(179);
        else if(i%3 == 1)
            cout                               << (char)(192) << (char)(196) << (char)(196);
    }
    //9: 217: line up-left
    else if(game.board[i/3][j] == (int)'9'){
        if(i%3 == 0){
            gotoxy(j*5 + 3, i + 2);
            cout                               << (char)(179);
        }
        else if(i%3 == 1){
            gotoxy(j*5 + 1, i + 2);
            cout << (char)(196) << (char)(196) << (char)(217);
        }
    }
}

void drawBorder(int color){
    TextColor(color);

    gotoxy(0, 1);
    cout << char(218);
    for(int i = 1; i <= 22*5; i++)
        cout << char(196);
    cout << char(191);
    for(int i = 2; i <= 10*3 + 2; i++){
        gotoxy(0, i);
        cout << char(179);
        gotoxy(22*5 + 1, i);
        cout << char(179);
    }
    gotoxy(0, 10*3 + 3);
    cout << char(192);
    for(int i = 1; i <= 22*5; i++)
        cout << char(196);
    cout << char(217);
}

void drawingBoard(mainScreen &game, char bgArt[40][120]){
	for(int i = 0; i < (10)*3; i++){
		for(int j = 0; j < 22; j++){
            if(i < (game.row + 2)*3 && j < game.col + 2){
                if(game.board[i/3][j] >= (int)'0' && game.board[i/3][j] <= (int)'9'){
                    drawingLine(game, i, j);
                }
                else{
                    //showing color from 8 to 14
                    TextColor(game.board[i/3][j]%6 + 9);
                    gotoxy(j*5 + 1, i + 2);
                    if(game.board[i/3][j] == -1){
                        //15 = 0*16 + 15 white text black background
                        TextColor(15);
                        cout << bgArt[i][j*5] << bgArt[i][j*5 + 1] << bgArt[i][j*5 + 2] << bgArt[i][j*5 + 3] << bgArt[i][j*5 + 4];
                    }
                    else if(i%3 == 0)
                        cout << (char)(201) << (char)(205) << (char)(205)                           << (char)(205) << (char)(187);
                    else if(i%3 == 1 && game.board[i/3][j] < 26)
                        cout << (char)(186) << " "         << (char)(game.board[i/3][j] + (int)'A')      << " "         << (char)(186);
                    else if(i%3 == 1 && game.board[i/3][j] >= 26)
                        cout << (char)(186) << " "         << (char)(game.board[i/3][j] + (int)'a' - 26) << " "         << (char)(186);
                    else if(i%3 == 2)
                        cout << (char)(200) << (char)(205) << (char)(205)                           << (char)(205) << (char)(188);
                }
            }
            else{
                //15 = 0*16 + 15 white text black background
                TextColor(15);
                cout << bgArt[i][j*5] << bgArt[i][j*5 + 1] << bgArt[i][j*5 + 2] << bgArt[i][j*5 + 3] << bgArt[i][j*5 + 4];
            }
		}
		cout << endl;
	}

    //15 = 0*16 + 15 white text black background
	TextColor(15);
}

void drawOutsideBoard(int &level, Player &user, bool accountLogedIn){
    if(level == 1){
        //1 draw blue border
        drawBorder(1);
        //40 = 1*16 + 15 white text blue background
        TextColor(31);
    }
    else if(level == 2 || level == 4){
        //5 draw purple border
        drawBorder(5);
        //95 = 5*16 + 15 white text purple background
        TextColor(95);
    }
    else if(level == 3 || level == 5){
        //4 draw red border
        drawBorder(4);
        //79 = 4*16 + 15 white text red background
        TextColor(79);
    }
    gotoxy(0, 0);
    cout << "Level " << level;
    
    //15 = 0*16 + 15 white text black background
	TextColor(15);
    gotoxy(30, 0);
    cout << "Player: ";
    if(accountLogedIn)
        cout << user.username;
    gotoxy(60, 0);
    cout << "Score: ";
    gotoxy(90, 0);
    cout << "Time: " << endl;


    //drawing turtorial
    //10 = 0*16 + 10 yellow text black background
	TextColor(6);
    for(int i = 0; i < 45; i++){
        gotoxy(120, i);
        cout << (char)(186);
    }
    gotoxy(125, 1);
    cout << "Using arrow key to move.";
    gotoxy(125, 2);
    cout << "Press SPACE for choosing 1 block.";
    gotoxy(125, 3);
    //cout << "Press 'A' for auto playing (1 hint lose 50 points). Then Press any key to match 2 hightlight cells";
    cout << "Press 'A' for auto playing (1 hint lose 50 points).";
    gotoxy(125, 4);
    cout << "Press 'S' for shuffling the board.";
    gotoxy(125, 5);
    cout << "Press ESC to exit the game (no saving).";

    //15 = 0*16 + 15 white text black background
	TextColor(15);
}

