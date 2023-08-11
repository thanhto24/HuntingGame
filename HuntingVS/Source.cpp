#include "header.h"

void generateAccScreen(int& roundSelect, int Choice, string FileName, User& oldMan, unsigned int& index)
{
    roundSelect = 0;
    TextColor(BlackW);
    while (true)
    {
        TextColor(BlackW);
        //Print Login menu to choose to play as guest or member
        if (roundSelect == 0)
        {
            TextColor(BlackW);
            gotoxy(0, 10);
            printAccChoice(Choice);                 //show user screen
            selectAccChoice(roundSelect, Choice);   //get input from keyboard
        }

        //out screen to Menu
        if (roundSelect == -1)
            break;
        //User choose Login
        else if (roundSelect == 1)
        {
            clearScreen();
            TextColor(BlackW);
            signIn(FileName, oldMan, index);        //login and get User info to User oldMan
            break;
        }
        //User choose Sign up
        else if (roundSelect == 2)
        {
            clearScreen();
            TextColor(BlackW);
            signUp(FileName);                       //new account
            roundSelect = 0;                        //back to login menu for User to choose log in
        }
    }
    TextColor(BlackW);
}

void printAccChoice(int Choice)
{
    int directX = 83, directY = 19;
    TextColor(BlackW);
    title();
    /*gotoxy(0,9);
    cout << "\t\t\t\t\t\t\t\t __________  .__   __                       .__            "<< endl;
    cout << "\t\t\t\t\t\t\t\t \\______   \\ |__| |  | __ _____      ____   |  |__    __ __ "<< endl;
    cout << "\t\t\t\t\t\t\t\t  |     ___/ |  | |  |/ / \\__  \\   _/ ___\\  |  |  \\  |  |  \\"<< endl;
    cout << "\t\t\t\t\t\t\t\t  |    |     |  | |    <   / __ \\_ \\  \\___  |   Y  \\ |  |  /"<< endl;
    cout << "\t\t\t\t\t\t\t\t  |____|     |__| |__|_ \\ /____  /  \\___  > |___|  / |____/ "<< endl;
    cout << "\t\t\t\t\t\t\t\t                       \\/      \\/       \\/       \\/        "<< endl;*/

    //244 = 15*16 + 4 red text white background
    TextColor(RW);
    switch (Choice)
    {
        TextColor(BlackW);
    case 1:
    {
        //clear old boxs
        deleteChoiceBox(directX, directY + 4);
        deleteChoiceBox(directX, directY + 8);
        deleteChoiceBox(directX, directY + 12);

        gotoxy(directX - 5, directY);
        TextColor(BlackW);
        cout << "  << Play as Guest >>  " << endl;
        /*gotoxy(directX - 6, directY + 1);
        cout << "   (Data will be lost) " << endl;*/
        printChoiceBox(directX, directY);

        //244 = 15*16 + 4 red text white background
        TextColor(RW);
        gotoxy(directX, directY + 4);
        cout << "   Log In        " << endl;

        gotoxy(directX, directY + 8);
        cout << "   Sign Up       " << endl;

        gotoxy(directX, directY + 12);
        cout << "    Quit        " << endl;
        break;
    }
    case 2:
    {
        //clear old boxs
        deleteChoiceBox(directX, directY);
        deleteChoiceBox(directX, directY + 8);
        deleteChoiceBox(directX, directY + 12);

        gotoxy(directX - 3, directY);
        cout << "   Play as Guest       " << endl;
        gotoxy(directX - 6, directY + 1);
        cout << "                       " << endl;

        gotoxy(directX - 2, directY + 4);
        TextColor(BlackW);
        cout << "  << Log In >>        " << endl;
        printChoiceBox(directX, directY + 4);

        //244 = 15*16 + 4 red text white background
        TextColor(RW);
        gotoxy(directX, directY + 8);
        cout << "   Sign Up            " << endl;

        gotoxy(directX, directY + 12);
        cout << "    Quit        " << endl;
        break;
    }
    case 3:
    {
        //clear old boxs
        deleteChoiceBox(directX, directY);
        deleteChoiceBox(directX, directY + 4);
        deleteChoiceBox(directX, directY + 12);

        gotoxy(directX - 3, directY);
        cout << "   Play as Guest       " << endl;
        gotoxy(directX - 6, directY + 1);
        cout << "                       " << endl;

        gotoxy(directX, directY + 4);
        cout << "   Log In               " << endl;

        gotoxy(directX - 2, directY + 8);
        TextColor(BlackW);
        cout << "  << Sign Up >>            " << endl;
        printChoiceBox(directX, directY + 8);
        //244 = 15*16 + 4 red text white background
        TextColor(RW);

        gotoxy(directX, directY + 12);
        cout << "    Quit        " << endl;
        break;
    }
    case 4:
    {
        //clear old boxs
        deleteChoiceBox(directX, directY);
        deleteChoiceBox(directX, directY + 4);
        deleteChoiceBox(directX, directY + 8);

        gotoxy(directX - 5, directY);
        TextColor(RW);
        gotoxy(directX - 3, directY);
        cout << "   Play as Guest       " << endl;
        gotoxy(directX - 6, directY + 1);
        cout << "                       " << endl;

        gotoxy(directX, directY + 4);
        cout << "   Log In        " << endl;

        gotoxy(directX, directY + 8);
        cout << "   Sign Up       " << endl;

        TextColor(BlackW);
        gotoxy(directX, directY + 12);
        cout << " << Quit >>     " << endl;
        printChoiceBox(directX, directY + 12);
        break;
    }
    }
}

