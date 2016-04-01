#!/usr/bin/bash

rm -R ./experiment_two_sr
mkdir ./experiment_two_sr

CONSTANTS="-m 1000 -t 50 -c 0.2"
ERROR_LOG="./experiment_two_sr/error_log.txt"


for window in 10 50 100 200 500
do

for loss in 0.2 0.5 0.8
do

echo "starting experiment two SR: loss ${loss} window: ${window}"
./run_experiments -p ../davidtow/sr ${CONSTANTS} -l ${loss} -w ${window} -o ./experiment_two_sr/sr_l${loss}_w${window}.csv 2>> ${ERROR_LOG} &

done

done

wait

echo "finished SR"

exit 0
