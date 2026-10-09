#!/bin/sh

code=$1
problem=`echo $code | cut -c1`
test=$2

g++ -std=c++20 -O2 -Wall $code.cpp -o main
./main < $problem/$test.in > $problem/out.txt
cat $problem/out.txt
diff -Z $problem/out.txt $problem/$test.ans
