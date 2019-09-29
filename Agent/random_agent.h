#ifndef RANDOMAGENTH
#define RANDOMAGENTH
#include"../Board/bitboard.h"
#include"../Board/boardcn.h"
#include"../Board/board.h"
#include<iostream>
#include<map>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<random> //new random lib c++14
#include<math.h>
#define BLACK 0
#define WHITE 1

using namespace std;

class RandomAgent
{
public:
  int best_action(board b, bool color);
  double calc_winrate(board b, bool color);

private:
}


#endif //RANDOMAGENTH
