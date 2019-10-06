#include "uctnode.h"

Node::Node(){};

Node::~Node()
{
  for(int i = 0; i < cptr.size(); i++)
  {
    delete cptr[i];
  }
  cptr.clear();
};

inline double Node::getQ()
{
  double Q, beta;
  if(USERAVEQ)
  {
    beta = rcnt/(cnt+rcnt+4*cnt*RAVEB*rcnt*RAVEB);
    Q = (1-beta)*(num/cnt)+beta*(rnum/rcnt);
  }
  else{
    //assert(parent != NULL);
    Q = (num/cnt) + UCB_WEIGHT*sqrt(parent->log_cnt/cnt);
  }
  return Q;
}


Node* Node::best_child()
{
  //should not use this condition:)
  if(cptr.empty()) return NULL;

  vector<Node*> maxC;
  double maxQ = cptr[0]->getQ();
  maxC.push_back(cptr[0]);
  const double eps = 0.005; //to deter if the value is close enough(to try both) in double

  for(int i = 1;i < cptr.size(); i++)
  {
    double curQ = cptr[i]->getQ();
    double delta = curQ - maxQ;
    if(delta > eps)
    {
      maxQ = curQ;
      maxC.clear();
      maxC.push_back(cptr[i]);
    }else if(delta > -eps){
      maxC.push_back(cptr[i]);
    }
  }
  std::uniform_int_distribution<int> dis(0, maxC.size()-1);
  return maxC[rand()%maxC.size()];
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
  bool c = !b.just_play_color(); //get player color
  for(Action p = 0; p < BOARDVL; p++)if(b.check(p, c))
  {
    idx[p] = cptr.size();
    Node *ptr =  new Node;
    ptr->initNode(this, p, c, rave_cnt[c][p], rave_num[c][p]);//use rave heuristic
    cptr.push_back(ptr);
  }
  return cptr.size(); // may use this
}

void Node::initNode(Node* p,Action i,bool c,double rcnt,double rnum)
{
  this->parent = p; //parent = parent => bugged
  memset(idx, -1, sizeof(idx));
  color = c;
  pos = i;
  num = BASENUM/2.0;
  cnt = BASENUM; //stablize the beginnnig of training
  //todo:r heuristic
  rnum = BASENUM/2.0;
  rcnt = BASENUM;
  log_cnt = log(BASENUM); //
}