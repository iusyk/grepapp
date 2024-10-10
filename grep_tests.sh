#!/bin/bash

grepResult="$(grep -r $2 -a --text -l $1 | wc -l)"
grepappResult="$(./grepapp -d $1 -t $2 -l | wc -l)"
echo $grepResult
echo $grepappResult
if [[ "$grepResult" == "$grepappResult" ]]; then
    echo "PASSED"
else
    echo "FAILED"
fi