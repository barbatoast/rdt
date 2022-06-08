#!/bin/bash

RUNNER=./runner

for r in $(ls $RUNNER); do
    $RUNNER/$r
done
