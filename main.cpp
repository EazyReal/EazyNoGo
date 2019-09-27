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
      bool j,f=false;
      int st,e;
      cin>>c;
      j=!b.just_play_color();
      for(i=0;i<BOARDSZ;i++)
      {
        if(b.check(i,j))
        {
          f=true;
          break;
        }
      }
      if(!f)
      {
        cout<<"=resign"<<endl<<endl;
        continue;
      }
      tree.reset(b);
      e = st = clock();
      int simulationFinishedCnt = 0;
      //while(e-st<t)
      while(simulationFinishedCnt < simulationCnt)
      {
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        tree.run_a_cycle();
        simulationFinishedCnt +=10;
        e=clock();
        if(simulationFinishedCnt %10000==0)
        {
          tree.show_path();
        }
      }
      k= tree.root -> getbestmove();
      ucbnode* tmp = tree.root -> childptr;
      int best_move = (tmp+k)->place;
      policy = tree.root->getPolicy();
      tree.root ->show_child();
      value = tree.root ->show_inf(k);
      cerr<<"simulation time : "<< (double)(e-st) / 1000.0<<endl;
      cerr<<"average deep : "<<(double)tree.total / (double)i<<endl;
      cerr<<"total node : "<< tree.totalnode<<endl;
      cerr<<"average speed : "<< (simulationFinishedCnt*1000) / (e-st) <<endl;
      tree.show_path();
      if(s != "reg_genmove")
    b.add(best_move, !b.just_play_color());
  if(value > 0.2)
  {
    cout<<"="<<inttoGTPstring(best_move)<<endl<<endl;
  }else
  {
    cout<<"=resign"<<endl<<endl;
  }

  tree.clear();

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
}else if(s== "time")
{
  cin>>t;
  t*=1000;
  t++;
  cout<<"="<<endl<<endl;
}else if(s == "boardsize")
{
  cin>>s;
  cout<<"="<<endl<<endl;
}else if(s == "komi")
{
  cin>>s;
  cout<<"="<<endl<<endl;
}else if(s == "time_left")
{
  cin>>s>>s>>s;
  cout<<"="<<endl<<endl;
}else if(s == "showboard" || s == "sb")
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
