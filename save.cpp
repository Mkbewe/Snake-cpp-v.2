#include <iostream>
#include <fstream>
#include <algorithm>

#include "save.h"
#include "snake.h"

using namespace std;


void ranking_save (Ranking player[])

{
    sort (player,player+50);
    fstream plik;
    plik.open("ranking.txt",ios::out );
    int i=0;
    while (player[i].length!=0)
    {
        plik<<player[i].name<<endl;
        plik<<player[i].score<<endl;
        plik<<player[i].length<<endl;
        plik<<player[i].time<<endl;
        i++;
    }
    plik.close();
}

void ranking_load (Ranking player[])

{

    fstream plik;
    plik.open("ranking.txt",ios::in);
    if(plik.good()==false)
    {
        cout<<"Plik nie istnieje";
    }

    string linia;
    string snick;
    int nr_lini=1,index=0;

    while (getline(plik,linia))
    {
        switch(nr_lini)
        {
        case 1:
            player[index].name=linia;
            break;
        case 2:
            player[index].score=atoi(linia.c_str());
            break;
        case 3:
            player[index].length=atoi(linia.c_str());
            break;
        case 4:
            player[index].time=atoi(linia.c_str());
            break;
        }

        nr_lini++;
        if (nr_lini==5)
        {
            nr_lini=1;
            index++;
        }
    }

    plik.close();
}
