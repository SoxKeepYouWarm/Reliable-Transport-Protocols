#!/usr/bin/bash

sh basic_abt_tests.sh &

sh basic_gbn_tests.sh &

sh basic_sr_tests.sh &

wait

exit 0
