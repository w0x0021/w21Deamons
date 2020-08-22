/*************************************************************************
 *
 *    Copyright (c) 2020 by w0x0021 All rights reserved.
 *    
 *    Filename: common.h
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Blog: httpps://www.wangsansan.com
 *    Date: Fri 14 Aug 2020 05:12:09 PM CST
 *    
 *    Description：
 *    
 *************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__
#pragma onece

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

static inline void w21_delayMs(unsigned int timeout)
{
	struct timeval timer;
	timer.tv_sec    = 0;
	timer.tv_usec   = timeout*1000;
	select(0, NULL, NULL, NULL, &timer);
}

#endif
