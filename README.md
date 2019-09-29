# EazyNoGo

practice MCTS+RAVE implementation with nogo
using GoGUI and GTP2 protocol

usage:
gogui-1.4.9/bin/gogui-twogtp
gogui-twogtp -black "python3 xxx.py xxx xxx" -white "./HaHaNoGo xxx" -size 9 -auto -games 1000 -sgffile results
gogui-twogtp -black "../../EazyNoGo/eazynogo" -white "../../HaHaNoGo/hahanogo" -size 9 -auto -games 1 -sgffile results

reference:
hahanogo project : https://github.com/lclan1024/HaHaNoGo
gogui download: http://gogui.sourceforge.net/
gtp2 documentations : https://www.lysator.liu.se/~gunnar/gtp/gtp2-spec-draft2.pdf
