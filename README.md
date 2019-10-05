# EazyNoGo

practice MCTS(+RAVE) implementation with nogo
using GoGUI, GTP2 protocol, and board of HaHaNoGo

structure:
/EazyNoGo is for eazynogo program(board part = hahanogo)
/HaHaNoGo is for hahanogo program, cloned from reference
/Results is for saving game .sgf and .dat
/Instructions is for reading
/gogui-1.4.9 is for gogui-gtp command

usage:
gogui-1.4.9/bin/gogui-twogtp
gogui-twogtp -black "python3 xxx.py xxx xxx" -white "./HaHaNoGo xxx" -size 9 -auto -games 1000 -sgffile results

@EazyNoGo/
gogui-1.4.9/bin/gogui-twogtp -black "EazyNoGo/eazynogo" -white "HaHaNoGo/hahanogo" -size 9 -auto -games 1 -sgffile Results/results


reference:
hahanogo project : https://github.com/lclan1024/HaHaNoGo
gogui download : http://gogui.sourceforge.net/
gtp2 documentations : https://www.lysator.liu.se/~gunnar/gtp/gtp2-spec-draft2.pdf
