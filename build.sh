#!/bin/bash

##############################################################
#    Copyright (c) 2020 by WangSansan All rights reserved.
#    
#    Filename: build.sh
#    Author：WangSansan
#    Email: w0x0021@gmail.com
#    Site: https://www.wangsansan.com
#    Date: Sat 23 May 2020 06:14:22 PM CST
#    
#    Description：
##############################################################

dirCurrent=`pwd`
dirCompile=$dirCurrent/build

# Initialization directory
rm -rf $dirCompile
mkdir -p $dirCompile
cd $dirCompile

# Run cmake
cmake $dirCurrent

# Run make
cmd_re=$?
if [ $cmd_re == 0 ];then
    echo "Make \`Makefile\` complete."
    make
else
    echo "[Err:$cmd_re] \`cmake\` faild."
    exit 1
fi



