#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include <iostream>
#include <fstream>

struct Ranking
{
  std::string name;
  int score;
  int length;
  int time;

   bool operator < (const Ranking &x)const //to umozliwa sortowanie
    {
        return length>x.length;
    }
};

void ranking_save (Ranking player[]);
void ranking_load (Ranking player[]);

#endif // SAVE_H_INCLUDED
