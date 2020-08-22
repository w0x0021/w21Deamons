/*************************************************************************
 *
 *    Copyright (c) 2020 by WangSansan All rights reserved.
 *    
 *    Filename: main.cpp
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Site: https://www.wangsansan.com
 *    Date: Sat 22 Aug 2020 11:42:49 AM CST
 *    
 *    Description：
 *    
 *************************************************************************/

#include <iostream>
using namespace std;

#include <signal.h>
#include "w21Deamons.h"

#include "config.h"

void signal_handel(int sig)
{

}

void signal_reg()
{
	// signal(SIGINT, signal_handel); 		// Ctrl + C
	// signal(SIGTERM, signal_handel); 		// kill
}

int init()
{
	/************************************ 
	 *       信号注册                    *
	 ************************************/
	signal_reg();

	/************************************ 
	 *       共享内存初始化              *
	 ************************************/
	

	/************************************ 
	 *       其它初始化工作              *
	 ************************************/
	

	return 0;
}

int main(int argc, char **argv)
{
	printf(__PRINT_WELCOME__);

	if(init() < 0){
		printf("Initialization failed. \n");
		return -1;
	}

	w21Dms_Main(argc, argv);
	return 0;
}
