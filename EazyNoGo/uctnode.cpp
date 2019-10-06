#include "uctnode.h"

Node::Node(){};

Node::~Node()
{
  if(cptr != NULL)
  {
    delete [] cptr;
    cptr = NULL;
  }
};

inline double Node::getQ()
{
  double Q, beta;
  if(RAVE)
  {
    beta = rcnt/(cnt+rcnt+4*cnt*RAVEB*rcnt*RAVEB);
    Q = (1-beta)*(num/cnt)+beta*(rnum/rcnt);
  }
  else{
    Q = (num/cnt) + UCB_WEIGHT*sqrt(parent->log_cnt/cnt);
  }
  return Q;
}


Node* Node::best_child()
{
  //should not use this condition:)
  if(cptr.isempty()) return NULL;

  vector<Node*> maxC;
  double maxQ = cptr[0]->getQ();
  maxC.push_back(cptr[0]);
  const double eps = 0.005; //to deter if the value is close enough(to try both) in double

  for(int i = 1;i < cptr.size(); i++)
  {
    double curQ = cpt[i]->getQ();
    double delta = curQ - maxQ;
    if(delta > eps)
    {
      maxQ = curQ
      maxC.clear();
      maxC.push_back(cptr[i]);
    }else if(delta > -eps){
      maxC.push_back(cptr[i]);
    }
  }
  std::uniform_int_distribution<int> dis(0, maxC.size()-1);
  return maxC[dis(gen)];
}

void Node::update(bool result)
{
  if((result&&color) || ((!result)&&(!color))) num++;
  cnt++;
  log_cnt = log(cnt);
}

void Node::rave_update(bool result)
{
  if((result&&color) || ((!result)&&(!color))) rnum++;
  rcnt++;
}

int Node::expand(board& b, double rave_cnt[2][BOARDVL], double rave_num[2][BOARDVL])
{
  //cptr.clear();
  bool c = !b.just_play_color; //get player color
  for(Action p = 0; p < BOARDVL; p++)if(check(p, c))
  {
    idx[p] = ctpr.size();
    Node *ptr =  new Node;
    ptr.initNode(this, p, c, rave_cnt[c][p], rave_num[c][p]);//use rave heuristic
    cptr.push_back(ptr);
  }
  return cptr.size(); // may use this
}

void Node::initNode(Node* parent,Action i,bool c,double rcnt,double rnum)
{
  parent = parent;
  memset(idx, -1, sizeof(idx));
  color = c;
  action = i;
  num = BASENUM/2.0;
  cnt = BASENUM; //stablize the beginnnig of training
  rnum = rnum;
  rcnt = rcnt;
  log_cnt = 1.0; //
}