void selectAccChoice(int& roundSelect, int& Choice)
{
    char button = _getch();
    switch (button)
    {
        TextColor(BlackW);
    case KeyUp: //point to upper choice
    {
        Choice--;
        if (Choice == 0)
            Choice = 4;
        break;
    }
    case KeyDown:   //point to below choice
    {
        Choice++;
        if (Choice == 5)
            Choice = 1;
        break;
    }
    case 13:     //accept choice
    {
        if (Choice == 1)
        {
            roundSelect = -1;
        }
        else if (Choice == 2)
        {
            roundSelect = 1;
        }
        else if (Choice == 3)
        {
            roundSelect = 2;
        }
        else if (Choice == 4)
        {
            exit(0);
        }
        break;
    }
    case Esc:       //turn off console
    {
        exit(0);
    }
    }
}
void signUp(string FileName)
{
    User newguy;
    unsigned index = 0;
    int directX = 85, directY = 10;
    char confirm[20];           //check if user type wrong letter
    TextColor(BlackW);
    printSignUpBoard(directX, directY);

    gotoxy(directX + 2, directY);
    TextColor(BlackW);
    cout << "SIGN UP" << endl;

    //244 = 15*16 + 4 red text white background
    TextColor(RW);
    gotoxy(directX - 8, directY + 3);

    cout << "Username " << endl;   //(less than 16 characters)

    gotoxy(directX - 8, directY + 7);
    cout << "Password " << endl;   //(no more than 14 characters)

    gotoxy(directX - 8, directY + 11);
    cout << "Confirm ";

    //4 = 0*16 + 4 red text black background
    TextColor(RW);
    gotoxy(directX - 8, directY + 15);
    //cout << "Username must be LESS than 16 characters";
    gotoxy(directX - 8, directY + 16);
    //cout << "Password is NO MORE THAN 14 characters";

    //244 = 15*16 + 4 red text white background
    TextColor(RW);
    //get Username and Password
    gotoxy(directX + 10, directY + 3);
    cin.getline(newguy.player.account, 17);

    gotoxy(directX + 10, directY + 7);
    cin.getline(newguy.player.password, 15);

    gotoxy(directX + 10, directY + 11);
    cin.getline(confirm, 15);

    //check if the username exists,
    bool valid = isExistAcc(FileName, newguy.player.account, index);
    if (valid)
    {
        //4 = 0*16 + 4 red text black background
        TextColor(RW);
        gotoxy(directX, directY + 22);
        cout << "Existed Username!!          ";
        //244 = 15*16 + 4 red text white background
        TextColor(RW);
        Sleep(1000);
        clearScreen();
        signUp(FileName);           //username is used then user need to type new username
    }
    else if (strcmp(confirm, newguy.player.password) != 0)     // check if confirm password is different from password
    {
        gotoxy(directX, directY + 22);
        TextColor(RW);
        cout << "Password is incorrect!!        ";
        Sleep(1000);
        clearScreen();
        signUp(FileName);           //redo sign up if information provided is invalid
    }
    else
    {
        TextColor(BlackW);
        gotoxy(directX, directY + 22);
        cout << "Welcome New Player             ";     // sign up successfully
        Sleep(500);
        clearScreen();

        // open file to store new user's account
        ofstream fout(FileName, ios::binary | ios::app);
        if (!fout.is_open())
        {
            cout << "Error While Opening";
            exit(0);
        }

        //New Account store nothing exept username and password
        newguy.points = 0;

        // Storing info in binary file
        fout.seekp(0, ios::end);
        fout.write(newguy.player.account, 20);
        fout.write(newguy.player.password, 20);
        fout.write((char*)&newguy.bodyOfSnake, sizeof(Point));
        fout.write((char*)&newguy.points, sizeof(int));
        fout.write((char*)&newguy.level, sizeof(int));
        fout.write((char*)&newguy.direct, sizeof(int));
        fout.close();
    }
}

