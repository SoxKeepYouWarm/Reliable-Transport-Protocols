#!/usr/bin/bash

rm -R ./experiment_two_abt
mkdir ./experiment_two_abt

CONSTANTS="-m 1000 -t 50 -c 0.2 -w 1"
ERROR_LOG="./experiment_two_abt/error_log.txt"


for loss in 0.2 0.5 0.8
do

echo "starting experiment two ABT: loss ${loss}"
./run_experiments -p ../davidtow/abt ${CONSTANTS} -l ${loss} -o ./experiment_two_abt/abt_l${loss}.csv 2>> ${ERROR_LOG} &

done

wait

echo "finished ABT"

exit 0
