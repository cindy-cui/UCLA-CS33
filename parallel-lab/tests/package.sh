#!/bin/bash

if [[ "$#" != "1" ]]; then
  echo "Please specify your UID on the command line without dashes, e.g.:"
  echo "$0 123456789"
  exit 1
fi

tar -czvf $1.tar.gz Makefile $(ls *.cpp *.hpp 2>/dev/null) README.md
