#ifndef BOARDH
#define BOARDH

#include<iostream>
#include<map>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<math.h>

#define BLACK 0
#define WHITE 1

using namespace std;

class Board
{
  void reset();
  void step();
  void render();
  bool is_legal();
}


#endif //BOARDH
