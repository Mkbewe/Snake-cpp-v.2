#include <iostream>
#include <conio.h>
#include <algorithm>

#include "screen.h"
#include "menu.h"
#include "menus.h"
#include "save.h"


using namespace std;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}


void cls()
{
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };     // pozycja pocz¹tkowa kursora
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Pobranie iloœci znaków w buforze konsoli
    if( !GetConsoleScreenBufferInfo( hStdout, &csbi ))
        return;
    // Okreœlenie, z ilu znaków sk³ada siê ekran konsoli (szerokoœæ * wysokoœæ)
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Zapisanie ca³ego ekranu spacjami
    if( !FillConsoleOutputCharacter( hStdout, (TCHAR) ' ',
                                     dwConSize, coordScreen, &cCharsWritten ))
        return;

    // Pobranie atrybutów (ustawieñ) tekstu (czyli np kolor itd)
    if( !GetConsoleScreenBufferInfo( hStdout, &csbi ))
        return;

    // Ustawienie w konsoli odczytanych wczeœniej atrybutów
    if( !FillConsoleOutputAttribute( hStdout, csbi.wAttributes,
                                     dwConSize, coordScreen, &cCharsWritten ))
        return;

    // Ustawienie kursora na pozycji startowej
    SetConsoleCursorPosition( hStdout, coordScreen );
}

int main_menu()
{
    short check = 0;
    short confirm = 0;
    char CHAR;

    Screen MainMenu (menu_width,menu_heigt,Screen::non);
    MainMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu GameMenu (menu_width/2,3,"Main Menu");
    GameMenu.show(true);

    Menu SinglePlayer (menu_width/2,7,"Single Player");
    Menu MultiPlayer (menu_width/2,9,"Multi Player");
    Menu Options (menu_width/2,11,"Options");
    Menu Ranking (menu_width/2,13,"Ranking");
    Menu Exit (menu_width/2,15,"Exit");
    HideCursor();

    while (check != 6)
    {
        if (check==0)
        {
            SinglePlayer.show(true);
            MultiPlayer.show(false);
            Options.show(false);
            Ranking.show(false);
            Exit.show(false);
            confirm = 0;
        }
        if (check==1)
        {
            SinglePlayer.show(false);
            MultiPlayer.show(true);
            Options.show(false);
            Ranking.show(false);
            Exit.show(false);
            confirm = 1;
        }
        else if (check==2)
        {
            SinglePlayer.show(false);
            MultiPlayer.show(false);
            Options.show(true);
            Ranking.show(false);
            Exit.show(false);
            confirm = 2;
        }
        else if (check==3)
        {
            SinglePlayer.show(false);
            MultiPlayer.show(false);
            Options.show(false);
            Ranking.show(true);
            Exit.show(false);
            confirm = 3;
        }
        else if (check==4)
        {
            SinglePlayer.show(false);
            MultiPlayer.show(false);
            Options.show(false);
            Ranking.show(false);
            Exit.show(true);
            confirm = 4;
        }

        CHAR = getch ();

        switch (CHAR)
        {
        case 'w':
        case 'W':
        case 72:
            check--;
            Beep(500,75);
            break;
        case 's':
        case 'S':
        case 80:
            check++;
            Beep(500,75);
            break;
        case 27:
            system ("cls");
            Beep(600,125);
            return 50;
        case 13:
        case 32:
            if (confirm == 0) // Single
            {
                Game_Mode=1;
                Beep(600,125);
                return 10;
            }

            else if (confirm == 1) //Multi
            {
                Game_Mode=2;
                Beep(600,125);
                return 20;
            }

            else if (confirm == 2) //Options
            {
                Beep(600,125);
                return 30;
            }
            else if (confirm == 3) // Ranking
            {
                Beep(600,125);
                return 40;
            }
            else if (confirm == 4)
            {
                Beep(600,125);
                return 50;
            }

        }
        if (check<0) check=4;
        if (check>4) check=0;
    }
    return 1;
}

int game_mode()

