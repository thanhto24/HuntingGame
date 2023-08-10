#include "printDesign.h"

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

void title(){
	ifstream ifs("title.txt");
	int row = 6, col = 28;
	string temp;
	while(!ifs.eof()){
		getline(ifs, temp, '\n');
		gotoxy(col, row++);
		TextColor(GreenW);
		cout << temp;
	}
	ifs.close();
}

void printSignUpBoard(int directX, int directY)
{
    //upper board
    gotoxy(directX - 12, directY + 1);
    cout << char(201);
    for (int i = 0; i < 44; i++)
        cout << char(205);
    cout << char(187); 
    //middle board
    for (int i = 0; i < 12; i++)
    {
        gotoxy(directX - 12, directY + 2 + i);
        cout << char(186);
        gotoxy(directX + 5, directY + 2 + i);
        cout << char(186);
        gotoxy(directX + 33, directY + 2 + i);
        cout << char(186);
        if (i % 4 == 0)
        {
            gotoxy(directX - 11,directY + 1 + i);
            for (int j = 0; j < 43; j++)
            {
                cout << char(205);
                if (j == 15 )    //the the intersection between two board lines
                    cout << char(206);
            }
        }
    }
    gotoxy(directX + 5, directY + 1);
    cout << char(203);
    // bottom board
    gotoxy(directX - 12, directY + 13);
    cout << char(200);

    for (int i = 0; i < 43; i++)
    {
        cout << char(205);
        if (i == 15)
            cout << char(202);
    }
    cout << char(188); 
    
}

void printSignInBoard(int directX, int directY)
{
    //  print upper board
    gotoxy(directX - 12, directY + 1);
    cout << char(201);
    for (int i = 0; i < 44; i++)
        cout << char(205);
    cout << char(187); 
    // print middle board
    for (int i = 0; i < 8; i++)
    {
        gotoxy(directX - 12, directY + 2 + i);
        cout << char(186);
        gotoxy(directX + 5, directY + 2 + i);
        cout << char(186);
        gotoxy(directX + 33, directY + 2 + i);
        cout << char(186);
        if (i % 4 == 0)
        {
            gotoxy(directX - 11,directY + 1 + i);
            for (int j = 0; j < 43; j++)
            {
                cout << char(205);
                if (j == 15 )    //the the intersection between two board lines
                    cout << char(206);
            }
        }
    }
    // print bottom board
    gotoxy(directX + 5, directY + 1);
    cout << char(203);

    gotoxy(directX - 12, directY + 9);
    cout << char(200);

    for (int i = 0; i < 43; i++)
    {
        cout << char(205);
        if (i == 15)
            cout << char(202);
    }
    cout << char(188); 
}

void printChoiceBox(int directX, int directY)
{
    //  print upper board
    gotoxy(directX - 5, directY - 1);
    cout << char(201);
    for (int i = 0; i < 21; i++)
        cout << char(205);
    cout << char(187); 
    // print middle board
    for (int i = 0; i < 3; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << char(186);

        gotoxy(directX + 17, directY + i);
        cout << char(186);
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 2);
    cout << char(200);
    for (int i = 0; i < 21; i++)
    {
        cout << char(205);
    }
    cout << char(188); 
}
void deleteChoiceBox(int directX, int directY)
{
    // overprint the box with space character
    gotoxy(directX - 5, directY - 1);
    cout << " ";
    for (int i = 0; i < 21; i++)
        cout << " ";
    cout << " "; 
    // print middle board
    for (int i = 0; i < 3; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << " ";

        gotoxy(directX + 17, directY + i);
        cout << " ";
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 2);
    cout << " ";
    for (int i = 0; i < 21; i++)
    {
        cout << " ";
    }
    cout << " "; 
}

void printMenuBox(int directX, int directY)
{
    //  print upper board
    gotoxy(directX - 5, directY - 1);
    cout << 'X';//char(201);
    for (int i = 0; i < 21; i++)
        cout << 'X';//char(205);
    cout << 'X';//char(187); 
    // print middle board
    for (int i = 0; i < 4; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << 'X';//char(186);

        gotoxy(directX + 17, directY + i);
        cout << 'X';//char(186);
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 3);
    cout << 'X';//char(200);
    for (int i = 0; i < 21; i++)
    {
        cout << 'X';//char(205);
    }
    cout << 'X';//char(188); 
}

void deleteMenuBox(int directX, int directY)
{
    // overprint the box with space character
    gotoxy(directX - 5, directY - 1);
    cout << " ";
    for (int i = 0; i < 21; i++)
        cout << " ";
    cout << " "; 
    // print middle board
    for (int i = 0; i < 4; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << " ";

        gotoxy(directX + 17, directY + i);
        cout << " ";
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 3);
    cout << " ";
    for (int i = 0; i < 21; i++)
    {
        cout << " ";
    }
    cout << " "; 
}
