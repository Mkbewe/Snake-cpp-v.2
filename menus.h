#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "screen.h"
#include "snake.h"


extern const unsigned menu_width;
extern const unsigned menu_heigt;

extern unsigned map_width;//szerokosc mapy
extern unsigned height;    //wysokosc mapy
extern bool goodmode;
extern short Game_Mode_Time;
extern short Dificult; // poziom trudnosci
extern int game_speed;
extern short apple_bonus_frequency;
extern bool snaks_colision;

extern short Game_Mode;

void cls();


int main_menu();
int main_menu();
int game_mode();
int options();
int more();
int mapsize();
int ranking(Ranking[]);
void HideCursor();
void ShowCursor();
std::string enter_name();
int lose(Snake &t);
int lose(Snake &t,Snake &m);
void gotoxy(int x, int y);


#endif // MENUS_H_INCLUDED
