#include <iostream>
#include <windows.h>
#include <conio.h>

#include "snake.h"
#include "menu.h"
#include "screen.h"
#include "apple.h"
#include "menus.h"
#include "save.h"

using  std::cout;
using  std::cin;
using  std::endl;
using  std::string;

HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
extern unsigned map_width;//szerokosc mapy + 20
extern unsigned height;    //wysokosc mapy + 10


Snake::Snake(int x, int y,Color c, int scr, int len)
{
    position_x=x;
    position_y=y;

    for (int i=0; i<=500; i++)
    {
        position_body_x[i]=2;
        position_body_y[i]=2;
    }

    score=scr;
    length=len;
    color = c;

    time=0;
    name="Player";
    tmpx=-1;
    tmpy=-1;

}

Snake::~Snake ()
{
}

void Snake::Show_Snake (char direction)

{
    HideCursor();
    move_snake(direction);

    //przechodzenie z jednej strony na druga
    if (position_x<=20) position_x=20+map_width; // 20 szerokosc pola gracza
    else if (position_x>=21+map_width) position_x=21;

    if (position_y<5) position_y=height+9; // 10 wysokosc pola belki
    else if (position_y>=height+10) position_y=5;

        // aktualizacja pozycji

    if (tmpx>-1&&tmpy>-1)
    {
        if (length==0)
        {
            position_body_x[0]=tmpx;
            position_body_y[0]=tmpy;
        }
        else
        {
            for (int i = length; i>0; i--)
            {
                position_body_x[i]=position_body_x[i-1];
                position_body_y[i]=position_body_y[i-1];
            }
              position_body_x[0]=tmpx;
              position_body_y[0]=tmpy;
        }
    }
        tmpx=position_x;
        tmpy=position_y;

    //cialo
    for (int i=0; i<length; i++)
    {
        gotoxy(position_body_x[i],position_body_y[i]);
        SetConsoleTextAttribute(uchwyt, color);
        cout<<(char)178;

    }
    //glowa
    gotoxy(position_x,position_y);
    SetConsoleTextAttribute(uchwyt, color);
    cout<<(char)219;

    //czyszczenie
    gotoxy(position_body_x[length],position_body_y[length]);
    SetConsoleTextAttribute(uchwyt, 0x11);
    cout<<(char)219;

    SetConsoleTextAttribute(uchwyt, color);

    SetConsoleTextAttribute(uchwyt, 7);
}

void Snake::move_snake(char t)
{
    switch (t)
    {
    case 'w':
    case 'i':
        position_y--;
        break;
    case 's':
    case 'k':
        position_y++;
        break;
    case 'a':
    case 'j':
        position_x--;
        break;
    case 'd':
    case 'l':
        position_x++;
        break;
    }
}

void Snake::Show_Name (int x,int y)

{
        SetConsoleTextAttribute(uchwyt, 0x70);
         int lnf = name.size();
         gotoxy(x-(lnf/2),y);
         cout<<" "<<name<<" ";

         gotoxy((x)-4,y+3);
         cout<<" "<<" Score: "<<score<<" ";

         gotoxy((x)-4,y+6);
         cout<<" Length: "<<length<<" ";

    SetConsoleTextAttribute(uchwyt, 0x07);
}

bool Snake::Snake_Colision ()

{
    for (int i=0;i<=length;i++)
    {
        if (position_x==position_body_x[i]&&position_y==position_body_y[i])
            return true;
    }
    return  false;
}

bool Snake::Apple_Colision (Apple t)

{
    if (position_x==t.position_x&&position_y==t.position_y)
        return true;
    else
        return false;
}

void Snake::Ad_Score (int s,int l)
{
 score+=s;
    if (score<0)
        score=0;

 length+=l;
}

bool Snake::Apple_Colision_body (Apple t)

{
    for (int i =0;i<length;i++)
    {
        if (position_body_x[i]==t.position_x&&position_body_y[i]==t.position_y)
        return true;

    }
        return false;
}

void Snake::set_player_name(string t)
{
        if (t.size()>11)
    {
        t.resize(10);
        name=t;
    }
   name=t;
}

ostream & operator<<(ostream &os, Snake t)

{
    os<<"Your Score: "<<t.score<<" your length: " <<t.length;
    return os;
}

string Snake::get_player_name()
{
    return name;
}

bool Snake::operator>(const Snake & t)const
{
    if (t.length>length)
        return false;
    else
        return true;
}

void Snake::save_to_Ranking(Ranking t[], int m)

{
    for (int i = 0; i<51;i++)
    {
    if (t[i].length==0)
    {
    t[i].score=score;
    t[i].length=length;
    t[i].time=m;
    t[i].name=name;
    break;
    }
    }
}

bool Snake::operator==(const Snake & t)const

{
    for (int i = 0;i<500;i++)
    {
       if (position_x==t.position_body_x[i]&&position_y==t.position_body_y[i])
            return true;
    }
            return false;
}

