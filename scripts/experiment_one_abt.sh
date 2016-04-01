#!/usr/bin/bash

rm -R ./experiment_one_abt
mkdir ./experiment_one_abt

CONSTANTS="-m 1000 -t 50 -c 0.2 -w 1"
ERROR_LOG="./experiment_one_abt/error_log.txt"


for loss in 0.1 0.2 0.4 0.6 0.8
do

echo "starting experiment one ABT: loss ${loss}"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l ${loss} -o ./experiment_one_abt/abt_l${loss}.csv 2>> ${ERROR_LOG} &

done

wait

echo "finished ABT"

exit 0
