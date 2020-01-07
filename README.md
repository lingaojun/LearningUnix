# LearningUnix

## 12.1
增加fork()函数，可以新建一个相同的进程，子进程的进程号为0。  

## 12.7  
增加文件打开读写以及seek功能。 
增加错误码stderr相关知识。   

## 12.8  
增加FILE 文件流的读写以及rewind修改流输入输出方向的知识。  
**总结：FILE文件流与文件不同的地方在于，流存在方向，在指定输入输出方向后，若需要修改方向，需要调用rewind等函数。**  

## 12.9  
增加ungetc和feof相关知识  
**ungetc： 读取当前流出的字符，之后再调用该函数可以修改该字符再流入**  
**feof： 检测是否到流的尾部，但是当到达流尾部时会返回非0表示退出**  
**文件结尾 ！= 最后一个字符**  
补充： getc检测到文件结尾会返回-1   

增加mkstemp相关知识
mkstemp是创建临时文件夹所用  
mkstemp入参不能是char* 因为需要对其进行修改，而char* 仅仅是将指针存入栈中，其内容是存入只读区，不能修改  
所以应使用char[]  

增加getenv以及putenv,setenv等知识
getenv是获取目标环境变量的值   
putenv和setenv的区别在于 putenv是修改之后仅在程序中生效，一旦程序结束，环境依旧原样。而setenv则会按照第三个形参是否为0来决定是否变成修改值。 
函数签名：     
int getenv(char* ch);
int setenv(const char *name, const char *value, int rewrite); //若rewrite为0则去判断原变量是否有值，若有则不会重写；若为非0，则直接重写  

## 12.10  
增加setjmp，longjmp相关知识  
setjmp是栈跳跃，类似于goto，但是优点在于goto只用于当前文件的跳转，而setjmp可用于多个文件间的跳转。  
setjmp入参为jmp_buf变量，其类似于数组，返回值为跳转码flag。
而longjmp的函数签名为 longjmp(jmp_buf buf, int flag)，可以修改其jmp_buf对应的跳转码flag，执行完这条语句后，会重新从setjmp所在的函数继续向下执行,但是其setjmp的返回值会变成longjmp设定的跳转吗，因此可以通过其多次检查setjmp的返回值即跳转码进行判定。  
关于**已修改的变量**是否也会回滚的问题，书中给出的结果是**不确定**，细节有点复杂，取决于**是否使用程序优化的方式 (-o)** ，本例不进行讨论。  

补充fork相关知识  
fork子进程生成后从**fork该条语句继续向下执行，且与父进程一起并行，不清楚谁执行较快**  

增加vfork相关知识  
vfork产生子进程后会等待子进程调用exit(0)或exec()完成后才调用父进程，且子进程是在父进程的地址空间中运行，所以子进程对变量的修改，在父进程会保存其修改。  

## 12.11  
增加fork 两次以避免产生僵死进程的相关知识  
已知当子进程结束时，若父进程还存在且不调用wait()或相关函数时，子进程的相关资源没有被回收，会占据内存，产生僵死进程。
两次fork的作用是，产生子进程和孙子进程(姑且这么称呼)，当子进程创建之后立即返回，那么对于孙子进程来说，其父进程(相当于子进程)消失了，那么他作为孤儿进程会自动交给init进程进行资源释放，而且孙子进程对于父进程来说没有关系，那么父进程只需要调用一次wait即可来处理子进程就行。  
![Image text](https://github.com/lingaojun/LearningUnix/blob/master/fork/forktwice/1.png)  
![Image text](https://github.com/lingaojun/LearningUnix/blob/master/fork/forktwice/2.png)  

增加exec函数族相关知识  
exec函数族共有七种函数，概括的说exec可以通过路径作为入参运行其他程序，也可以为新启动程序提供argv[]和env相关变量。
本例使用经典的execve的函数，与fork混合使用。   

## 12.24 
平安夜快乐！！  
增加alarm知识以及栈跳转导致信号处理函数终止相关知识  
已知alarm是用于设定固定时间后触发**SIGALRM**信号，且alarm在进程中只能存在一个，即当alarm被调用且时间未到时，二次调用alarm时的返回值将是第一次调用的余留值，可从代码中的fun函数可知。  
另外，当在信号处理函数中触发了了栈跳跃(longjmp)时，会导致另一个信号处理函数提前终止。  

## 12.25  
圣诞节快乐！！  
增加sigsetjmp相关知识  
sigsetjmp与setjmp的区别在于**在信号处理函数中，若使用setjmp对应的longjmp时，则会直接返回到setjmp所在的位置**,会导致原来被阻塞的信号不能被释放，二次触发该信号时会被再次阻塞。sigsetjmp则可以避免这个问题，sigsetjmp函数有两个接口，第二个接口若为非0的话，会保存信号屏蔽字，那么在调用siglongjmp时，若已经保存了信号屏蔽字的话，会从其中恢复保存的信号屏蔽字。  

增加sigemptyset sigaddset sigprocmask sigsuspend相关知识  
**sigemptyset** 类似于信号集初始化    
**sigaddset** 将目标信号加入目标信号集  
**sigprocmask** 根据不同的参数对两个信号集进行处理  
**sigsuspend** 挂起进程目标信号出现，该信号必须在目标信号集中不存在，**比如说sigsuspend(&sigmask)中的sigmask信号集若存在SIGQUIT信号时，当执行到sigsuspend时阻塞住，若触发了SIGQUIT信号则不会有反应，但是其他信号都会有反应**，这是这个函数的特性。代码中信号集变量为newmask,该信号集无任何信号，所以任何信号都会被触发信号处理函数。  

## 1.7  
2020快乐！！  
增加pthread_create相关知识  
int pthread_create(pthread_t *tidp, const pthread_attr_t *attr, (void*)(*start_rtn)(void*), void *arg)  
第一个参数表示pid特征值，第二个参数表示线程熟悉，第三个参数表示线程函数的头地址，第四个参数表示线程函数的参数。  
get_pid()和pthread_self()区别 get_pid是获取进程id，在同一个进程中的不同线程他们的同一时刻的进程id相同，但是在不同时刻运行程序时的进程id不同。pthread_self是获取线程id，不同线程的id不同  

增加pthread_exit、pthread_join相关知识  
pthread_exit类似于return,只不过只用于线程函数中使用。  
pthread_join会阻塞当前线程直至指定的线程调用pthread_exit或从函数中取消或者返回，另外可以得到指定线程返回值。  






