#include "mcts.h"

//#define DEBUG

//btw beause of base num stablize the initial Q(s,a)m, thus unexplored child will always get accesed before win 1 child


void MCTS::init_with_board(board b)
{
  root = new Node;
  root_board = b; //copy a board
  root->initNode(NULL, root_board.just_play_color(), BOARDSZ, 0, 0);
  //use NULL, BOARDSZ, 0, 0 for last action doesnt matter
  root->expand(root_board,rave_num,rave_cnt);
  total = 0;
}

void MCTS::reset()
{
  simu_board = root_board; //reset select simulation board(bpath, wpath will be rested)
  path.clear(); //clear select path
  rave_path[0].clear();
  rave_path[1].clear();
}

Node* MCTS::select(Node* r)
{
  Node* cur = r;
  path.push_back(cur);
  while(cur->cptr.size()) //if cptr.size() = 0, not expanded or game over
  {
    #ifdef DEBUG
    cout << "calc best start\n";
    #endif
    cur = cur->best_child();
    #ifdef DEBUG
    cout << "calc best done\n";
    #endif
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
    rave_path[0].push_back(simu_board.wpath[i]);
  return (res == -1);
}

void MCTS::backpropogation(bool res)
{
  //update the sim_tree part with path, and child's rave value with rave_path
  //rave_path[0/1][i] ~= path[i*2]
  for(int t = 0; t < path.size(); t++)
	{
		path[t]->update(res);
    //update child's rave value because expansion method create unexplored children
    //these children need good heuristic
    bool c = !path[t]->color; //c is the color of its children
    for(int tp = t/2; tp < rave_path[c].size(); tp++)
    {
      int k = path[t]->idx[rave_path[0][tp]];
      if( k !=-1) path[t]->cptr[k]->rave_update(res);
    }
	}
}

int MCTS::best_action(board init_b, bool color, time_t time_limit) //gen random playable move
{
  init_with_board(init_b);
  time_t start_t, cur_t;
  start_t = clock();
  cur_t = clock();

  while(start_t + time_limit > cur_t)//while time available
  {
    for(int block_i = 0; block_i < BLOCKSIZE; block_i++) //do blocksz cycles
    {
      reset();
#ifdef DEBUG
      cout << "reset done\n";
#endif
      //selection
      Node* selected_root = select(root);
#ifdef DEBUG
      cerr << "select done\n";
#endif
      //expansion
      bool res;
      int nc = selected_root->expand(simu_board, rave_cnt, rave_num);
#ifdef DEBUG
      cerr << "expand done\n";
#endif
      if(nc == 0)
      {
        res = simu_board.just_play_color();
      }
      else{
        //simulation
        res = roll_out();
      }
#ifdef DEBUG
      cerr << "simulation done\n";
#endif
      //backpropogation
      backpropogation(res);
#ifdef DEBUG
      cerr << "backpro done\n";
#endif
    }
    cur_t = clock();
  }

  Action maxA = root->best_child()->pos;

  assert(cur_t < start_t + time_limit + time_limit); //for no inf loop;
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
