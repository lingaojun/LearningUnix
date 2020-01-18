#/bin/sh
echo "hello world"
gcc main.c -o main
gcc test.c -o test
echo "GCC SUCCESS ALL"
##开一个终端后台运行main
##./main &
##10s内另开一个终端运行test 会显示锁被占用
##./test
