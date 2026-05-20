#/bin/sh

g++ -std=c++17 -O2 -Wall $1.cpp -o main
./main < in-$1$2.txt > out.txt
cat out.txt
diff out.txt std-$1$2.txt
