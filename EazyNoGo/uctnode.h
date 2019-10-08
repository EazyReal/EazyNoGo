#ifndef UCTH
#define UCTH
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

#define USERAVEQ 1
#define RAVEK 1000
#define UCB_C 0.25

typedef int Action; //for clarity

using namespace std;

//std::random_device rd;
//std::default_random_engine gen;

class Node
{
public:
  Node();
  ~Node();
  Node* parent; //its parent
  bool color; //last color
  Action pos; // last polay pos
  double num, cnt; //value;
  double log_cnt;
  double rnum, rcnt; //rave value, like after-Action Q-value IMO

  int idx[BOARDVL+1]; //idx: board pos => cptr idx
  vector<Node*> cptr; //children of the node

  void initNode(Node* parent, Action i, bool c, double rcnt, double rnum);
  int expand(board& b, double rave_cnt[2][BOARDVL], double rave_num[2][BOARDVL]);
  void update(bool result);
  void rave_update(bool result);
  Node* best_child();
  inline double getQ();

private:
};


#endif //UCTH