{
    short check = 0;
    short confirm = 0;
    char CHAR;

    Screen GameMenu (menu_width,menu_heigt,Screen::non);
    GameMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu GameMode (menu_width/2,3,"Game Mode");
    GameMode.show(true);

    Menu NormalGame (menu_width/2,7,"Normal Game");
    Menu PlayOnTime (menu_width/2,9,"Play On Time");
    Menu Back (menu_width/2,11,"Back");
    HideCursor();

    while (check != 4)
    {
        if (check==0)       // Standard
        {
            NormalGame.show(true);
            PlayOnTime.show(false);
            Back.show(false);
            confirm = 0;
        }
        else if (check==1)          //On Time
        {
            NormalGame.show(false);
            PlayOnTime.show(true);
            Back.show(false);
            confirm = 1;
        }
        else if (check==2)          //Back
        {
            NormalGame.show(false);
            PlayOnTime.show(false);
            Back.show(true);
            confirm = 2;
        }
        CHAR = getch ();

        switch (CHAR)
        {
        case 'w':
        case 'W':
        case 72:
            check--;
            Beep(500,75);
            break;
        case 's':
        case 'S':
        case 80:
            check++;
            Beep(500,75);
            break;
        case 27:
            Beep(600,125);
            return 1;
        case 13:
        case 32:
            if (confirm == 0)  // Standard
            {
                Beep(600,125);
                Game_Mode_Time= 1;
                return 2;
            }

            else if (confirm == 1) //On Time
            {
                Beep(600,125);
                Game_Mode_Time= 2;
                return 2;
            }
            else if (confirm == 2) //Back
            {
                Beep(600,125);
                return 1;
            }
        }
        if (check<0) check=2;
        if (check>2) check=0;
    }
    return 1;
}

    int options()
{

    short check = 0;
    short confirm = 0;
    char CHAR;

    Screen GameMenu (menu_width,menu_heigt,Screen::non);
    GameMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu Options (menu_width/2,3,"Options");
    Options.show(true);
    Menu Difficult (menu_width/2,6,"Difficult");
    Difficult.show(true);
    Menu Other (menu_width/2,15,"Other");
    Other.show(true);

    static Menu Easy (menu_width/2,8,"Easy Off","Easy On");
    static Menu Medium (menu_width/2,10,"Medium Off","Medium On");
    static Menu Hard (menu_width/2,12,"Hard Off","Hard On");

    if (Dificult==1) Easy.set_mode2(true);
    else if (Dificult==2) Medium.set_mode2(true);
    else if (Dificult==3) Hard.set_mode2(true);

    Menu MapSize (menu_width/2,17,"Map Size");
    static Menu GoodMode (menu_width/2,19,"Good Mode Off","Good Mode On");

    Menu More (menu_width/2,21,"More..");
    Menu Back (menu_width/2,23,"Back");

    HideCursor();

    while (check != 7)
    {

        if (check==0)       // Easy
        {
            Easy.show(true);
            Medium.show(false);
            Hard.show(false);

            MapSize.show(false);
            GoodMode.show(false);

            More.show(false);
            Back.show(false);

            Back.show(false);
            confirm = 0;
        }
        else if (check==1)          //Medium
        {
            Easy.show(false);
            Medium.show(true);
            Hard.show(false);

            MapSize.show(false);
            GoodMode.show(false);
            More.show(false);

            Back.show(false);
            confirm = 1;
        }
        else if (check==2)          //Hard
        {
            Easy.show(false);
            Medium.show(false);
            Hard.show(true);

            MapSize.show(false);
            GoodMode.show(false);
            More.show(false);

            Back.show(false);
            confirm = 2;
        }
        else if (check==3)          //Map Size
        {
            Easy.show(false);
            Medium.show(false);
            Hard.show(false);

            MapSize.show(true);
            GoodMode.show(false);
            More.show(false);

            Back.show(false);
            confirm = 3;
        }

        else if (check==4)          //GoodMode
        {
            Easy.show(false);
            Medium.show(false);
            Hard.show(false);

            MapSize.show(false);
            GoodMode.show(true);
            More.show(false);

            Back.show(false);
            confirm = 4;
        }

        else if (check==5)          //more
        {
            Easy.show(false);
            Medium.show(false);
            Hard.show(false);

            MapSize.show(false);
            GoodMode.show(false);
            More.show(true);

            Back.show(false);
            confirm = 5;
        }

        else if (check==6)          //back
        {
            Easy.show(false);
            Medium.show(false);
            Hard.show(false);

            MapSize.show(false);
            GoodMode.show(false);
            More.show(false);

            Back.show(true);
            confirm = 6;
        }

        CHAR = getch ();

        switch (CHAR)
        {
        case 'w':
        case 'W':
        case 72:
            check--;
            Beep(500,75);
            break;
        case 's':
        case 'S':
        case 80:
            check++;
            Beep(500, 75);
            break;
        case 27:
            Beep(600,125);
            return 1;
        case 13:
        case 32:
            if (confirm == 0)  // Easy
            {
                Easy.set_mode2(true);
                Medium.set_mode2(false);
                Hard.set_mode2(false);
                Dificult = 1;
                game_speed = 150;
                apple_bonus_frequency = 150;
                Beep(600, 125);
                return 1;
            }

            else if (confirm == 1) //Medium
            {
                Easy.set_mode2(false);
                Medium.set_mode2(true);
                Hard.set_mode2(false);
                Dificult = 2;
                game_speed = 100;
                apple_bonus_frequency = 250;
                Beep(600, 125);
                return 1;
            }
            else if (confirm == 2) //Hard
            {
                Easy.set_mode2(false);
                Medium.set_mode2(false);
                Hard.set_mode2(true);
                Dificult = 3;
                game_speed = 50;
                apple_bonus_frequency = 400;
                Beep(600, 125);
                return 1;
            }
            else if (confirm == 3) //MapSize
            {
                Beep(600, 125);
                return 31;
            }
            else if (confirm == 4) //GoodMode
            {
                if (goodmode==false)
                {
                    goodmode=true;
                    GoodMode.set_mode2(true);
                }
                else if (goodmode==true)
                {
                    goodmode=false;
                    GoodMode.set_mode2(false);
                }
                Beep(600, 125);
                return 1;
            }

            else if (confirm == 5) //MapSize
            {
                Beep(600, 125);
                return 41;
            }

            else if (confirm == 6) //Back
            {
                Beep(600, 125);
                return 1;
            }
        }
        if (check<0) check=6;
        if (check>6) check=0;
    }
    return 1;
}

