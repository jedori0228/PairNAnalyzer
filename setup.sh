#!/bin/bash
export PLOTTER_WORKING_DIR=`pwd`
export FILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
#export PLOT_PATH=$PLOTTER_WORKING_DIR/plots/
export PLOT_PATH=/home/jskim/Dropbox/PairN_13TeV/plots/
export SCRIPT_DIR=$PLOTTER_WORKING_DIR/script/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/
export CATVERSION="v8-0-7"
export CATANVERSION="v8-0-7.37"

alias lqout='cd '$PLOT_PATH

mkdir -p $FILE_PATH/$CATANVERSION
