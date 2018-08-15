#!/bin/bash
path=`pwd`
export LD_LIBRARY_PATH=$path/3rdpart/unix/ffmpeg:$LD_LIBRARY_PATH
cd $path
$path/3rdpart/unix/ffmpeg/ffmpeg -i $1 -r $2 $3
