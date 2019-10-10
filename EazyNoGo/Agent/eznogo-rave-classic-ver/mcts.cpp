#include "mcts.h"

//#define DEBUG

void MCTS::init_with_board(board b)
{
  root = new Node;
  root_board = b; //copy a board
  root->initNode(NULL, BOARDVL, root_board.just_play_color());//2019.10.10.17:09....
  //use NULL, BOARDSZ, 0, 0 for last action doesnt matter
  root->expand(root_board);
  total = 0;
}

void MCTS::reset()
{
  simu_board = root_board; //reset select simulation board(bpath, wpath will be rested)
  path.clear(); //clear select path
  rave_path[0].clear();
  rave_path[1].clear();
  simu_boardb.bpsize=0;
	simu_boardb.wpsize=0;
}

Node* MCTS::select(Node* r)
{
  Node* cur = r;
  path.push_back(cur);
  while((cur->cnt > BASENUM||cur = r)  && cur->cptr.size()) //if cptr.size() = 0, not expanded or game over
  {
    cur = cur->best_child();
    simu_board.add(cur->pos, cur->color);
    rave_path[cur->color].push_back(cur->pos);
    path.push_back(cur);
  }
  return cur;
}

bool MCTS::roll_out() //the one in the board
{
  bool c = !simu_board.just_play_color(); //c = cur player to move
  //getv update info for rollout by pointer and reference
  simu_board.getv(bpos, wpos, bothpos, bpos_sz, wpos_sz, bothpos_sz);
  //simulate the rest of board, record is in b
  //res == 1 => black(0)player win
  int res = simu_board.simulate(c, bpos, wpos, bothpos, bpos_sz, wpos_sz, bothpos_sz);
  //update the simu actions to my rave_path vec
  for(int i = 0; i < simu_board.bpsize; i++)
    rave_path[0].push_back(simu_board.bpath[i]);
  for(int i = 0; i < simu_board.wpsize; i++)
    rave_path[1].push_back(simu_board.wpath[i]); //bugged until 2019/10/0 18:22
  return (res == -1);
}

void MCTS::backpropogation(bool res)
{
  //update the sim_tree part with path, and child's rave value with rave_path
  //rave_path[0/1][i] ~= path[i*2]
  for(int t = 0; t < path.size(); t++)
	{
		path[t]->update(res);
    bool c = path[t]->color;
    //update subtree action value AMAF
    for(int tp = 0; tp < rave_path[c].size(); tp++) //the former play matters more in nogo
    {
      if(rave_path[c][tp] == path[t]->pos) path[t]->rave_update(res);
    }
	}
}

Action MCTS::best_action(board init_b, bool color, int simu_per_step)
{
  init_with_board(init_b);
  time_t start_t, cur_t;
  start_t = clock();
  cur_t = clock();

  for(int ep = 0; ep < simu_per_step; ep++){
      reset();
      //selection
      Node* selected_root = select(root);
      //expansion
      bool res;
      int nc = selected_root->expand(simu_board);
      if(nc == 0)
      {
        res = simu_board.just_play_color();
      }
      else{
        Node* cur = selected_root->best_child();
        simu_board.add(cur->pos, cur->color);
        rave_path[cur->color].push_back(cur->pos);
        path.push_back(cur);
        //simulation
        res = roll_out();
      }
      //backpropogation
      backpropogation(res);
  }
  //return result, forget to judge NULL at first
  Node *best_node = root->best_child();
  Action maxA = (best_node == NULL) ? -1 : best_node->pos;
#ifdef USETIME
  assert(cur_t < start_t + time_limit + time_limit); //for no inf loop;
#endif
  clear();
  return maxA;
}

double MCTS::calc_winrate(board b, bool color)
{
  return 0.5;
}

void MCTS::clear()
{
  delete root;
}
