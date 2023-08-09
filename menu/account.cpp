#include "account.h"
#include "printDesign.h"

void generateAccScreen(int &roundSelect, int Choice, string FileName, User &oldMan, unsigned int &index)
{
    roundSelect = 0;
	TextColor(BlackW);
    while(true)
    {
    	TextColor(BlackW);
        //Print Login menu to choose to play as guest or member
        if (roundSelect == 0)
        {
        	TextColor(BlackW);
            gotoxy(0,10);                               
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
    switch(Choice)
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
            gotoxy(directX - 6, directY + 1);
            cout << "   (Data will be lost) " << endl;
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

void selectAccChoice(int &roundSelect, int &Choice)
{
    char button = getch();
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
        case Space:     //accept choice
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
    cin.getline (newguy.player.account, 17);

    gotoxy(directX + 10, directY + 7);
    cin.getline (newguy.player.password, 15);

    gotoxy(directX + 10,directY + 11);
    cin.getline (confirm, 15);

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
        Sleep(2000);
        clearScreen();
	    
	    // open file to store new user's account
	    ofstream fout(FileName, ios::binary|ios::app);
	    if (!fout.is_open())
	    {
	        cout << "Error While Opening";
	        exit(0);
	    }
	
	    //New Account store nothing exept username and password
	    newguy.record = 0;
	
	    // Storing info in binary file
	    fout.seekp(0, ios::end);
	    fout.write(newguy.player.account, 20);
	    fout.write(newguy.player.password, 20);
	    //fout.write('\n', 1);
	    //fout.write((char*) &newguy.record, sizeof(unsigned int));
		fout.close();
	}
}

void signIn(string FileName, User &oldMan, unsigned int &index)
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

    if(isExistAcc(FileName, oldMan.player.account, index))        //Check username if it is signed up then Check password is correct (similar to storing in file)
    {  
        if(isPasswordCorrect(FileName, oldMan.player.password, index))        //compare the password with the stored one in SaveFile.dat
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
        char button = getch();
        if (button == Esc)                                      //if Users type wrong account, they can choose to sig in again or make the new one
        {
            clearScreen();
            signUp(FileName);                                   
            signIn(FileName, oldMan, index);
        }
        else if (button == Space)
        {
            clearScreen();
            signIn(FileName, oldMan, index);
        }

    }
}

bool isExistAcc(string FileName, char username[20], unsigned int &index)
{
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }
    
    fin.seekg(0, ios::end);     //point to the end of file
    int file_size = fin.tellg();    //size of file in bytes
    int numAcc = file_size/sizeof(struct Player);   //count a number of account signed up

    vector <string> name;   //Storing the signed Account
    char nameTemp[20];
    
    //if there is no acc signed up before, test will be skipped
    if (file_size == 0)
        return false;
    else
    {
        for (int i = 0; i < numAcc; i++)
        {
            fin.seekg(sizeof(struct User) * i,ios::beg);  //point to the first element of the username
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
    
    fin.seekg(20 + (sizeof(struct Player) * index) ,ios::beg);  //point to the first element of the password
    fin.read(passTemp, 20);         //read password (20 is size of password)
    
    if (strcmp(password, passTemp) == 0) 
        Correct = true;

    fin.close();
    return Correct;
}

void getInfo (string FileName, User &oldMan, unsigned int index)
{
    ifstream fin(FileName, ios::binary);
    if (!fin.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }
    
    //fin.seekg((sizeof(oldMan.player.account) + sizeof(oldMan.player.password)) + sizeof(oldman.player)*index, ios::beg);        //point to the record of the indexth player
    fin.seekg((sizeof(oldMan.player.account) + sizeof(oldMan.player.password)), ios::beg);        //point to the record of the indexth player
    //fin.read((char*) &oldMan.record, sizeof(int));                                                      //read score and size of stage to Player oldMan
    //fin.read((char*) &oldMan.savedStage, sizeof(oldMan.savedStage));
}

void updateScore(string FileName, User &oldMan, unsigned int index, int newscore)
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
    int numAcc = file_size/sizeof(struct User);   //count the number of accounts signed up

    fin.seekg(0, ios::beg);
    for (int i = 0; i < numAcc; i++)
    {
        fin.read((char*) &temp, sizeof(User));        //store all user's info to array List
        List.push_back(temp);
    }

    fin.close();

    List[index].record = newscore;      //update a new score , storing in file
    oldMan.record = newscore;           //in play time
    ofstream fout(FileName, ios::binary);
    if (!fout.is_open())
    {
        cout << "Error While Opening";
        exit(0);
    }

    fout.seekp(0, ios::beg);
    for (int i = 0; i < numAcc; i++)
    {
        fout.write((char*) &List[i], sizeof(User));       //overwriting SaveFile
    }

    fout.close();
}
