#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>



#include "screen.h"
#include "menu.h"
#include "snake.h"
#include "apple.h"
#include "menus.h"
#include "save.h"

#pragma comment(lib,"Winmm.lib")

using namespace std;



using namespace std;

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGT = 10;

const int TIME_LIMIT = 120;
const short BONUS_APPLE = 100;

unsigned map_width=60;//szerokosc mapy  + PLAYER_WIDTH
unsigned height=15;    //wysokosc mapy  + PLAYER_HEIGT

const unsigned menu_width=75;
const unsigned menu_heigt=15;

int game_speed = 100;  //szybkosc gry
bool goodmode = false;
bool snaks_colision = true;
short Game_Mode = 2; // tryb gry 1/2 graczy
short Game_Mode_Time= 1; // tryb gry na czas lub nie
short Dificult = 2; // poziom trudnosci
short apple_bonus_frequency = 250;

Ranking ranking1[50] {"",0,0,0};

void show_time(int&);


int main()
{

    srand  (time (NULL));

    // Menu
    int w=1;
    ranking_load (ranking1);

    while (w)
    {
        cls();
        if (w==1)
        {
            w = main_menu();
        }

        if (w==10||w==20)
        {
            w = game_mode();
            continue;
        }
        else if (w==30)     //Opcje
        {
            w = options();
            if (w==31)
            {
                w = mapsize();
            }
            else if (w==41)
            {
                w = more();
            }
            continue;
        }
        else if (w==40)     //Ranking
        {
            w = ranking(ranking1);
            continue;
        }
        else if (w==50)     //Exit
        {
            cls();
            exit (0);
        }

// Ekran gry

        cls();

        Screen Map1 (map_width,height,Screen::one_player);
        Screen Map2 (map_width,height,Screen::two_player);


        int apple_x = rand() % map_width + 21;
        int apple_y = rand() % height + 5;

        Apple apple_simple(apple_x,apple_y);
        Apple apple_bonus(2,2,Apple::White);

        clock_t start,stop;
        start = clock();

        if (1==Game_Mode)   // jeden gracz
        {
            char direction='w';
            string tmp_player_name = enter_name();

            Snake Player1( ( (map_width/2) +PLAYER_WIDTH),( (height+PLAYER_HEIGT)/2));
            Player1.set_player_name(tmp_player_name);
            cls();
            Map1.show_screen();
            char last;

            Menu GameName (map_width/3+PLAYER_WIDTH,3,"Snake.v.2");
            GameName.show(true);

            int game_time = 0;

            bool IsEaten = true;
            PlaySound(TEXT("soundTruck.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            while (w!=1)
            {
                stop = clock();
                game_time=(int)(stop-start)/CLOCKS_PER_SEC;

                show_time(game_time);

                Player1.Show_Name(9,3);
                while (kbhit())
                {
                    char tmp;
                    tmp = getch();
                    tmp = tolower( tmp );

                    if (tmp=='w'||tmp=='s'||tmp=='a'||tmp=='d')
                    {
                        direction = tmp;
                        break;
                    }
                    else if (tmp==27)
                    {
                        w=1;
                        break;
                    }
                }

                if (direction=='w'&&last=='s')  direction='s';
                else if (direction=='s'&&last=='w')  direction='w';
                else if (direction=='a'&&last=='d')  direction='d';
                else if (direction=='d'&&last=='a')  direction='a';

                //wykrywanie kolizcji z cialem
                if (goodmode==false)
                    if (Player1.Snake_Colision()==true)
                    {
                        Sleep(500);
                        Player1.save_to_Ranking(ranking1,game_time);
                        w = lose(Player1);
                        PlaySound(NULL, 0, 0);
                        break;
                    }

                if (Game_Mode_Time==2&&game_time==TIME_LIMIT)
                {
                    Sleep(500);
                    getch();
                    Player1.save_to_Ranking(ranking1,game_time);
                    w = lose(Player1);
                    PlaySound(NULL, 0, 0);
                    break;
                }

                cout<<apple_simple;
                Player1.Show_Snake(direction);

                // sprawdzanie kolizji z jablkiem
                if (Player1.Apple_Colision(apple_simple))
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;
                    apple_simple.update_apple(apple_x,apple_y);

                    while (Player1.Apple_Colision_body(apple_simple)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_simple.update_apple(apple_x,apple_y);
                    }
                    Player1.Ad_Score(Dificult*5,1);
                }

                int apple_bonus_shoot = rand() % apple_bonus_frequency;

                if (IsEaten==true&&apple_bonus_shoot==BONUS_APPLE)
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;
                    apple_bonus.update_apple(apple_x,apple_y);

                    while (Player1.Apple_Colision_body(apple_bonus)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_bonus.update_apple(apple_x,apple_y);
                    }
                    IsEaten=false;
                    cout<<apple_bonus;
                }

                if (Player1.Apple_Colision(apple_bonus))
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;
                    apple_bonus.update_apple(apple_x,apple_y);

                    while (Player1.Apple_Colision_body(apple_bonus)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_bonus.update_apple(apple_x,apple_y);
                    }
                    IsEaten=true;
                    Player1.Ad_Score(Dificult*15,3);
                }
                //aktualizacja ostatniego ruchu
                last = direction;

                Sleep(game_speed);
            }
            ranking_save(ranking1);
            PlaySound(NULL, 0, 0);
        }

        else if (2==Game_Mode) //dwoch graczy
        {
            char direction='w';
            char direction2='i';

            Snake Player1( ( (map_width/3)+PLAYER_WIDTH),
                          ( height+PLAYER_HEIGT),Snake::Yellow,0,3);

            Snake Player2( ( (map_width-(map_width/3))+PLAYER_WIDTH),
                          (height+PLAYER_HEIGT),Snake::Green,0,3);

            string tmp_player_name = enter_name();
            Player1.set_player_name(tmp_player_name);

            tmp_player_name = enter_name();
            Player2.set_player_name(tmp_player_name);
            char last;
            char last2;

            cls();
            Map2.show_screen();
            Menu GameName (map_width/3+PLAYER_WIDTH,3,"Snake.v.2");
            GameName.show(true);

            bool IsEaten = true;
            int game_time = 0;
            PlaySound(TEXT("soundTruck.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            while (w!=1)
            {
                stop = clock();

                game_time=(int)(stop-start)/CLOCKS_PER_SEC;

                show_time(game_time);

                Player1.Show_Name(9,3);
                Player2.Show_Name(29+map_width,3);

                short keys_full_1 = 0;
                short keys_full_2 = 0;
                while (kbhit())
                {
                    char tmp;
                    tmp = getch();
                    tmp = tolower( tmp );

                    if (tmp=='w'||tmp=='s'||tmp=='a'||tmp=='d')
                        {direction = tmp;keys_full_1=1;}
                    else if (tmp=='i'||tmp=='k'||tmp=='j'||tmp=='l')
                        {direction2 = tmp;keys_full_2=1;}
                    else if (tmp==27)
                    {
                        w=1;
                        break;
                    }
                    else
                        char rubish = tmp;
                    if (keys_full_1+keys_full_2==2)
                            break;
                }

                //blokowanie mozliwosci zmiany kierunku o 180
                if (direction=='w'&&last=='s')  direction='s';
                else if (direction=='s'&&last=='w')  direction='w';
                else if (direction=='a'&&last=='d')  direction='d';
                else if (direction=='d'&&last=='a')  direction='a';

                //wykrywanie kolizcji z cialem
                if (goodmode==false)
                    if (Player1.Snake_Colision()==true||
                        snaks_colision==true&&Player1==Player2)
                    {
                        Sleep(500);
                        Player1.save_to_Ranking(ranking1,game_time);
                        Player2.save_to_Ranking(ranking1,game_time);
                        w = lose(Player1,Player2);
                        PlaySound(NULL, 0, 0);
                        break;
                    }

                if (direction2=='i'&&last2=='k')  direction2='k';
                else if (direction2=='k'&&last2=='i')  direction2='i';
                else if (direction2=='j'&&last2=='l')  direction2='l';
                else if (direction2=='l'&&last2=='j')  direction2='j';

                if (goodmode==false)
                    if (Player2.Snake_Colision()==true||
                        snaks_colision==true&&Player2==Player1)
                    {
                        Sleep(500);
                        Player2.save_to_Ranking(ranking1,game_time);
                        Player1.save_to_Ranking(ranking1,game_time);
                        w = lose(Player2,Player1);
                        PlaySound(NULL, 0, 0);
                        break;
                    }

                if (Game_Mode_Time==2&&game_time==TIME_LIMIT)
                {
                    Sleep(500);
                    getch();
                    if (Player1>Player2)
                    {
                        w = lose(Player2,Player1);
                        Player1.save_to_Ranking(ranking1,game_time);
                        Player2.save_to_Ranking(ranking1,game_time);
                        PlaySound(NULL, 0, 0);
                        break;
                    }
                    else if (Player2>Player1)
                    {
                        w = lose(Player1,Player2);
                        Player1.save_to_Ranking(ranking1,game_time);
                        Player2.save_to_Ranking(ranking1,game_time);
                        PlaySound(NULL, 0, 0);
                        break;
                    }
                }

                cout<<apple_simple;

                Player1.Show_Snake(direction);
                Player2.Show_Snake(direction2);

                bool IsColiion = false;

                if (Player1.Apple_Colision(apple_simple))
                {
                    IsColiion=true;
                    Player1.Ad_Score(Dificult*5,1);
                }
                else if (Player2.Apple_Colision(apple_simple))
                {
                    IsColiion=true;
                    Player2.Ad_Score(Dificult*5,1);
                }

                if (IsColiion==true)
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;

                    apple_simple.update_apple(apple_x,apple_y);

                    // sprawdzanie czy jab�ko nie wygenerowa�o sie w ciele

                    while (Player1.Apple_Colision_body(apple_simple)==true||
                            Player2.Apple_Colision_body(apple_simple)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_simple.update_apple(apple_x,apple_y);
                    }
                    IsColiion=false;
                }


                bool IsColiion2 = false;

                if (Player1.Apple_Colision(apple_bonus))
                {
                    IsColiion2=true;
                    Player1.Ad_Score(Dificult*15,3);
                }
                else if (Player2.Apple_Colision(apple_bonus))
                {
                    IsColiion2=true;
                    Player2.Ad_Score(Dificult*15,3);
                }

                int apple_bonus_shoot = rand() % apple_bonus_frequency;


                if (IsEaten==true&&apple_bonus_shoot==BONUS_APPLE)
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;
                    apple_bonus.update_apple(apple_x,apple_y);

                    while (Player1.Apple_Colision_body(apple_bonus)==true||
                            Player2.Apple_Colision_body(apple_bonus)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_bonus.update_apple(apple_x,apple_y);
                    }
                    IsEaten=false;
                    IsColiion2=false;
                    cout<<apple_bonus;
                }

                if (IsColiion2)
                {
                    int apple_x = rand() % map_width + 21;
                    int apple_y = rand() % height + 5;
                    apple_bonus.update_apple(apple_x,apple_y);

                    while (Player1.Apple_Colision_body(apple_bonus)==true||
                            Player2.Apple_Colision_body(apple_bonus)==true)
                    {
                        int apple_x = rand() % map_width + 21;
                        int apple_y = rand() % height + 5;
                        apple_bonus.update_apple(apple_x,apple_y);
                    }
                    IsEaten=true;
                    IsColiion2=false;
                }

                //aktualizacja ostatniego ruchu
                last = direction;
                last2 = direction2;

                Sleep(game_speed);
            }
            ranking_save(ranking1);
            PlaySound(NULL, 0, 0);
        }

        char Exit;
        Exit=getch();
        if (Exit==27)
        {
            cls();
            w=1;
        }

    }

    return 0;
}

void show_time(int &t)
{
    if (Game_Mode_Time==1)
    {
        HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
        Menu show_time (PLAYER_WIDTH+map_width/1.5,3,"Time: ");
        show_time.show(true);
        SetConsoleTextAttribute(uchwyt, 0x70);
        cout<<t<<" ";
        SetConsoleTextAttribute(uchwyt, 0x07);
    }
    else if (Game_Mode_Time==2)
    {
        HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
        Menu show_time (PLAYER_WIDTH+map_width/1.5,3,"Time: ");
        show_time.show(true);
        SetConsoleTextAttribute(uchwyt, 0x70);
        cout<<TIME_LIMIT-t<<" ";
        SetConsoleTextAttribute(uchwyt, 0x07);
    }

}

