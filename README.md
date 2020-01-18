# LearningUnix

## 2019.12.1
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

## 2020.1.7  
2020快乐！！  
增加pthread_create相关知识  
int pthread_create(pthread_t *tidp, const pthread_attr_t *attr, (void*)(*start_rtn)(void*), void *arg)  
第一个参数表示pid特征值，第二个参数表示线程熟悉，第三个参数表示线程函数的头地址，第四个参数表示线程函数的参数。  
get_pid()和pthread_self()区别 get_pid是获取进程id，在同一个进程中的不同线程他们的同一时刻的进程id相同，但是在不同时刻运行程序时的进程id不同。pthread_self是获取线程id，不同线程的id不同  

增加pthread_exit、pthread_join相关知识  
pthread_exit类似于return,只不过只用于线程函数中使用。  
pthread_join会阻塞当前线程直至指定的线程调用pthread_exit或从函数中取消或者返回，另外可以得到指定线程返回值。  

增加pthread_cleanup_push、pthread_cleanup_pop相关知识  
pthread_cleanup_push作用是添加(机制类似于栈添加)线程清理函数可用于线程退出时调用。**且必须是通过pthread_exit（）退出**，若通过return退出时是不会调用的。  
pthread_cleanup_pop的作用通过参数来觉得是否调用线程清理函数，**若入参为0时则会不执行线程清理函数，但不论是否为0，都会删除上一次添加的线程清理函数。**  

## 1.8  
增加pthread_mutex相关知识
pthread_mutex_init(),第一个入参是mutex的地址，第二个入参是mutex初始化属性，可用NULL表示默认。实际上在mutex声明时可定义为**pthread_mutex mutex = PTHREAD_MUTEX_INITIALIZER**也可代表初始化。  
pthread_mutex_lock()，获取mutex并上锁，当该mutex上锁时，其他线程调用pthread_mutex_lock时会被阻塞。**单个线程两次上锁会产生死锁！**  
pthread_mutex_trylock（），如果线程不希望被阻塞，它可以使用该函数对mutex进行加锁。**如果mutex此时为未锁住状态，则当前线程会锁住mutex，不会出现阻塞并返回0，否则该函数会失败，返回EBUSY(16?)。** **单个线程两次trylock不会产生死锁，但是会返回EBUSY (16)**  
pthread_mutex_unlock（）,对mutex解锁。  
pthread_mutex_timedlock（）,通过设定阻塞时间来避免永久阻塞，当超过该时间后会继续向后执行，不推荐使用，可能会发生死锁现象而且时间控制不稳定。  

## 1.11  
增加pthread_cond_wait和pthread_cond_signal相关知识  
pthrad_cond_wait() **当线程运行到这条语句时会自动对mutex解锁，并阻塞该线程**，直到收到其他线程的pthread_cond_signal()信号或pthread_cond_broadcast()才被唤醒,当**pthread_cond_wait（）返回时，mutex会被再次锁住**  

## 1.13  
增加pthread_barrier_wait和thread_barrier_init/thread_barrier_destroy相关知识  
首先理解需求：在某些场景下，需要多个线程同时运行，而不是需要在create时运行，此时每个线程都像是运动员，需要有发令枪响来告诉他们开始比赛。  
线程中的发令枪就是barrier(栏杆)。  
pthread_barrier_init()，第一个参数是pthread_barrier_t 为特性的变量，第二个是barrier变量的属性(NULL表示默认属性), 第三个参数是线程数量，即当内部计数器达到目标线程数量时，即会立即告诉线程开始同一运行。  
pthread_barrier_wait(),唯一参数是特性变量的地址。 **当线程内运行到这句函数时表明该线程已被阻塞,等待同一运行，且计数加1。**  
pthread_barrier_destroy(),反初始化，用于所有线程结束后。  
线程数量的取值：**所有线程+1**。理由：大部分情况下需要在主函数的同一规划下一起运行，又因为init中的计数是又运行的wait次数决定，**所以若目标计数 = 所有线程数量 +主线程数量(1)时，然后在主线程中再次调用wait函数，则可以起到一起运行所有线程的目标。**  
**PS:若wait个数与init设定的目标计数不同时，不管是大于还是小于其计数，所有线程都会阻塞住。**  

## 1.14  
凌晨 {
增加线程属性设置相关接口知识  
pthread_attr_t 线程属性变量类型  
pthread_attr_init()初始化线程属性变量，把属性设置为默认值  
pthread_attr_setdetachstate() 第一个参数是线程属性变量地址，第二个是线程某个宏，例如:PTHREAD_CREATE_DETACHED   
pthread_attr_destroy() 反初始化线程属性  
线程分离与线程可结合的区别： 线程可结合(pthread_join)表示一个可结合的线程是**可以被其他进程回收资源或者杀死的**，在其他线程被回收之前，他的存储器资源（如栈）是不会被回收的。  
线程分离(pthread_detach)是指当前线程不受其他线程控制,当自身线程结束时，**会自己释放所占用的资源**。  
}  
  
