#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <iostream>
#include <windows.h>

// kolory 0x41E bialy na niebieskim

class Screen
{
public:
    enum Mode {one_player,two_player,non} ;
    enum Color {Color_1 = 0x41E, Color_2 = 0xF0};
private:
   int width,height;
   //Player_width szerokosc okna gracza
   //Min_height wysokosc okna gracza
   int Player_width, Min_height;
   Mode mode;
   Color color;
   //void gotoxy(int x, int y);
   void paint_screen (Color c);
   void show_screen_player(Mode m, Color c); // rysuje okno gracza
public:
    Screen(int w=75,int h=15,Mode m=one_player,Color c=Color_1,int  wmin = 20,int hmin = 10);
    ~Screen();
    void show_screen();
};

#endif // SCREEN_H_INCLUDED