int more()

{
    short check = 0;
    short confirm = 0;
    char CHAR;

    Screen GameMenu (menu_width,menu_heigt,Screen::non);
    GameMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu Advance (menu_width/2,3,"Other");
    Advance.show(true);

    static Menu Advance1 (menu_width/2,6,"Two snake colision On","Two snake colision Off");

    Menu Back (menu_width/2,21,"Back");

    HideCursor();

    while (check != 2)
    {

        if (check==0)
        {
            Advance1.show(true);

            Back.show(false);
            confirm = 0;
        }
        else if (check==1)
        {
            Advance1.show(false);

            Back.show(true);
            confirm = 1;
        }

        CHAR = getch ();

        switch (CHAR)
        {
        case 'w':
        case 'W':
        case 72:
            check--;
            Beep(500,75);
            break;
        case 's':
        case 'S':
        case 80:
            check++;
            Beep(500, 75);
            break;
        case 27:
            Beep(600,125);
            return 1;
        case 13:
        case 32:

            if (confirm == 0)
            {
                if (Advance1.Is_mode2()==false)
                {
                    snaks_colision = false;
                    Advance1.set_mode2(true);
                    Beep(600, 125);
                }
                else if (Advance1.Is_mode2()==true)
                {
                    snaks_colision = true;
                    Advance1.set_mode2(false);
                    Beep(600, 125);
                }
                return 30;
            }

            else if (confirm == 1) //Back
            {
                Beep(600, 125);
                return 30;
            }
        }
        if (check<0) check=1;
        if (check>1) check=0;
    }
    return 30;
}

int mapsize()

{
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    short tmp;
    Screen MainMenu (menu_width,menu_heigt,Screen::non);
    MainMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu MapOptions (menu_width/2,3,"Map Options");
    MapOptions.show(true);

    Menu EnterX1 (menu_width/2,7,"Enter the width of the map");
    Menu EnterX2 (menu_width/2,9,"Min 10, Max 85:");
    EnterX1.show(true);
    EnterX2.show(true);
    ShowCursor();

    SetConsoleTextAttribute(uchwyt, 0x70);
    while (!(cin>>tmp))
    {
        cin.clear();
        cin.ignore();
    }
    if (tmp>85)
        tmp=85;

    map_width=tmp;
    Beep(600,125);

    Menu EnterY1 (menu_width/2,13,"Enter the height of the map:");
    Menu EnterY2 (menu_width/2,15,"Min 10, Max 24:");
    EnterY1.show(true);
    EnterY2.show(true);
    while (!(cin>>tmp))
    {
        cin.clear();
        cin.ignore();
    }
    if (tmp>24)
        tmp=24;

    height=tmp-5;
    Beep(600,125);

    SetConsoleTextAttribute(uchwyt, 0x07);
    return 30;
}

string enter_name()

