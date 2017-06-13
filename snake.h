#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <iostream>
#include "apple.h"
#include "save.h"

using std::string;


extern unsigned map_width;//szerokosc mapy + 20
extern unsigned height;    //wysokosc mapy + 10


class Snake
{
public:
    enum Color {Yellow = 0x1E, Green = 0x1A};
private:
    unsigned int position_x,position_y;
    unsigned int position_body_x[500] , position_body_y[500];
    int tmpx,tmpy;
    int score,length;
    string name;
    Color color;
    int time;

    void move_snake(char);
public:
    Snake(int x=(map_width/2)+20, int y =((height+10)/2),
          Color c = Yellow, int scr = 0, int len = 3);
    ~Snake ();

    void Show_Snake (char direction);
    void Show_Name (int x,int y);
    void Ad_Score (int s=1,int l=1);
    bool Snake_Colision ();
    bool Apple_Colision (Apple t);
    bool Apple_Colision_body (Apple t);
    void set_player_name(string t);
    void save_to_Ranking(Ranking t[], int m);
    string get_player_name();
    bool operator>(const Snake & t)const;
    friend ostream & operator<<(ostream &os, Snake t);
    bool operator==(const Snake & t)const;
};

#endif // SNAKE_H_INCLUDED
