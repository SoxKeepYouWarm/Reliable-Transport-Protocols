#!/ugbn/bin/bash

rm -R ./experiment_one_gbn
mkdir ./experiment_one_gbn

CONSTANTS="-m 1000 -t 50 -c 0.2"
ERROR_LOG="./experiment_one_gbn/error_log.txt"

echo "starting experiment one GBN: loss 0.1 window: 10"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.1 -w 10 > ./experiment_one_gbn/gbn_l0.1_w10.txt 2>> ${ERROR_LOG} &
 
echo "starting experiment one GBN: loss 0.2 window: 10"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.2 -w 10 > ./experiment_one_gbn/gbn_l0.2_w10.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.4 window: 10"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.4 -w 10 > ./experiment_one_gbn/gbn_l0.4_w10.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.6 window: 10"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.6 -w 10 > ./experiment_one_gbn/gbn_l0.6_w10.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.8 window: 10"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.8 -w 10 > ./experiment_one_gbn/gbn_l0.8_w10.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.1 window: 50"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.1 -w 50 > ./experiment_one_gbn/gbn_l0.1_w50.txt 2>> ${ERROR_LOG} &
 
echo "starting experiment one GBN: loss 0.2 window: 50"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.2 -w 50 > ./experiment_one_gbn/gbn_l0.2_w50.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.4 window: 50"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.4 -w 50 > ./experiment_one_gbn/gbn_l0.4_w50.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.6 window: 50"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.6 -w 50 > ./experiment_one_gbn/gbn_l0.6_w50.txt 2>> ${ERROR_LOG} &

echo "starting experiment one GBN: loss 0.8 window: 50"
./run_experiments -p ../davidtow/gbn ${CONSTANTS} -l 0.8 -w 50 > ./experiment_one_gbn/gbn_l0.8_w50.txt 2>> ${ERROR_LOG} &

wait

exit 0
