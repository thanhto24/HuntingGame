#include "header.h"

void generateMenu (int &roundSelect, int Choice, string FileName)
{
    roundSelect = 1;
    int directX = 85, directY = 19;

    clearScreen();
    
    while (true)
    {
        //240 = 15*16 + 0 black text white background
        TextColor(BlackW);
        gotoxy(79, 38);
        cout << "Use arrow key to move.";
        gotoxy(78, 39);
        cout << "Press SPACE for choosing.";

        //out while loop
        if (roundSelect < 0)
            break;
        printMenu(roundSelect, Choice, FileName);
        getEvents(roundSelect, Choice);
    }
}

void getEvents(int &roundSelect, int &Choice)
{
    char button = getch();
    switch (roundSelect)
    {
        //first screen 
        case 1:
        {
            switch(button)
            {
                //point to upper choice
                case KeyUp:
                {
                    Choice--;
                    if (Choice == 0)
                        Choice = 4;
                    break;                  
                }
                //point to below choice
                case KeyDown:
                {
                    Choice++;
                    if (Choice == 5)
                        Choice = 1;
                    break;
                }
                //to select
                case Space:
                {
                    if (Choice == 1)
                    {
                        /*//go to difficulty options screen
                        roundSelect = 2;
                        Choice = 1;*/
                        roundSelect = -1;
                    }
                    else if (Choice == 2)
                    {
                        //LeaderBoard
                        roundSelect = 4;
                    }
                    else if (Choice == 3)
                    {
                        //Credit
                        roundSelect = 3;
                    }
                    else if (Choice == 4)
                        //Quit
                        exit(0);
                    break;
                }
                case Esc:
                {
                    //Quit
                    exit(0);
                    break;
                }
            }
        break;
        }
        //Screen where choosing game difficulty
        /*case 2:
        {
            switch(button)
            {
                case KeyUp:
                {
                    Choice--;
                    if (Choice == 0)
                        Choice = 3;
                    break;                  
                }
                case KeyDown:
                {
                    Choice++;
                    if (Choice == 4)
                        Choice = 1;
                    break;
                }
                case Space:
                { 
                    switch (Choice)
                    {
                        case (1):
                        {
                            roundSelect = -1;        
                            break;
                        }
                        case (2):
                        {
                            roundSelect = -2;
                            break;
                        }
                        case (3):
                        {
                            roundSelect = -3;
                            break;
                        }
                    }
                    break;
                }
                case Esc:
                {
                    clearScreen();
                    roundSelect = 1;
                    Choice = 1;
                }
            }
        break;
        }*/
        case 3: case 4:
        {
            if (button == Esc)
            {
                clearScreen();
                roundSelect = 1;
                Choice = 1;
            }
            break;
        }
    }
}

