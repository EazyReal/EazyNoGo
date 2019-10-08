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
  double Q = (num/cnt);
  //double UCB = sqrt(UCB_C*parent->log_cnt/cnt);
  double UCB = UCB_C*sqrt(parent->log_cnt/cnt);
  double rave_Q, beta;
  if(USERAVEQ)
  {
    //ver2.6
    rave_Q = (rnum/rcnt);
    beta = sqrt(RAVEK/(3*parent->cnt + RAVEK));
  }
  return USERAVEQ ? ((1-beta)*Q + beta*rave_Q + UCB) : (Q+UCB);
}


Node* Node::best_child()
{
  //should not use this condition:) or will let to segment fault
  if(cptr.empty()) return NULL;

  vector<Node*> maxC;
  double maxQ = cptr[0]->getQ();
  maxC.push_back(cptr[0]);
  const double eps = 0.001; //to deter if the value is close enough(to try both) in double

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

int Node::expand(board& b)
{
  //cptr.clear();
  bool c = !b.just_play_color(); //get player color
  for(Action p = 0; p < BOARDVL; p++)if(b.check(p, c))
  {
    idx[p] = cptr.size();
    Node *ptr =  new Node;
    ptr->initNode(this, p, c);
    cptr.push_back(ptr);
  }
  return cptr.size(); // may use this
}

void Node::initNode(Node* p, Action i, bool c)
{
  this->parent = p; //parent = parent => bugged
  memset(idx, -1, sizeof(idx));
  color = c;
  pos = i;
  num = BASENUM/2.0;
  cnt = BASENUM; //stablize the beginnnig of training //but may cuz UCB problem
  //todo:r heuristic
  rnum = BASENUM/2.0;
  rcnt = BASENUM;
  log_cnt = log(BASENUM); //may cuz UCB proble
}
