#!/bin/bash

prog = $1
tests_num = $2
tests_len = $3

for ((i=1; i<=tests_num; i++)); do
 tst_str = "test"
 dir_name = `echo $tst_str$i`
 mkdir "$dir_name"
 ./test.py $tests_len "$dir_name/test"
 "./$dir_name/test.in" > $prog > "./$dir_name/test.res"

 if diff "./$dir_name/test.out" "./$dir_name/test.res" >/dev/null ; then
  rm -rf "$dir_name"
 fi

done