#include "printDesign.h"

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
    cout << char(201);
    for (int i = 0; i < 21; i++)
        cout << char(205);
    cout << char(187); 
    // print middle board
    for (int i = 0; i < 4; i++)
    {
        gotoxy(directX - 5, directY + i);
        cout << char(186);

        gotoxy(directX + 17, directY + i);
        cout << char(186);
        
    }

    //print bottom box
    gotoxy(directX - 5, directY + 3);
    cout << char(200);
    for (int i = 0; i < 21; i++)
    {
        cout << char(205);
    }
    cout << char(188); 
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
