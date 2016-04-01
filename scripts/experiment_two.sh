#!/usr/bin/bash

echo "running experiment two!"

echo "starting ABT"
sh experiment_two_abt.sh &

echo "starting GBN"
sh experiment_two_gbn.sh &

echo "starting SR"
sh experiment_two_sr.sh &

wait

echo "DONE!"

exit 0
