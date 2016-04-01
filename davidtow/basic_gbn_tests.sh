#!/usr/bin/bash

rm -R ./basic_tests_gbn
mkdir ./basic_tests_gbn

echo "running gbn -l .1 -c 0"
./gbn -s 1 -m 20 -t 50 -w 50 -l .1 -c 0 -v 3 > ./basic_tests_gbn/gbn_l.1_c0.txt 2> ./basic_tests_gbn/error_log.txt &

echo "running gbn -l .4 -c 0"
./gbn -s 1 -m 20 -t 50 -w 50 -l .4 -c 0 -v 3 > ./basic_tests_gbn/gbn_l.4_c0.txt 2> ./basic_tests_gbn/error_log.txt &

echo "running gbn -l .8 -c 0"
./gbn -s 1 -m 20 -t 50 -w 50 -l .8 -c 0 -v 3 > ./basic_tests_gbn/gbn_l.8_c0.txt 2> ./basic_tests_gbn/error_log.txt &

echo "running gbn -l 0 -c .1"
./gbn -s 1 -m 20 -t 50 -w 50 -l 0 -c .1 -v 3 > ./basic_tests_gbn/gbn_l0_c.1.txt 2> ./basic_tests_gbn/error_log.txt &

echo "running gbn -l 0 -c .4"
./gbn -s 1 -m 20 -t 50 -w 50 -l 0 -c .4 -v 3 > ./basic_tests_gbn/gbn_l0_c.4.txt 2> ./basic_tests_gbn/error_log.txt &

echo "running gbn -l 0 -c .8"
./gbn -s 1 -m 20 -t 50 -w 50 -l 0 -c .8 -v 3 > ./basic_tests_gbn/gbn_l0_c.8.txt 2> ./basic_tests_gbn/error_log.txt &

echo "\nfinished issuing commands for GBN basic tests"
date
wait

echo "GBN basic tests done!"
date
exit 0
