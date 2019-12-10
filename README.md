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
 





