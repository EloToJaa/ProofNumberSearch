#!/usr/bin/env python3

import os
import sys

def run_test(n, output=False):
    print(f'STARTED TEST {n}')
    os.system(f'./pn < ./tests/{n}.in > ./out/{n}.out')
    if output:
        with open(f'./out/{n}.out') as f:
            print(f.read())

def run_tests(test_nums):
    first, last = test_nums
    for i in range(first, last+1):
        run_test(i)

def compile_files():
    os.system('g++ *.cpp -o pn -std=c++17 -Wall -Wextra -Wunused -Wconversion -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG')
    # os.system('g++ *.cpp -o pn -std=c++17 -Wall -Wextra -Wunused -Wconversion -g')

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('Missing an argument')
        sys.exit(1)

    compile_files()

    arg = sys.argv[1]

    if len(sys.argv) == 3:
        run_tests((int(arg), int(sys.argv[2])))

        sys.exit(0)

    test_num = int(arg)
    
    run_test(test_num)
    
    sys.exit(0)


