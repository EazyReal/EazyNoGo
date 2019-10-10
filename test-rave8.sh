#2019/10/9 ver1.1
#author: maxwill lin, contact me @ 0312fs3@gmail.com
#usage:
#build new exe from eznogo program(Eazynogo/ g++ *.cpp -o newvername)
#and compete with EazyNoGo/black vs HaHaNoGo/white in Results/balck-white/games
#ver 1.1 2019/10/9 11:14 tested ok

#PATH = ?
#export path

read -p "input new ver(build form Eazynogo/*.cpp): " newver
cd EazyNoGo/
g++ *.cpp -o ${newver}
cd ..

read -p "input black program(EazyNoGo/): " black

cd Results/
mkdir ${black}-prave8
cd ..

gogui-1.4.9/bin/gogui-twogtp -black "EazyNoGo/${black}" -white "EazyNoGo/eazynogo-rave8" -size 9 -auto -games 5 -sgffile Results/${black}-prave8/games