void signIn(string FileName, User& oldMan, unsigned int& index)
{
    TextColor(BlackW);
    index = 0;  // index of account to search for password quickly
    int directX = 85, directY = 10;
    printSignInBoard(directX, directY);
    gotoxy(directX + 2, directY);
    cout << "LOGIN" << endl;

    //244 = 15*16 + 4 red text white background
    TextColor(RW);
    gotoxy(directX - 8, directY + 3);
    cout << "Username " << endl;   //(less than 16 characters)

    gotoxy(directX - 8, directY + 7);
    cout << "Password " << endl;   //(no more than 14 characters)

    gotoxy(directX + 10, directY + 3);
    cin.getline(oldMan.player.account, sizeof(oldMan.player.account));

    gotoxy(directX + 10, directY + 7);
    cin.getline(oldMan.player.password, sizeof(oldMan.player.password));

    if (isExistAcc(FileName, oldMan.player.account, index))        //Check username if it is signed up then Check password is correct (similar to storing in file)
    {
        if (isPasswordCorrect(FileName, oldMan.player.password, index))        //compare the password with the stored one in SaveFile.dat
        {
            TextColor(BlackW);
            gotoxy(directX, directY + 22);
            cout << "Success!!";
            //244 = 15*16 + 4 red text white background
            TextColor(RW);
            getInfo(FileName, oldMan, index);                   //store info from file to variable (oldMan
        }
        else
        {
            TextColor(RW);
            gotoxy(directX, directY + 22);
            cout << "Wrong Password";
            Sleep(1000);
            clearScreen();
            //244 = 15*16 + 4 red text white background
            TextColor(RW);
            signIn(FileName, oldMan, index);                    //sign in again
        }
    }
    else
    {
        TextColor(RW);
        gotoxy(directX, directY + 10);
        cout << "Invalid Account" << endl;
        gotoxy(directX, directY + 11);
        cout << "Please Sign Up" << endl;
        gotoxy(directX - 25, directY + 12);
        cout << "Press Space to try Login again, Esc to SignUp or any keys to Play as Guest." << endl;
        //244 = 15*16 + 4 red text white background
        TextColor(RW);
        char button = _getch();
        if (button == Esc)                                      //if Users type wrong account, they can choose to sig in again or make the new one
        {
            clearScreen();
            signUp(FileName);
            signIn(FileName, oldMan, index);
        }
        else if (button == 13)
        {
            clearScreen();
            signIn(FileName, oldMan, index);
        }

    }
}

bool isExistAcc(string FileName, char username[20], unsigned int& index)
{
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    fin.seekg(0, ios::end);     //point to the end of file
    int file_size = (int)fin.tellg();    //size of file in bytes
    int numAcc = file_size / (sizeof(struct Player) + sizeof(Point) + 3 * sizeof(int));   //count a number of account signed up

    vector <string> name;   //Storing the signed Account
    char nameTemp[20];

    //if there is no acc signed up before, test will be skipped
    if (file_size == 0)
        return false;
    else
    {
        for (int i = 0; i < numAcc; i++)
        {
            fin.seekg((sizeof(struct Player) + sizeof(Point) + 3 * sizeof(int)) * i, ios::beg);  //point to the first element of the username
            fin.read(nameTemp, 20);         //read username
            name.push_back((string)nameTemp);
        }
    }
    fin.close();

    //check if a new username is similar with the valid username
    for (int i = 0; i < numAcc; i++)
    {
        if (strcmp(username, name[i].c_str()) == 0)
        {
            index = i;
            return true;
        }
    }

    return false;

}

bool isPasswordCorrect(string FileName, char password[20], unsigned int index)
{
    char passTemp[20];
    bool Correct = false;
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    fin.seekg(20 + ((sizeof(struct Player) + sizeof(Point) + 3 * sizeof(int)) * index), ios::beg);  //point to the first element of the password
    fin.read(passTemp, 20);         //read password (20 is size of password)

    if (strcmp(password, passTemp) == 0)
        Correct = true;

    fin.close();
    return Correct;
}

void getInfo(string FileName, User& oldMan, unsigned int index)
{
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    //fin.seekg((sizeof(oldMan.player.account) + sizeof(oldMan.player.password)) + sizeof(oldman.player)*index, ios::beg);        //point to the record of the indexth player
    fin.seekg((sizeof(oldMan.player.account) + sizeof(oldMan.player.password)), ios::beg);        //point to the record of the indexth player
    //fin.read((char*) &oldMan.points, sizeof(int));                                                      //read score and size of stage to Player oldMan
    //fin.read((char*) &oldMan.savedStage, sizeof(oldMan.savedStage));
}

