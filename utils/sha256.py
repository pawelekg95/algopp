#!/bin/python3

import hashlib
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Python hash calculator')
    parser.add_argument('-f', '--file', dest='file')
    args = parser.parse_args()
    print(hashlib.md5(open(args.file, 'rb').read()).hexdigest())
