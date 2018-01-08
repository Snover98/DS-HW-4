#!/bin/bash

prog = $1
tests_num = $2
tests_len = $3

for ((i=1; i<=tests_num; i++)); do
 mkdir "test$i"
 ./test.py $tests_len "test${i}/test"
 "./test$i/test.in" > eval "./$prog" > "./test$i/test.res"

 if diff "./test$i/test.out" "./test$i/test.res" >/dev/null ; then
  rm -rf "./test$i"
 fi

done