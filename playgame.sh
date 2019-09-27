PATH=$PATH:./gogui-1.4.9/bin/
export PATH

read -p "the cmd for executing black program:" blackp
read -p "the cmd for executing white program:" whitep
read -p "the cmd for executing white program:" whitep
gogui-twogtp -black ${blackp} -white ${whitep} -size 9 -auto -games 1000 -sgffile results
