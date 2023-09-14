#!/bin/sh

gcc -Wall -o prog swiph.c

if [ -f 'prog' ]; then
    ./prog $1
fi
exit
