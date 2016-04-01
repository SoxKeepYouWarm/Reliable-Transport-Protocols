#!/usr/bin/bash

rm -R ./basic_tests_abt
mkdir ./basic_tests_abt

echo "running abt -l .1 -c 0"
./abt -s 1 -m 20 -t 1000 -w 50 -l .1 -c 0 -v 3 > ./basic_tests_abt/abt_l.1_c0.txt 2> ./basic_tests_abt/error_log.txt &

echo "running abt -l .4 -c 0"
./abt -s 1 -m 20 -t 1000 -w 50 -l .4 -c 0 -v 3 > ./basic_tests_abt/abt_l.4_c0.txt 2> ./basic_tests_abt/error_log.txt &

echo "running abt -l .8 -c 0"
./abt -s 1 -m 20 -t 1000 -w 50 -l .8 -c 0 -v 3 > ./basic_tests_abt/abt_l.8_c0.txt 2> ./basic_tests_abt/error_log.txt &

echo "running abt -l 0 -c .1"
./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .1 -v 3 > ./basic_tests_abt/abt_l0_c.1.txt 2> ./basic_tests_abt/error_log.txt &

echo "running abt -l 0 -c .4"
./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .4 -v 3 > ./basic_tests_abt/abt_l0_c.4.txt 2> ./basic_tests_abt/error_log.txt &

echo "running abt -l 0 -c .8"
./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .8 -v 3 > ./basic_tests_abt/abt_l0_c.8.txt 2> ./basic_tests_abt/error_log.txt &

echo "\nfinished issuing commands for ABT basic tests"
date
wait

echo "ABT basic tests done!"
date
exit 0
