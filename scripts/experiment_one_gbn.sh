#!/ugbn/bin/bash

rm -R ./experiment_one_gbn
mkdir ./experiment_one_gbn

CONSTANTS="-m 1000 -t 50 -c 0.2"
ERROR_LOG="./experiment_one_gbn/error_log.txt"


for window in 10 50
do

for loss in 0.1 0.2 0.4 0.6 0.8
do

echo "starting experiment one GBN: loss ${loss} window: ${window}"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l ${loss} -w ${window} -o ./experiment_one_gbn/gbn_l${loss}_w${window}.csv 2>> ${ERROR_LOG} &

done

done

wait

echo "finished GBN"

exit 0
