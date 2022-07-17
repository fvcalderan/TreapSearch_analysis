#! /bin/bash

mkdir -p arrays

for size in 10 100 1000 10000 100000 1000000
do
    for mode in {0..3}
    do
        for seed in {0..90..10}
        do
            array_generator/gen arrays/arr_${size}_${mode}_${seed}.bin\
                $size $mode $seed
        done
    done
done
