#!/usr/bin/bash

rm -R ./experiment_one_abt
mkdir ./experiment_one_abt

CONSTANTS="-m 1000 -t 50 -c 0.2"
ERROR_LOG="./experiment_one_abt/error_log.txt"

echo "starting experiment one ABT: loss 0.1"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l 0.1 > ./experiment_one_abt/abt_l0.1.txt 2>> ${ERROR_LOG} &
 
echo "starting experiment one ABT: loss 0.2"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l 0.2 > ./experiment_one_abt/abt_l0.2.txt 2>> ${ERROR_LOG} &

echo "starting experiment one ABT: loss 0.4"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l 0.4 > ./experiment_one_abt/abt_l0.4.txt 2>> ${ERROR_LOG} &

echo "starting experiment one ABT: loss 0.6"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l 0.6 > ./experiment_one_abt/abt_l0.6.txt 2>> ${ERROR_LOG} &

echo "starting experiment one ABT: loss 0.8"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l 0.8 > ./experiment_one_abt/abt_l0.8.txt 2>> ${ERROR_LOG} &

wait

exit 0
