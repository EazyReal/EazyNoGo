#include "uctnode.h"

Node::Node(){};

Node::~Node()
{
  if(cptr != NULL)
  {
    delete [] cptr;
    cptr = NULL;
  }
}


int Node::expand(board& b, double rave_cnt[2][BOARDVL], double rave_num[2][BOARDVL])
{
  //cptr.clear();
  bool c = !b.just_play_color; //get player color
  for(Action p = 0; p < BOARDVL; p++)if(check(p, c))
  {
    idx[p] = ctpr.size();
    Node *ptr =  new Node;
    ptr.initNode(p, c, rave_cnt[c][p], rave_num[c][p]);//use rave heuristic
    cptr.push_back(ptr);
  }
  return cptr.size(); // may use this
}

void Node::initNode(Action i,bool c,double rcnt,double rnum)
{
  memset(idx, -1, sizeof(idx));
  color = c;
  action = i;
  num = BASENUM/2.0;
  cnt = BASENUM; //stablize the beginnnig of training
  rnum = rnum;
  rcnt = rcnt;
  log_cnt = 1.0; //
}
