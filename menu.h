#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "screen.h"

#endif // MENU_H_INCLUDED

class Menu
{
private:
    bool mode;
    bool mode2;
    int position_x,position_y;
    std::string name;
    std::string name2;
    void gotoxy(int x, int y);
public:
    Menu(int x,int y,std::string button="text",std::string button2="text");
    ~Menu();

     void set_mode2 (bool m2);
     bool Is_mode2 ();
     void show (bool m=false);
};
