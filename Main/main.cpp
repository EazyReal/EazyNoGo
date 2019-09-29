#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>

//lib of algorithms for game
#include "../Board/board.h"
#include "../Agent/random_agent.h"

#define NAME "EazyNoGo"
#define VERSION "0.1" //0=beta
#define BOARDSZ 9
#define BOARDVL 81
#define BLACK 0
#define WHITE 1
#define RESIGN 0.2

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
}

int main(int argc, char** argv)
{
  //some setting, initialization
  board env; env.clear();
	RandomAgent agent;
	//loop for gtp input and output
  string cmd, color, pos, tmp; //cmd, color, position
	//color black is represented by bool 0
  while(cin >> cmd)
  {
		if(cmd[0] == "play")
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
			if(color[0] == 'b' || color[0] == 'B') c = BLACK; else c = WHITE;
			//the agent make choices
			int a_max = agent.best_action(env, c);
			int wr = agent.calc_winrate(env, c);
			if(cmd[0] == 'g') env.add(a_max, c);
			if(wr < RESIGN) cout << "=resign" << endl << endl;
			else cout << '=' << Int2GTP(a_max) << endl << endl;
		}
		else if(cmd == "protocol_version") { cout << "=2" << endl << endl;}
		else if(cmd == "name") {cout << "=" << NAME << endl << endl;}
		else if(cmd == "version") {cout << "=" << VERSION << endl << endl;}
		else if(cmd == "known_command")
		{
			for(int i = 0;i < 11; i++) if(cmd == known_commands[i]) {cout << "=" << true << endl << endl; continue;}
			cout << "=" << false << endl << endl; continue;
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
		else{ cout << "=" << endl << endl;}
	}
  //end loop for gtp input and output
}
