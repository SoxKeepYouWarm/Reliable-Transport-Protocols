#!/usr/bin/bash

echo "running experiment one!"

echo "starting ABT"
sh experiment_one_abt.sh &

echo "starting GBN"
sh experiment_one_gbn.sh &

echo "starting SR"
sh experiment_one_sr.sh &

wait

echo "DONE!"

exit 0
