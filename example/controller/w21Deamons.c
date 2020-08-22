/*************************************************************************
 *
 *    Copyright (c) 2020 by WangSansan All rights reserved.
 *    
 *    Filename: w21Deamons.c
 *    Author：WangSansan
 *    Email: w0x0021@gmail.com
 *    Site: https://www.wangsansan.com
 *    Date: Tue 11 Aug 2020 02:09:00 PM PDT
 *    
 *    Description：
 *    
 *************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "w21Deamons.h"


#define W21DMS_TASK_DELAY 50            /*** The time the daemons loop listens ***/
#define W21DMS_XMACROS(ENUM, STRUCT_ARR, FUNC)   ENUM,
    enum TASK_IDS{
        W21DMS_MACROS
    };
#undef W21DMS_XMACROS

w21Dms_TaskStatus_t w21Dms_gTask[TASK_MAX];
int w21Dms_gTaskActiveNum  = 0;


static inline void w21Dms_delayMs(unsigned int timeout)
{
	struct timeval timer;
	timer.tv_sec    = 0;
	timer.tv_usec   = timeout*1000;
	select(0, NULL, NULL, NULL, &timer);
}


/**
 * @Function : task_deamons()
 * @Description ： Daemons, preventing accidental crashes
 *
 * @Return : `fork()` number of successful subprocesses.
 */
int w21Dms_listen(int argc, const char **argv)
{
    int i;
	while(1)
	{
		w21Dms_delayMs(W21DMS_TASK_DELAY);
		for(i=0; i<TASK_MAX; i++)
		{
            if(waitpid(w21Dms_gTask[i].pid, &(w21Dms_gTask[i].status), WNOHANG) == 0){		// Check whether the child process crashes
				w21Dms_gTask[i].act = 1;
			}else{ 		                                                                    // Restart the crashed child process
				if(1 == w21Dms_gTask[i].act){
					w21Dms_gTaskActiveNum--;
					w21Dms_gTask[i].act = 0;
                    
					/*** Does the process exit normally ***/
					if(!WIFEXITED(w21Dms_gTask[i].status)){
						switch(i)
						{
                            #define W21DMS_XMACROS(ENUM, STRUCT_ARR, FUNC)                                         \
                                case ENUM: {                                                                        \
                                    STRUCT_ARR[ENUM].pid = 0;                                                       \
                                    STRUCT_ARR[ENUM].pid = fork();                                                  \
                                    if(STRUCT_ARR[ENUM].pid < 0){                   /*** `fork()` failed ***/       \
                                        return -1;                                                                  \
                                    }else if(STRUCT_ARR[ENUM].pid == 0){            /*** Child process ***/         \
                                        FUNC(argc, (char **)argv);                                                  \
                                    }else if(STRUCT_ARR[ENUM].pid > 0){             /*** Father process ***/        \
                                        w21Dms_gTaskActiveNum++;                                                    \
                                        STRUCT_ARR[ENUM].act = 1;                                                   \
                                    }                                                                               \
                                }break;

                                W21DMS_MACROS
                            #undef W21DMS_XMACROS
							default: break;
						}
					}
				}
			}
		}

		if(w21Dms_gTaskActiveNum < 1) {
            break;
        }
	}

	return w21Dms_gTaskActiveNum;
}

/**
 * @Function : task_init()
 * @Description ： Initialization of some global 
 *                 parameters before the task starts.
 *
 * @Return : Success : = 0
 *           Fail    : < 0
 */
int w21Dms_init()
{
    #define W21DMS_XMACROS(ENUM, STRUCT_ARR, FUNC)     \
        STRUCT_ARR[ENUM].act    = 0;                    \
        STRUCT_ARR[ENUM].pid    = 0;                    \
        STRUCT_ARR[ENUM].status = 0;

        W21DMS_MACROS
    #undef W21DMS_XMACROS

    return 0;
}

/**
 * @Function :      task_main()
 * @Description ：  Main task entry.
 *
 * @Return : Success : = 0
 *           Fail    : < 0
 */
int w21Dms_Main(int argc, char **argv)
{
    if(w21Dms_init() < 0){
        return -1;
    }

    for(int i=0; i<TASK_MAX; i++)
	{
		w21Dms_gTaskActiveNum++; 		            // Be sure to put it before `fork()`
		w21Dms_gTask[i].pid 	= fork();
		
		if(w21Dms_gTask[i].pid  < 0){ 		        // `fork()` Failed. This is father process.
			w21Dms_gTaskActiveNum--;
			return i;
		}else if(0 == w21Dms_gTask[i].pid){ 		// `fork()` Success. This is child process.
			switch(i)
			{
                #define W21DMS_XMACROS(ENUM, STRUCT_ARR, FUNC)     \
                    case ENUM : FUNC(argc, argv); return 0;
                    W21DMS_MACROS
                #undef W21DMS_XMACROS
				default: return -2;
			}
		}
	}

    if(w21Dms_listen(argc, (const char **)argv) < 0){
        return -3;
    }

    return w21Dms_gTaskActiveNum;
}
