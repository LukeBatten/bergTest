# Quickly make ANITA-4 root files w/ batch farm
#!/bin/bash

source /home/batten/.bashrc
export ANITA4_BASE_DIR=/unix/anita4/flight2016
export TREE_DIR=/home/batten/anitaTreeMaker

cd /home/batten/anitaTreeMaker/sendBatch

FIRSTRUN=1
LASTRUN=2

bold=$(tput bold)
normal=$(tput sgr0)

for ((n=${FIRSTRUN};n<=${LASTRUN};n++)); do

    cd /home/batten/anitaTreeMaker/sendBatch
    
    cp ANITA4rootifier.sh ANITA4rootifier$n.sh
    sed -i "s/^RUN=.*/RUN=$n/" ANITA4rootifier$n.sh
    qsub -q long -M luke.batten.15@ucl.ac.uk ANITA4rootifier$n.sh

    #./runEventFileMaker$n.sh  # for events onlycd ..
    #./runNonEventFileMaker.sh # house 
    #./runNonEventFileMakerWHead.sh # house + event headers
    #./runHeaderFileMaker.sh # header
    echo "${bold}Run $n submitted! ${normal}"
    echo "<----------------------------------------->"

    if [ $n == ${LASTRUN} ]; then
	echo "${bold}ANITA-4 data processed"
    fi
    
done
