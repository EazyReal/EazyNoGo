#include "random_agent.h"

#define BOARDSZ 9
#define BOARDVL 81

int random_agent::best_action(board b, bool color) //gen random playable move
{
  std::random_device rd;
  std::default_random_engine gen = std::default_random_engine(rd());
  //std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

  int available_pos[BOARDVL];
  int cnt = 0;

  for(int i = 0; i < BOARDVL; i++)
  {
    if(b.check(i, c)) available_pos[cnt++] = i;
  }
  std::uniform_int_distribution<int> dis(0, cnt-1);

  return available_pos[dis(gen)];
}

double random_agent::calc_winrate(board b, bool color)
{
  return 0.5;
}