{
    cls();
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    string tmp;
    Screen MainMenu (menu_width,menu_heigt,Screen::non);
    MainMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu AddPlayer (menu_width/2,3,"Add Player");
    AddPlayer.show(true);

    Menu EnterX1 (menu_width/2,7,"Enter your name");
    Menu EnterX2 (menu_width/2,9,"Max 11 characters: ");
    EnterX1.show(true);
    EnterX2.show(true);
    ShowCursor();

    SetConsoleTextAttribute(uchwyt, 0x70);
    cin>>tmp;

    SetConsoleTextAttribute(uchwyt, 0x07);
    HideCursor();

    return tmp;
}

int ranking(Ranking player[])
{
    short check = 0;
    short confirm = 0;
    char CHAR;

    Screen GameMenu (menu_width,menu_heigt,Screen::non);
    GameMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    Menu Ranking (menu_width/2,3,"Ranking");
    Ranking.show(true);

    Menu Back (menu_width/2,menu_heigt+9,"Back");


    {


    sort (player,player+50);
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(uchwyt, 0x70);
    for (int i=0; i<18; i++) {gotoxy(menu_width-1,i+6); cout<<"  ";}
    gotoxy(1,5);
    cout<<" LP.     Nick                                Score       Length       Time \n";

    for (int i=0; i<18; i++)
    {
        if (player[i].length==0)
        {
            cout.width( 1 );
            cout<<right<<"[";
            cout.width( 2 );
            cout<<right<<i+1;
            cout.width( 1 );
            cout<<right<<"] ";
            cout<<"           ............................   0   .....    0   ....    0 \n";

        }
        else
        {
            cout.width( 1 );
            cout<<right<<"[";
            cout.width( 2 );
            cout<<right<<i+1;
            cout.width( 1 );
            cout<<right<<"] ";
            cout.width( 10 );
            cout<<left<<player[i].name;

            cout<<" ............................ ";

            cout.width( 3 );
            cout<<internal<<player[i].score;
            cout<<"   .....  ";
            cout.width( 3 );
            cout<<internal<<player[i].length;
            cout<<"   ....  ";
            cout.width( 3 );
            cout<<internal<<player[i].time<<" "<<endl;

        }
    }
     SetConsoleTextAttribute(uchwyt, 0x07);
    }

    HideCursor();

    while (check != 2)
    {
        if (check==0)          //Back
        {
            Back.show(true);
            confirm = 0;
        }

        CHAR = getch ();

        switch (CHAR)
        {
        case 'w':
        case 'W':
        case 72:
            check--;
            break;
        case 's':
        case 'S':
        case 80:
            check++;
            break;
        case 27:
            Beep(600,125);
            return 1;
        case 13:
        case 32:
            if (confirm == 0)  // back
            {
                Beep(600,125);
                return 1;
            }

        }
        if (check<0) check=1;
        if (check>1) check=0;
    }
    return 1;
}


int lose(Snake &t)

{
    cls();
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    string tmp;
    Screen MainMenu (menu_width,menu_heigt,Screen::non);
    MainMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);

    Menu EnterX1 (menu_width/2,7,"Game Over");
    EnterX1.show(true);
    SetConsoleTextAttribute(uchwyt, 0x70);
    gotoxy((menu_width/2)-(t.get_player_name().size()/2),9);
    cout<<t.get_player_name();
    gotoxy(menu_width/3,11);
    cout<<t;

    SetConsoleTextAttribute(uchwyt, 0x07);

    return 1;
}

int lose(Snake &t,Snake &m)

{
    cls();
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    string tmp;
    Screen MainMenu (menu_width,menu_heigt,Screen::non);
    MainMenu.show_screen();

    Menu GameName (menu_width/2,2,"Snake.v.2");
    GameName.show(true);
    short name_lenth;

    name_lenth = t.get_player_name().size();

    SetConsoleTextAttribute(uchwyt, 0x70);
    gotoxy((menu_width/2)-((name_lenth+8)/2),7);
    cout<<" "<<t.get_player_name()<<" you lose ";
    gotoxy(menu_width/3.5,9);
    cout<<" "<<t<<" ";

    name_lenth = m.get_player_name().size();

    gotoxy((menu_width/2)-((name_lenth+8)/2),11);
    cout<<" "<<m.get_player_name()<<" you won ";
    gotoxy(menu_width/3.5,13);
    cout<<" "<<m<<" ";


    SetConsoleTextAttribute(uchwyt, 0x07);

    return 1;
}


void HideCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
}

void ShowCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    if( hCCI.bVisible != TRUE )
    {
        hCCI.bVisible = TRUE;
        ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
    }
}

