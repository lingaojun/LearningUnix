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

