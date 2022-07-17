#! /bin/bash

./array_generator/make_arrays.sh

echo "algorithm,file,size,add_c,add_t,look_c,look_t,del_c,del_t"

for algo in avltree binary binarytree linear rnbtree treap
do
    for size in 10 100 1000 10000 100000 1000000
    do
        for mode in {0..3}
        do
            for seed in {0..90..10}
            do
                ./${algo} arrays/arr_${size}_${mode}_${seed}.bin ${size}
            done
        done
    done
done
