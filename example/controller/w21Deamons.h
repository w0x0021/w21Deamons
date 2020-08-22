/*************************************************************************
 *
 *    Copyright (c) 2020 by WangSansan All rights reserved.
 *    
 *    Filename: w21Deamons.h
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Site: https://www.wangsansan.com
 *    Date: Tue 11 Aug 2020 02:11:23 PM PDT
 *    
 *    Description：
 *    
 *************************************************************************/

#ifndef __TASK_MAIN_H__
#define __TASK_MAIN_H__
#pragma onece

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
	unsigned char 	act; 		// Whether the process survives. Active: 1; death: 0.
	pid_t 	        pid;        // PID of subprocess.
	int 	        status;     // The second parameter of `waitpid()`
}w21Dms_TaskStatus_t;

extern w21Dms_TaskStatus_t w21Dms_gTask[];
static inline void w21Dms_taskMaxFunc(int argc, char **argv){};


/*******************************************************************
 *       Please change the code for this area - Start              *
 *******************************************************************/
void task1_main(int argc, char **argv);
void task2_main(int argc, char **argv);
void task3_main(int argc, char **argv);
#define W21DMS_MACROS                                               \
	W21DMS_XMACROS(TASK_FUNC1 , w21Dms_gTask, task1_main)			\
	W21DMS_XMACROS(TASK_FUNC2 , w21Dms_gTask, task2_main)			\
	W21DMS_XMACROS(TASK_FUNC3 , w21Dms_gTask, task3_main)			\
                                                                    \
    W21DMS_XMACROS(TASK_MAX , w21Dms_gTask, w21Dms_taskMaxFunc)     /*** The line dose not be changed ***/
/*******************************************************************
 *       Please change the code for this area - End                *
 *******************************************************************/

int w21Dms_Main(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
