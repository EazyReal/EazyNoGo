#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>

//lib of algorithms for game
#include "board.h" //to implement : step(), isempty(), clear()
#include "random_player.h"
#define BOARDSZ 9
#define BOARDVL 81

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

//hyper params
int simulation_n = 50000;

int main(int argc, char** argv)
{
  //some setting, initialization
  if (argc == 2)
	{
		istringstream (string(argv[1])) >> simulation_n;
		cerr << "set simulation step to: " << simulation_n << endl;
	}
  board b; b.clear();

  string cmd, color, pos; //cmd, color, position
  //bool last_color; //0 = black, 1 = white
  while(cin >> cmd)
  {
    if(cmd == "play" || cmd == "p" )
    {
      cin >> color >> pos;
      bool play_color = (color[0]=='b' || color[0]=='B') ? 0 : 1;
      b.step(GTP2Int(pos),play_color);
      cout << "=" << endl << endl;
    }
    else if(cmd[0] == 'e')
    {
      cout << b.isempty() << endl << endl;
    }
    else if(cmd[0] == 'c')
    {
      b.clear();
      cout << "=" << endl << endl;
    }
    else if(cmd[0] == 'g' || cmd == "reg_genmove")
    {
      cin >> color; //color to move, Generate the supposedly best move for either color
      bool color_to_play = !b.just_play_color();
			bool flag = false;
      for(int i = 0; i < BOARDVL; i++) if(b.check(i,color_to_play))
      { flag = true; break;}
      if(!flag)
      {
        cout << "=resign" << endl << endl; //resign ? wtf, what if some special case
        continue;
      }

//implement MCTS+RAVE
      if(s != "reg_genmove")
    		b.add(best_move, !b.just_play_color());
  		if(win_rate > 0.2)
  		{
    		cout<<"="<<Int2GTP(best_move)<<endl<<endl;
  		}else
  		{
    		cout<<"=resign"<<endl<<endl;
  		}


		}
		else if (s == "policy")
		{
  		for (int i = 0; i < 9; i++)
  		{
    		for (int j = 0; j < 9; j++)
    		{
      		cout << policy[i * 9 + j] << ' ';
    		}
    		cout << endl;
  		}

		}
		else if (s == "value")
		{
  		cout << value << endl;
		}
		else if (s == "protocol_version")
		{
  		cout<<"=2\n\n";
		}
		else if (s == "rev")
		{
  		int bsize, wsize, tsize;
  		int bone[BOARDSSIZE], wone[BOARDSSIZE], two[BOARDSSIZE];
  		float x;
  		cin >> x;
  		float sum = 0;
  		for (int i = 0; i < x; i++)
  		{
    		board tmpb = b;
    		tmpb.getv(bone, wone, two, bsize, wsize, tsize);
    		sum += tmpb.simulate(!tmpb.just_play_color(), bone, wone, two, bsize, wsize, tsize);
  		}
  		cout << sum / x << endl;
		}
		else if(s== "name")
		{
  		cout<<"=haha"<< UCB_WEIGHT * 100<<"_rn"<<ravenum<<"_bn"<<basenum << "\n\n";
		}
		else if(s== "time")
		{
  		cin>>t;
  		t*=1000;
  		t++;
  		cout<<"="<<endl<<endl;
		}
		else if(s == "boardsize")
		{
  		cin>>s;
  		cout<<"="<<endl<<endl;
		}
		else if(s == "komi")
		{
  		cin>>s;
  		cout<<"="<<endl<<endl;
		}
		else if(s == "time_left")
		{
  		cin>>s>>s>>s;
  		cout<<"="<<endl<<endl;
		}
		else if(s == "showboard" || s == "sb")
		{
  		b.showboard();
  		cout<<endl;
		}
		else
		{
  		cout<<"="<<endl<<endl;
		}
  }
  //loop for gtp input and output
}
