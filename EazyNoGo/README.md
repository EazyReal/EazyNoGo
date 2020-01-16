#hyper params

mcts:
\#define USEROUNDS bool (use roud or time)
\#define DEFAUT_TIME_PER_STEP (time_t(0.5*CLOCKS_PER_SEC))
\#define DEFAUT_SIMS 50000(if use round, the round num)
\#define BLOCKSIZE 50(if use time, the check time block size)

uctnode:
BASENUM RBASENUM double(for stablizing beginnnig)
UCB_C(for ucb tuning)
eps(for maxQ & double)
USERAVE (ifndef)
RAVEK the threshold that no rave is more important then rave
