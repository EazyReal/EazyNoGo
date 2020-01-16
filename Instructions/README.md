# EazyNoGo

practice MCTS(+RAVE) implementation with nogo
using GoGUI, GTP2 protocol, and board of HaHaNoGo

structure:
/EazyNoGo is for eazynogo program(board part = hahanogo)
/HaHaNoGo is cloned hahanogo program
/Results is for saving games (.sgf and .dat)
/Instructions is for reading
/gogui-1.4.9 is for gogui-gtp communications between programs

usage:
gogui-1.4.9/bin/gogui-twogtp
gogui-twogtp -black "python3 xxx.py xxx xxx" -white "./hahanogo xxx" -size 9 -auto -games 1000 -sgffile results

@EazyNoGo/
gogui-1.4.9/bin/gogui-twogtp -black "EazyNoGo/eazynogo" -white "HaHaNoGo/hahanogo" -size 9 -auto -games 1 -sgffile Results/results
test.sh can be use to compile and test against hahanogo quickly
gogui.sh for more general testing between two execution file




reference:
hahanogo project : https://github.com/lclan1024/HaHaNoGo
gogui download : http://gogui.sourceforge.net/
gtp2 documentations : https://www.lysator.liu.se/~gunnar/gtp/gtp2-spec-draft2.pdf
mcts-rave algorithm : http://www.cs.utexas.edu/~pstone/Courses/394Rspring13/resources/mcrave.pdf
