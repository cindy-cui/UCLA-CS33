#!/bin/bash

if [[ "$#" != "1" ]]; then
  echo "Usage:"
  echo "$0 [nBodies]"
  exit 1
fi

for i in $(seq 1 $1); do
  x=$((1 + ${RANDOM} % 50000 - 25000))
  y=$((1 + ${RANDOM} % 50000 - 25000))
  mass=$((1 + ${RANDOM} % 50000))
  echo "${x} ${y} ${mass}"
done
