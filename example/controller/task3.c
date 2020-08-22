/*************************************************************************
 *
 *    Copyright (c) 2020 by w0x0021 All rights reserved.
 *    
 *    Filename: task3.c
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Blog: httpps://www.wangsansan.com
 *    Date: Fri 14 Aug 2020 05:08:43 PM CST
 *    
 *    Description：
 *    
 *************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "common.h"

void task3_main(int argc, char **argv)
{
    while(1)
    {
        w21_delayMs(1500);
        printf("[%d] - I am task3\n", getpid());
    }
}