#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime> //clock = long, second =  clock()/CLOCKS_PER_SEC
#include <cassert>

#define DEBUG

//lib of algorithms for game
#include "board.h"
//#include "random_agent.h"
#include "mcts.h"

//#define NAME "EazyNoGo(MCTS+UCB)"
//#define VERSION "1.4" //0=beta
#define NAME "EazyNoGo(MCTS+UCB+RAVE)"
#define VERSION "2.8" //0=beta
//#define BOARDSZ 9
#define BOARDVL 81
#define BLACK 0
#define WHITE 1
#define RESIGN 0.2
//typedef int Action //for clarity

/*
hyper params

mcts:
#define USEROUNDS bool (use roud or time)
#define DEFAUT_TIME_PER_STEP (time_t(0.5*CLOCKS_PER_SEC))
#define DEFAUT_SIMS 50000(if use round, the round num)
#define BLOCKSIZE 50(if use time, the check time block size)

uctnode:
BASENUM double(for stablizing beginnnig)
UCB_C(for ucb tuning)
eps(for maxQ)
USERAVE bool
RAVEK the threshold that no rave is more important then rave
*/

using namespace std;

//protocol transformation
string Int2SGF(int i)
{
	string s = "aa";
	s[0] += (i/BOARDSZ);
	s[1] += (i%BOARDSZ);
	return s;
}

int GTP2Int(string s)
{
	if(s[0]>='a'&&s[0]<='z')
	{
		int x = s[0]-'a';
		if(s[0]>'i') x--;
		int y = s[1]-'1';
		return x*BOARDSZ+y;
	}else{
		int x = s[0]-'A';
		if(s[0]>'I')x--;
		int y = s[1]-'1';
		return x*BOARDSZ+y;
	}
}

string Int2GTP(int i)
{
	string s = "A1";
    s[0]+= i / BOARDSZ;
    if(s[0]>='I')s[0]++;
    s[1]+= i % BOARDSZ;
    return s;
}

string known_commands[11] =
{
	"protocol_version",
	"name",
	"known_command",
	"list_commands",
	"quit",
	"boardsize",
	"clear_board",
	"komi",
	"play",
	"genmove",
	"reg_genmove"
};

int main(int argc, char** argv)
{
  //some setting, initialization
  //board env; env.clear();
  //gen = std::default_random_engine(rd());
  //std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	//RandomAgent agent;
	MCTS agent;
	board env;
	env.clear();
	srand(time(NULL)) ;
	//loop for gtp input and output
  string cmd, color, pos, tmp; //cmd, color, position
	//color black is represented by bool 0
  while(cin >> cmd)
  {
		if(cmd == "play")
		{
			cin >> color >> pos;
			bool c;
			if(color[0] == 'b' || color[0] == 'B') c = BLACK; else c = WHITE;
			env.add(GTP2Int(pos), c);
			cout << '=' << endl << endl;
		}
		else if(cmd[0] == 'g' || cmd == "reg_genmove" )
		{
			cin >> color;
			bool c;
			if(color[0] == 'b' || color[0] == 'B') c = BLACK; else c = WHITE;

			//the agent make choices
			Action a_max = agent.best_action(env, c);
			if(a_max == -1) {cout << "=resign" << endl << endl; continue;}
			if(cmd[0] == 'g') env.add(a_max, c);

			if(agent.calc_winrate(env, c) < RESIGN) cout << "=resign" << endl << endl;
			else cout << '=' << Int2GTP(a_max) << endl << endl;
		}
		else if(cmd == "protocol_version") { cout << "=2" << endl << endl;}
		else if(cmd == "name") {cout << "=" << NAME << endl << endl;}
		else if(cmd == "version") {cout << "=" << VERSION << endl << endl;}
		else if(cmd == "known_command")
		{
			string tmp;
			cin >> tmp;
			bool flag = 0;
			for(int i = 0;i < 11; i++) if(tmp == known_commands[i]) {cout << "=" << true << endl << endl; flag = 1; break;}
			if(!flag) {cout << "=" << false << endl << endl;}
		}
		else if(cmd == "list_commands")
		{
			cout << "=";
			for(int i = 0;i < 11; i++) {cout << known_commands[i] << endl;}
			cout << endl << endl;
		}
		else if(cmd == "boardsize") {cin >> tmp; cout << "=" << endl << endl; }
		else if(cmd == "clear_board") {env.clear(); cout << "=" << endl << endl;}
		else if(cmd == "komi") {cin >> tmp; cout << "=" << endl << endl;}
		else if(cmd == "showboard" || cmd == "sb") //from hahanogo, debug usage
		{
			env.showboard();
			cout<<endl;
		}
		else{ cout << "=" << endl << endl;}
	}
  //end loop for gtp input and output
}
