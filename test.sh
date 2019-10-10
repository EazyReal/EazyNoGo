#2019/10/9 ver1.2
#author: maxwill lin, contact me @ 0312fs3@gmail.com
#usage:
#build new exe from eznogo program(Eazynogo/ g++ *.cpp -o newvername)
#and compete with EazyNoGo/black vs HaHaNoGo/white in Results/balck-white/games
#ver 1.1 2019/10/9 11:14 tested ok
#ver 1.2 can test with hahanogo with different rounds

#PATH = ?
#export path

read -p "input new ver(build form Eazynogo/*.cpp): " newver
cd EazyNoGo/
g++ *.cpp -o ${newver}
cd ..

read -p "input black program(EazyNoGo/): " black
read -p "input HaHaNoGo strength by simulation rounds: " whitenum
read -p "game number(w vs b gnum + b vs w gnum): " gamenum

cd Results/
mkdir ${black}-haha${whitenum}
cd ..

gogui-1.4.9/bin/gogui-twogtp -black "EazyNoGo/${black}" -white "HaHaNoGo/hahanogo ${whitenum}" -size 9 -auto -games ${gamenum} -sgffile Results/${black}-haha${whitenum}/games-bvw
gogui-1.4.9/bin/gogui-twogtp -white "EazyNoGo/${black}" -black "HaHaNoGo/hahanogo ${whitenum}" -size 9 -auto -games ${gamenum} -sgffile Results/${black}-haha${whitenum}/games-wvb
