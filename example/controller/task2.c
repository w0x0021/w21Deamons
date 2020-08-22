/*************************************************************************
 *
 *    Copyright (c) 2020 by w0x0021 All rights reserved.
 *    
 *    Filename: task2.c
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Blog: httpps://www.wangsansan.com
 *    Date: Fri 14 Aug 2020 05:08:33 PM CST
 *    
 *    Description：
 *    
 *************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "common.h"

void task2_main(int argc, char **argv)
{
    while(1)
    {
        w21_delayMs(1000);
        printf("[%d] - I am task2\n", getpid());
    }
}
