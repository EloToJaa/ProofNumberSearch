#!/usr/bin/env python3

import os
from posixpath import split
import sys

def compare_test(n, output=True):
    a = open(f'./tests/{n}.out').read()
    b = open(f'./out/{n}.out').read()
    ins = open(f'./tests/{n}.in').read().split('\n\n')[:-1]
    if a != b:
        a = a.split('\n')
        b = b.split('\n')
        print(f'Test {n} failed\n')
        for la, lb, test in zip(a, b, ins):
            if la != lb:
                print(f'Expected: {la}')
                print(f'Got: {lb}')
                print(test)
                print()

                with open('tests/10.in', 'w') as f:
                    f.write(test)


def compare_tests(test_nums):
    first, last = test_nums
    for i in range(first, last+1):
        compare_test(i, output=True)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('Missing an argument')
        sys.exit(1)

    arg = sys.argv[1]

    if len(sys.argv) == 3:
        compare_tests((int(arg), int(sys.argv[2])))

        sys.exit(0)

    test_num = int(arg)
    
    compare_test(test_num)
    
    sys.exit(0)


