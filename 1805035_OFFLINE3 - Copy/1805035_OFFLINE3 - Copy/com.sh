yacc -y -d -v 1805035.y
g++  -w -c -o y.o y.tab.c 
flex 1805035.l
g++  -w -c -o l.o lex.yy.c 
g++  *.cpp  -o a.out y.o l.o -lfl -g
# ./a.out  input.txt
./a.out  testcases/loop.c