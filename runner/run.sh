#/bin/sh

cd ./$1
g++ -std=c++20 -O2 -Wall $1.cpp -o main
./main < $2.in > out.txt
cat out.txt
diff -Z out.txt $2.ans
