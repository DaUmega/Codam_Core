#!/bin/bash

def="$2"
range="100"
if [ "$def" == "" ]
then
def="$range"
fi
for i in $(seq $1);
do
ARG="$(ruby -e "puts (1..$def).to_a.shuffle.join(' ')")"
# ARG="$(ruby -e "puts (1..$def).to_a.reverse.join(' ')")"
 ./push_swap $ARG | ./checker_Mac $ARG && ./push_swap $ARG  | wc -l
# ./push_swap $ARG | ./checker_os $ARG && ./push_swap $ARG | wc -l
#./push_swap $ARG | ./checker_linux $ARG && ./push_swap $ARG | wc -l
done

# for i in $(seq $1);
# do
# ARG="$(ruby -e "puts (0..$def).to_a.shuffle.join(' ')")"
# ./push_swap $ARG | ./checker_linux $ARG && ./push_swap $ARG | wc -l
# done


# ./test.sh 100 | grep 7..

# ARG="$(ruby -e "puts (0..99).to_a.shuffle.join(' ')")"
#&& time ./push_swap $ARG