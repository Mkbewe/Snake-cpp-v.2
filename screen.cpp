#include <iostream>
#include <windows.h>

#include "screen.h"
#include "menus.h"


using  std::cout;
using  std::cin;
using  std::endl;
using  std::string;

Screen::Screen(int w,int h,Mode m,Color c,int wmin,int hmin)
{
    if (w<5)
        w=5;
    if (h<0)
        h=0;

    width=w;
    height=h;
    mode=m;
    color = c;
    Player_width = wmin;
    Min_height = hmin;
}

Screen::~Screen()
{
}



void Screen::show_screen_player(Mode m,Color c)

{
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    int orgin_player;

    if (m==one_player)
        orgin_player=2;
    else if (m==two_player)
        orgin_player=Player_width+width+2;

    SetConsoleTextAttribute(uchwyt, c); //zielony

    if (m==one_player)
    {
        gotoxy(1,1);
        cout<<(char)201;
    }

    // poziomo gracz

    for (int i=orgin_player; i<Player_width+orgin_player-2; i++)
    {
        gotoxy(i,1);
        cout<<(char)205;
    }
    if (m==one_player)
    {
        cout<<(char)203;
        gotoxy(1,Min_height+height);
        cout<<(char)200;
    }
    else if  (m==two_player)
        cout<<(char)187;

    gotoxy(1,Min_height+height);
    cout<<(char)200;

//srodek

    for (int i=orgin_player; i<Player_width+orgin_player-2; i++)
    {
        gotoxy(i,4);
        cout<<(char)205;
    }

//dol

    for (int i=orgin_player; i<Player_width+orgin_player-2; i++)
    {
        gotoxy(i,Min_height+height);
        cout<<(char)205;
    }
    if (m==one_player)
    {
        cout<<(char)202;
    }
    else if  (m==two_player)
        cout<<(char)188;

    // pionowo gracz

    // lewa linia

    if (m==one_player)
    {
        for (int i=2; i<Min_height; i++)
        {
            gotoxy(orgin_player-1,i);
            if (i==4)
                cout<<(char)204<<endl;
              else
                cout<<(char)186<<endl;
        }
    }

    // srodkowa linia

    for (int i=2; i<Min_height; i++)
    {
        gotoxy(Player_width+orgin_player-2,i);
        if (i==4)
        {
            if (m==one_player)
                cout<<(char)206;
            else if (m==two_player)
                cout<<(char)185;
        }
        else
            cout<<(char)186;
    }
    //prawa linia

    if (m==one_player)
    {
        for (int i=2; i<Min_height; i++)
        {
            gotoxy(Player_width+1+width,i);
            if (i==4&&mode==one_player)
                cout<<(char)185;
            else if (i==4&&mode==two_player)
                cout<<(char)206;
            else
                cout<<(char)186;
        }
    }

    SetConsoleTextAttribute(uchwyt, 15);
}

void  Screen::show_screen()
{
    paint_screen(color);
    int window_width=0;

    if (mode==one_player)
    {
        show_screen_player(one_player,color);  // rysuje obszar dla pierwszego gracza
        window_width=Player_width;
    }
    else if (mode==two_player)
    {
        show_screen_player(one_player,color);
        show_screen_player(two_player,color);
        window_width=Player_width;
    }

    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(uchwyt, color); //zielony

// poziomo zmienne
//gora
    for (int i=window_width+1; i<window_width+1+width; i++)
    {
        gotoxy(i,1);
        cout<<(char)205;
    }
    gotoxy(window_width+1+width,1);
    if (mode==one_player)
        cout<<(char)187;
    else if (mode==two_player)
        cout<<(char)203;

//srodek

    for (int i=window_width+1; i<window_width+1+width; i++)
    {
        gotoxy(i,4);
        cout<<(char)205;
    }

//dol
    for (int i=window_width+1; i<window_width+1+width; i++)
    {
        gotoxy(i,height+Min_height);
        cout<<(char)205;
    }
    gotoxy(window_width+1+width,height+Min_height);
    if (mode==one_player)
        cout<<(char)188;
    else if (mode==two_player)
        cout<<(char)202;

// pionowo zmienne
//lewa linia

    if (mode!=non)
    {
    for (int i=Min_height; i<Min_height+height; i++)
    {
        gotoxy(1,i);
        cout<<(char)186;
    }
    // dla drugiego gracza
    if (mode==two_player)
    {
        for (int i=Min_height; i<Min_height+height; i++)
    {
        gotoxy(2*window_width+width,i);
        cout<<(char)186;
    }
    }

//srodkowa linia
    for (int i=Min_height; i<Min_height+height; i++)
    {
        gotoxy(window_width,i);
        cout<<(char)186;
    }
//prawa linia
    for (int i=Min_height; i<Min_height+height; i++)
    {
        gotoxy(window_width+1+width,i);
        cout<<(char)186;
    }
    }
    gotoxy(1,height+Min_height+1);
    SetConsoleTextAttribute(uchwyt, 0xF); //bialy
}

void Screen::paint_screen (Color c)

{
     HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(uchwyt, c);
     unsigned short m;
     if (mode==one_player)
        m=1;
     else if (mode==two_player)
        m=2;
     else if (mode==non)
        m=0;

        gotoxy(1,1);
     for (int j=1;j<=Min_height+height;j++)
     {
         for(int i=1;i<=(m*Player_width)+width;i++)
         {
             gotoxy(i,j);
             cout<<" ";
         }
     }

    gotoxy(1,Min_height+height+2);

    SetConsoleTextAttribute(uchwyt, 7);
}
