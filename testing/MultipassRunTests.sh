#!/bin/bash

max=1000
i=1

while [ "$i" -le $max ]; do
    sh RunTests.sh >> output.dat;
    echo "Completed pass #" $i
    i=$((i+1))
done
