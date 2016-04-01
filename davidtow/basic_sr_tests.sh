#!/usr/bin/bash

rm -R ./basic_tests_sr
mkdir ./basic_tests_sr

echo "running sr -l .1 -c 0"
./sr -s 1 -m 20 -t 50 -w 50 -l .1 -c 0 -v 3 > ./basic_tests_sr/sr_l.1_c0.txt 2> ./basic_tests_sr/error_log.txt &

echo "running sr -l .4 -c 0"
./sr -s 1 -m 20 -t 50 -w 50 -l .4 -c 0 -v 3 > ./basic_tests_sr/sr_l.4_c0.txt 2> ./basic_tests_sr/error_log.txt &

echo "running sr -l .8 -c 0"
./sr -s 1 -m 20 -t 50 -w 50 -l .8 -c 0 -v 3 > ./basic_tests_sr/sr_l.8_c0.txt 2> ./basic_tests_sr/error_log.txt &

echo "running sr -l 0 -c .1"
./sr -s 1 -m 20 -t 50 -w 50 -l 0 -c .1 -v 3 > ./basic_tests_sr/sr_l0_c.1.txt 2> ./basic_tests_sr/error_log.txt &

echo "running sr -l 0 -c .4"
./sr -s 1 -m 20 -t 50 -w 50 -l 0 -c .4 -v 3 > ./basic_tests_sr/sr_l0_c.4.txt 2> ./basic_tests_sr/error_log.txt &

echo "running sr -l 0 -c .8"
./sr -s 1 -m 20 -t 50 -w 50 -l 0 -c .8 -v 3 > ./basic_tests_sr/sr_l0_c.8.txt 2> ./basic_tests_sr/error_log.txt &

echo "\nfinished issuing commands for SR basic tests"
date
wait

echo "SR basic tests done!"
date
exit 0
