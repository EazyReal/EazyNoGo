#2019/10/12 ver1.0
#author: maxwill lin, contact me @ 0312fs3@gmail.com
#usage:
#interactive gogui shell script

#PATH = ?
#export path


read -p "input program 1 command: " p1
read -p "input program 2 command: " p2
read -p "input number of games to simulate: " gamenum
read -p "input saving diectory name(/Results/name/)" res

cd Results/
mkdir res
cd ..

#gogui-1.4.9/bin/gogui-twogtp -black "EazyNoGo/eznogo61 1000000" -white "HaHaNoGo/hahanogo 1000000" -size 9 -auto -games 10 -sgffile Results/ez100w-haha100w/games

gogui-1.4.9/bin/gogui-twogtp -black "${p1}" -white "${p2}" -size 9 -auto -games ${gamenum} -sgffile Results/${res}/games-bvw &
gogui-1.4.9/bin/gogui-twogtp -white "${p1}" -black "${p2}" -size 9 -auto -games ${gamenum} -sgffile Results/${res}/games-wvb &