void printMenu(int roundSelect, int Choice, string FileName)
{
    //241 = 15*16 + 1 blue text white background
    TextColor(BlackW);
    int directX = 86, directY = 19;
    title();
	//242 = 15*16 + 1 green text white background
	TextColor(GreenW);

    switch (roundSelect)
    {
    	TextColor(BlackW);
        case 1:
        {
            if (Choice == 1)
            { 
                //delete old boxs
                deleteMenuBox(directX - 2, directY + 2);
                deleteMenuBox(directX - 2, directY + 6);
                deleteMenuBox(directX - 2, directY + 10);

                gotoxy(directX - 4, 18);
			    //242 = 15*16 + 2 green text white background
			    TextColor(GreenW);
                cout << "   << Play >>    " << endl;
                TextColor(boxColor);
                printMenuBox (directX - 2, directY - 2);
                gotoxy(directX - 4, 22);
			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
                cout << "   LeaderBoard   " << endl;

                gotoxy(directX - 4, 26);
                cout << "     Credit     " << endl;

                gotoxy(directX - 4, 30);
                cout << "      Quit      " << endl;
            }
            else if (Choice == 2)
            {
                //delete old boxs
                deleteMenuBox(directX - 2, directY - 2);
                deleteMenuBox(directX - 2, directY + 6);
                deleteMenuBox(directX - 2, directY + 8);

				TextColor(RW);
                gotoxy(directX - 4, 18);
                cout << "      Play       " << endl;

			    TextColor(boxColor);
                printMenuBox (directX - 2, directY + 2);
			    TextColor(GreenW);
                gotoxy(directX - 4, 22);
                cout << "<< LeaderBoard >>  " << endl;

                gotoxy(directX - 4, 26);
			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
                cout << "     Credit      " << endl;

                gotoxy(directX - 4, 30);
                cout << "      Quit       "  << endl;
            }
            else if (Choice == 3)
            {
                //delete old boxs
                deleteMenuBox(directX - 2, directY - 2);
                deleteMenuBox(directX - 2, directY + 2);
                deleteMenuBox(directX - 2, directY + 10);
				
				TextColor(RW);
                gotoxy(directX - 4, 18);
                cout << "      Play       " << endl;

                gotoxy(directX - 4, 22);
                cout << "   LeaderBoard   " << endl;

			    TextColor(boxColor);
                printMenuBox (directX - 2, directY + 6);
			    TextColor(GreenW);
                gotoxy(directX - 4, 26);
                
                cout << "  << Credit >>    " << endl;

                gotoxy(directX - 4, 30);
			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
                cout << "      Quit       " << endl;
            }
            else if (Choice == 4)
            {
                //delete old boxs
                for (int i = 0; i < 4; i++)
                    deleteMenuBox(directX - 2, directY - 2 + i*4);
                TextColor(RW);
				gotoxy(directX - 4, 18);
                cout << "      Play        " << endl;

                gotoxy(directX - 4, 22);
                cout << "   LeaderBoard    " << endl;

                gotoxy(directX - 4, 26);
                cout << "     Credit       " << endl;

			    TextColor(boxColor);
                printMenuBox (directX - 2, directY + 10);
			    TextColor(GreenW);
                gotoxy(directX - 4, 30);
                cout << "   << Quit >>      " << endl;

			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
            }
            break;
        }
        /*case 2:
        {
            gotoxy(directX - 4, 30);
            cout << "                   " << endl;

            if (Choice == 1)
            {
                //clear old boxs
                deleteMenuBox(directX - 2, directY + 2);
                deleteMenuBox(directX - 2, directY + 6);
                deleteMenuBox(directX - 2, directY + 10);
                deleteMenuBox(directX - 2, directY + 10);

                gotoxy(directX - 2, 18);
			    //242 = 15*16 + 2 green text white background
			    TextColor(GreenW);
                cout << " << Easy >>    " << endl;
                printMenuBox(directX - 2, directY - 2);        

			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
                gotoxy(directX - 2, 22);
                cout << "    Normal    " << endl;
                gotoxy(directX - 2, 26);
                cout << "    Hard      " << endl;
                
            }
            else if (Choice == 2)
            {
                //clear old boxs
                deleteMenuBox(directX - 2, directY - 2);
                deleteMenuBox(directX - 2, directY + 6);
                deleteMenuBox(directX - 2, directY + 10);
                gotoxy(directX - 2, 18);
                cout << "    Easy      " << endl;

			    //242 = 15*16 + 2 green text white background
			    TextColor(GreenW);
                gotoxy(directX - 2, 22);
                cout << " << Normal >>  " << endl;
                printMenuBox(directX - 2, directY + 2);

			    //244 = 15*16 + 4 red text white background
			    TextColor(RW);
                gotoxy(directX - 2, 26);
                cout << "    Hard      " << endl;
            } 
            else if (Choice == 3)
            {
                //clear old boxs
                deleteMenuBox(directX - 2, directY - 2);
                deleteMenuBox(directX - 2, directY + 2);
                deleteMenuBox(directX - 2, directY + 10);
                gotoxy(directX - 2, 18);
                cout << "    Easy      " << endl;
                gotoxy(directX - 2, 22);
                cout << "    Normal    " << endl;

                gotoxy(directX - 2, 26);
			    //242 = 15*16 + 2 green text white background
			    TextColor(GreenW);
                cout << " << Hard >>   " << endl;
                printMenuBox(directX - 2, directY + 6);
            }
            break;
        }*/
        case 3:
        {
            clearScreen();
            printCredit();
            break;
        }
        case 4:
        {
            clearScreen();
            gotoxy(0, 6);
            //printLeaderBoard(FileName);
            // displayFiles();
            break;
        }
    }

}
void printCredit()
{
    int directX = 85, directY = 19;
    gotoxy(0, 12);
    //242 = 15*16 + 2 green text white background
    TextColor(242);
    cout << "\t\t\t\t\t\t\t        ____                     _   _   _             \n"; 
    cout << "\t\t\t\t\t\t\t       / ___|  _ __    ___    __| | (_) | |_   ___    \n"; 
    cout << "\t\t\t\t\t\t\t      | |     | '__|  / _ `  / _` | | | | __| / __|   \n"; 
    cout << "\t\t\t\t\t\t\t      | |___  | |    |  __/ | (_| | | | | |_ .\\__ \\   \n"; 
    cout << "\t\t\t\t\t\t\t       `____| |_|     `___|  `__,_| |_| '__./ |___/   \n\n"; 

    cout << "\t\t\t\t\t\t\t\t\t       Hunting Game \n";
    cout << "\t\t\t\t\t\t\t\t Programming Technique's Course Project \n\n";
    //241 = 15*16 + 1 blue text white background
    TextColor(241);
    cout << "\t\t\t\t\t\t\t\t Programmed and Designed by \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Ngo Van Khai" << setfill(' ')  << "22127174 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Le Phuoc Phat" << setfill(' ')  << "22127322 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " To Quoc Thanh" << setfill(' ')  << "22127388 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Thai Huyen Tung" << setfill(' ')  << "22127441 \n";
    
    //241 = 15*16 + 1 blue text white background
    TextColor(241);
    cout << "\t\t\t\t\t\t\t\t\t  Thank you for playing!!";
    gotoxy(directX - 8, directY + 10);
    //241 = 15*16 + 1 blue text white background
    TextColor(241);
    cout << "Press ESC to exit";

    //241 = 15*16 + 1 blue text white background
    TextColor(241);
}

int main(){
	Sleep(5000);
    int roundSelect = 1, Choice = 1;
    int *pChoice = &Choice;
    User user;
    bool accountLogedIn = true;
    string FileName = "SaveFile.dat";
    unsigned int index = 0;

    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd, 0, 0, 1450, 760,TRUE);
    //ShowScrollbar(0);
    //DisableResizeWindow();
    system("color f0");
    TextColor(BlackW);
    gotoxy(79, 38);
    cout << "Use arrow key to move.";
    gotoxy(78, 39);
    cout << "Press SPACE for choosing.";
    generateAccScreen(roundSelect, Choice, FileName, user, index);
    if(roundSelect == -1)
        accountLogedIn = false;
	while(1){
        int scoreWhenOutGame = 0;
    	generateMenu(roundSelect, Choice, FileName);
	}
	return 0;
}