增加线程取消相关知识  
pthread_cancel()，唯一入参表示线程特征变量(pthread_t类型)，表示发出取消目标线程的指令，**当目标线程接受到被取消的命令后再次调用系统接口时，才会被取消**，取消后的线程退出值为-1。  
pthread_testcancel(), 无入参。若被取消线程在收到线程取消的指令时，某个取消请求被挂起状态，而且取消线程指令并没有置为无效，则线程会被取消。  

## 1.15  
增加pthread_key与pthread_once相关知识  
pthread_key_t是线程私有变量，它可以使多个线程用一个全局变量，但各自持有不同的值(通过pthread_set_specific调用)
pthread_once_t是线程仅执行一次的变量类型。  
pthread_key_create()第一个入参用于创建键，第二个入参表示在用于**这个键的线程退出后调用的析构函数。**  
pthread_key_delete()用于取消键与线程特定数据之间的连接关系，**并不会激活与键关联的析构函数**  
pthread_set_specific()调用该函数可以使键与线程特定变量进行连接。  
pthread_getspecific()，唯一入参是键，返回值为键对应的线程特定变量(一般多为无符号指针)。    
pthread_once()有两个入参，第一个为pthread_once_t变量的地址，表示线程执行一次的特有变量类型。第二个是表示在多线程环境下，只执行一次的函数对应的地址，到底是哪个线程执行，有内核调度决定。  

## 1.16  
增加信号在线程中的使用方式相关知识  
首先明确，信号在进程中的运行方式与在线程中的运行方式有很大不同。  
**在进程中，信号触发属于异步触发**，系统也不知何时会被触发信号。  
**在线程中，系统机制将信号触发流程转变为同步触发**，即安排一个线程专门用于处理信号触发，且等待信号触发的函数会被一直**阻塞**住直到目标信号的触发。
sig_wait（），第一个入参表示线程等待的信号集，即只有在该信号集中的信号被触发时，才会向下执行不被阻塞，第二个入参表示发送信号具体的宏，例如SIGINT，SIGQUIT等等。  
pthread_sigmask(),与sigprocmask功能相同，入参基本相同，请参考sigprocmask，只不过这个接口中用到的屏蔽信号集的信号是用于**线程**中使用。  

## 1.17  
增加fcntl中记录锁的相关知识  
**测试例程前须知：该例程无法达到预期效果，因为一般的UNIX不使用记录锁！！！**  
fcntl()是文件打开时可以修改文件性质的系统函数，作用很多，本次按记录锁的方式进行学习。  第一个入参是文件描述符，第二个按具体需求而定，表示文件性质，第三个在不同功能基础上是不同的入参类型，记录锁中是flock指针类型。  
flock是记录锁的相关结构体，成员有很多，具体可以控制锁在文件中的起始位置(成员有SEEK_SET等同等文件操作)，偏移量(等同于文件操作中的offset)，锁的长度(len)，以及锁的类型(读锁，写锁，解锁)。  

## 1.18  
增加select相关知识 (fd/select/main.c)
fd_set 文件描述符集变量类型，据说是个long数组。
select介绍，用于监控**打开的**文件描述符的变化情况，读写或异常。  
select(),第一个入参是最大文件描述符的值+1，表示需要检查的文件描述符集的范围，函数执行时会从0开始一直查询到目标文件描述符集的长度。第二个入参是读文件描述符集的变量地址。第三个入参是写文件描述符集的变量地址。第四个入参是异常情况文件描述符集的变量地址。第五个入参是时间变量类型，表示愿意等待的时间长度，不同的值表示的意义不同，这里不做展开讨论，若需要请百科。  
FD_ZERO() 唯一入参是文件描述符集的地址，表示对文件描述符的初始化，在声明了一个描述符集之后，必须用FD_ZERO讲此描述符集设为0。  
FD_SET() 第一个入参表示需要设定的文件描述符，第二个入参表示需要建立联系的的文件描述符集。用于将文件描述符加入文件描述符集中。  
FD_SET() 参数列表与FD_SET相同，未在demo中使用。用于将目标文件描述符从目标文件描述符集中清除。  
FD_ISSET()，参数列表与FD_SET相同，用于检测文件描述符是否在目标文件描述符集中。  
已知**文件描述符0，1，2为系统自带**的**已打开**的文件描述符，所以用select()测试返回值**大于0**，而在此外的文件描述符未初始化，所以无法测试。 select返回值将小于等于0，表示异常。





