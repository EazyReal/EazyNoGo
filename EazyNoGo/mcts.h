#ifndef MCTSH
#define MCTSH
#include"bitboard.h"
#include"boardcn.h"
#include"board.h"
#include"uctnode.h"
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
#define DEFAUT_TIME_PER_STEP (time_t(0.5*CLOCKS_PER_SEC))
#define BLOCKSIZE

typedef int Action;//for clarity

using namespace std;

class MCTS
{
public:
  Action best_action(board b, bool color, time_t time_limit = DEFAUT_TIME_PER_STEP);
  double calc_winrate(board b, bool color);
  void init_with_board(board b); //init MCTS with board
  void reset(); //reset board and path before each cycle
  void clear(); //clear MCTS by delete root

  Node* select(Node* r);
  void roll_out();
  void backpropogation();

  int total;
  Node* root; //the current position to play
  board root_board; //root board should be saved
  board simu_board; //board for slect + simulation
  vector<Node*> path; //record path of each select
  vector<Action> rave_path[2]; //for amaf rave value update
  //heuristic rave value, not used in ver1
  double rave_cnt[2][BOARDVL+1]; //rave count, amaf, action taken = counted
  double rave_num[2][BOARDVL+1]; //rave value, amaf, dont consider (S,A) only A
  //note that the way to add rava value is
  //run over selected path, update selected move's child's rave val once
  //if the child have a action in select + simulation method(should be after?)

  //rollout follows that both player try to capture both can play positions first
  //my idea is the same as haha nogo, so some of its board functions for rollout is used
  int bpos[BOARDVL+1], wpos[BOARDVL+1], bothpos[BOARDVL+1]; //for recoding possible move to play for rollout
  int bpos_sz, wpos_sz, bothpos_sz; //vector sz

  //btw beause of base num stablize the initial Q(s,a)m, thus unexplored child will always get accesed before win 1 child
  //http://www.cs.utexas.edu/~pstone/Courses/394Rspring13/resources/mcrave.pdf simu_tree+simu_defaut is a good way to think
};


#endif //MCTSH
