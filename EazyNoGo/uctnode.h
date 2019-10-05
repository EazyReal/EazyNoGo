#ifndef MCTSH
#define MCTSH
#include"bitboard.h"
#include"boardcn.h"
#include"board.h"
#include<iostream>
#include<map>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<random> //new random lib c++14
#include<math.h>
#include <ctime>
#define BLACK 0
#define WHITE 1

#define BOARDSZ 9
#define BOARDVL 81
#define BASENUM 10

typedef int Action; //for clarity

using namespace std;

class Node
{
public:
  Node* parent; //its parent
  bool color; //last color
  Action pos; // last polay pos
  double num, cnt; //value;
  double log_cnt;
  double rnum, rcnt; //rave value, like after-Action Q-value IMO

  int idx[BOARDVL+1]; //idx: board pos => cptr idx
  vector<Node*> cptr; //children of the node

  void initNode(Action i,bool c,double rcnt,double rnum);
  void expand(board& b, double rave_cnt[2][BOARDVL], double rave_num[2][BOARDVL]);
  void update();

private:
};


#endif //MCTSH
