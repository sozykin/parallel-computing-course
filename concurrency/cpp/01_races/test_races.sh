#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 program_name number_of_launches"
fi
n=${2:-1000}
for (( i=0; i<n; i++ )) ; do $1 ; done | sort | uniq -c
