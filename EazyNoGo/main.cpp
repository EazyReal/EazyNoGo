#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime> //clock = long, second =  clock()/CLOCKS_PER_SEC
#include <cassert>
#include<iomanip>

#define DEBUG

//lib of algorithms for game
#include "board.h"
#include "mcts.h"

#define NAME "EazyNoGo(MCTS+UCB+newRAVE)"
#define VERSION "6.0" //0=beta

//#define BOARDSZ 9
#define BOARDVL 81
#define BLACK 0
#define WHITE 1
//typedef int Action //for clarity

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
	MCTS agent;
	board env;
	env.clear();
	srand(time(NULL)) ;
	int simu_per_step = DEFAUT_SIMS;
	if(argc == 2) istringstream(string(argv[1])) >> simu_per_step;
	cerr << "simulate " << simu_per_step << "/step" << endl;
  string cmd, color, pos, tmp; //cmd, color(black = 0), position
	//loop for gtp input and output
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
			Action a_max = agent.best_action(env, c, simu_per_step);
			if(a_max == -1) {cout << "=resign" << endl << endl; continue;}
			if(cmd[0] == 'g') env.add(a_max, c);
			//note that the tree use board to search
			//should always balck first or will be wrong adding
			cout << '=' << Int2GTP(a_max) << endl << endl;
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