/*void updateScore(string FileName, User &oldMan, unsigned int index, Board board)
{
    vector <User> List;
    User temp;
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    fin.seekg(0, ios::end);     //point to the end of file
    int file_size = fin.tellg();    //size of file in bytes
    int numAcc = file_size/(sizeof(struct Player) + sizeof(Point) + 3*sizeof(int));   //count the number of accounts signed up

    fin.seekg(0, ios::beg);
    for (int i = 0; i < numAcc; i++)
    {
        fin.read((char*) &temp, (sizeof(struct Player) + sizeof(Point) + 3*sizeof(int)));        //store all user's info to array List
        List.push_back(temp);
    }

    fin.close();

    List[index].level = board.level;      //update a new score , storing in file
    oldMan.level = board.level;           //in play time
    ofstream fout(FileName, ios::binary);
    if (!fout.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    fout.seekp(0, ios::beg);
    for (int i = 0; i < numAcc; i++)
    {
        fout.write((char*) &List[i], (sizeof(struct Player) + sizeof(Point) + 3*sizeof(int)));       //overwriting SaveFile
    }

    fout.close();
}*/

void generateMenu(int& roundSelect, int Choice, string FileName)
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
        cout << "Press ENTER for choosing.";

        //out while loop
        if (roundSelect < 0)
            break;
        printMenu(roundSelect, Choice, FileName);
        getEvents(roundSelect, Choice);
    }
}

void getEvents(int& roundSelect, int& Choice)
{
    char button = _getch();
    switch (roundSelect)
    {
        //first screen 
    case 1:
    {
        switch (button)
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
        case 13:
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
            printMenuBox(directX - 2, directY - 2);
            gotoxy(directX - 4, 22);
            //244 = 15*16 + 4 red text white background
            TextColor(RW);
            cout << "  Play new file  " << endl;

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
            printMenuBox(directX - 2, directY + 2);
            TextColor(GreenW);
            gotoxy(directX - 4, 22);
            cout << "<<Play new file>>  " << endl;

            gotoxy(directX - 4, 26);
            //244 = 15*16 + 4 red text white background
            TextColor(RW);
            cout << "     Credit      " << endl;

            gotoxy(directX - 4, 30);
            cout << "      Quit       " << endl;
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
            cout << "  Play new file  " << endl;

            TextColor(boxColor);
            printMenuBox(directX - 2, directY + 6);
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
                deleteMenuBox(directX - 2, directY - 2 + i * 4);
            TextColor(RW);
            gotoxy(directX - 4, 18);
            cout << "      Play        " << endl;

            gotoxy(directX - 4, 22);
            cout << "  Play new file   " << endl;

            gotoxy(directX - 4, 26);
            cout << "     Credit       " << endl;

            TextColor(boxColor);
            printMenuBox(directX - 2, directY + 10);
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
    //Credit Button
    case 3:
    {
        clearScreen();
        printCredit();
        break;
    }
    //LeaderBoard Button
    case 4:
    {
        clearScreen();
        gotoxy(0, 6);
        gotoxy(77, 29);
        TextColor(241);
        cout << "Press ESC to exit";
        //printLeaderBoard(FileName);
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
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Ngo Van Khai" << setfill(' ') << "22127174 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Le Phuoc Phat" << setfill(' ') << "22127322 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " To Quoc Thanh" << setfill(' ') << "22127388 \n";
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " Thai Huyen Tung" << setfill(' ') << "22127441 \n";

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

//https://www.codeincodeblock.com/2011/03/move-console-windows-using-codeblock.html
/*HWND WINAPI GetConsoleWindowNT(void)
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
    if (GetConsoleWindow == NULL) {
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}*/

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

//https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
void ShowScrollbar(BOOL Show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

//https://cplusplus.com/forum/articles/10515/
void clearScreen() {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
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
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

//https://nguyenvanquan7826.wordpress.com/2013/08/22/cc-gotoxy-trong-dev-c-gotoxy-in-dev-c/
void gotoxy(SHORT x, SHORT y) {//y: row, x: col
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
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
void TextColor(int color) {
    HANDLE colo;
    colo = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colo, color);
}

void title() {
    ifstream ifs("title.txt");
    int row = 6, col = 28;
    string temp;
    while (!ifs.eof()) {
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
            gotoxy(directX - 11, directY + 1 + i);
            for (int j = 0; j < 43; j++)
            {
                cout << char(205);
                if (j == 15)    //the the intersection between two board lines
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
            gotoxy(directX - 11, directY + 1 + i);
            for (int j = 0; j < 43; j++)
            {
                cout << char(205);
                if (j == 15)    //the the intersection between two board lines
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