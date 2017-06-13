
#include "screen.h"
#include "menu.h"
#include <iostream>
#include <conio.h>

using namespace std;

void Menu::gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}

Menu::Menu(int x,int y,string button,string button2)
{
    position_x=x;
    position_y=y;
    name = " "+button+" ";
    name2 = " "+button2+" ";
}

Menu::~Menu()
{
}

void Menu::set_mode2 (bool m2)

{
    mode2=m2;
}

void Menu::show (bool m)
{
    int lnf = name.size();

if (mode2==false)
 {
     mode=m;
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(position_x-(lnf/2),position_y);
    if (mode==false)
    {
        SetConsoleTextAttribute(uchwyt, 0x80);
        cout<<name;
    }
    else if (mode==true)
    {
        SetConsoleTextAttribute(uchwyt, 0x70);
         cout<<name;
    }
    SetConsoleTextAttribute(uchwyt, 0x07);
 }
 else if (mode2==true)
 {
      mode=m;
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(position_x-(lnf/2),position_y);
    if (mode==false)
    {
        SetConsoleTextAttribute(uchwyt, 0x80);
        cout<<name2;
    }
    else if (mode==true)
    {
        SetConsoleTextAttribute(uchwyt, 0x70);
         cout<<name2;
    }
    SetConsoleTextAttribute(uchwyt, 0x07);
 }

}

bool Menu::Is_mode2 ()
{
   return mode2;
}

