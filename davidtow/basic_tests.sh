#!/usr/bin/bash

mkdir ./basic_tests_abt

echo "running abt -l .1 -c 0"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l .1 -c 0 -v 3 > ./basic_tests_abt/abt_l.1_c0.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 1"

echo "running abt -l .4 -c 0"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l .4 -c 0 -v 3 > ./basic_tests_abt/abt_l.4_c0.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 2"

echo "running abt -l .8 -c 0"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l .8 -c 0 -v 3 > ./basic_tests_abt/abt_l.8_c0.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 3"

echo "running abt -l 0 -c .1"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .1 -v 3 > ./basic_tests_abt/abt_l0_c.1.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 4"

echo "running abt -l 0 -c .4"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .4 -v 3 > ./basic_tests_abt/abt_l0_c.4.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 5"

echo "running abt -l 0 -c .8"
nohup ./abt -s 1 -m 20 -t 1000 -w 50 -l 0 -c .8 -v 3 > ./basic_tests_abt/abt_l0_c.8.txt 2> ./basic_tests_abt/error_log.txt | echo "finished test 6"

echo "Done!\n"

exit 0
