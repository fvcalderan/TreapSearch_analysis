# TreapSearch_analysis
An analysis of the Treap Search algorithm

## Article link

This repository contains the source code for
[this article](https://fvcalderan.github.io/myworks/articles/treap_search.pdf).

## Abstract

Treap is a binary search tree that bets on the uniformity of a random
distribution of items at the time of insertion. The bet is that by entering
items in this way, a relatively balanced tree can be built, without the extra
cost of algorithmically calculating and balancing the tree. It is also worth
mentioning that treap has this name because it is a fusion of tree and heap,
since the conformation of the items in the tree follows the rules of both
binary search trees and binary heap trees. In this article, we will analyze the
complexity and CPU time of the operations of inserting, searching and removing
items from the treap tree, in addition to comparing it with other search
methods, specifically linear, binary, binary tree, AVL tree search and
red-black tree.

## Project Solution
```
.
├── LICENSE
├── README.md
└── src
    ├── array_generator
    │   ├── gen_array.c
    │   ├── load_array.c
    │   ├── make_arrays.sh
    │   └── makefile
    ├── avltree.c
    ├── binary.c
    ├── binarytree.c
    ├── linear.c
    ├── makefile
    ├── rnbtree.c
    ├── run_all.sh
    └── treap.c
```

## How the project is structured

Inside the **src** folder lies the code to run the comparison between Linear,
Binary, Binary Tree, AVL Tree, Red-Black Tree and Treap search algorithms.
Each algorithm is implemented in a separate C file, with a respective `main`
function in the same file.

The *array_generator* folder contains the source code of a program that can
generate different types of arrays (*gen_arrays*) and read them afterwards
(*load_array*). The array generation program is used to create the arrays to
compare the search algorithms.

## Compile everything

Run `make` inside **src** and **src/array_generator**.

## Run the program

### Using scripts

Before proceeding, make sure you have Bash installed and that `/bin/bash` is
not a symlink to another shell, like `Zsh`. Although other shells may be able
to run the scripts, they were not tested.

Make sure all the required bash scripts files are executable, by running
(inside the **src** folder):

```bash
chmod +x run_all.sh
chmod +x array_generator/make_arrays.sh
```

After that, run:
```bash
nohup ./run_all.sh > output.csv &
```
This will create the arrays, run the algorithms and generate a `CSV` file with
all the data to make the comparisons present in the paper, in the background
and with the `stdout` detached from the current session (through `nohup`) and
redirected to `output.csv`. To generate the charts you may use your favorite
software. I, personally, used Python + Pandas + Matplotlib.

If you want to generate and/or run a different set of arrays, you can modify
the for loops inside the Bash scripts or execute the C programs manually.

### Manually running the programs

To run the programs yourself, specific sets of arguments are needed for each
one of them:
```
./gen file_name size mode seed
./load file_name size
./avltree file_name size
./binary file_name size
./binarytree file_name size
./linear file_name size
./rnbtree file_name size
./treap file_name size
```
The arguments should be intuitive to understand by their names, but you can
always check the source code to verify what they mean. For instance: the `mode`
argument of the `gen` program is a number that defines the rules to generate
the elements inside the generated array:
- 0 - ordered unique
- 1 - inversely ordered unique
- 2 - almost ordered unique
- 3 - random unique
- 4 - ordered
- 5 - inversely ordered
- 6 - almost ordered
- 7 - random

So to run the Treao Search algorithm to perform insertion, search and deletion
of elements in an array which file is named arrays/my_array.bin of size
1000000, you may run something like:
```bash
./treap arrays/my_array.bin 1000000
```
Finally, you can completely ignore the array_generator and generate the binary
files yourself using your programming language or hex editor of choice. The
only restriction is that the elements must be C signed integers.

## License
```
BSD 3-Clause License

Copyright (c) 2022, fvcalderan
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
