#!/bin/bash
n=${2:-1000}
for (( i=0; i<n; i++ )) ; do $1 ; done | sort | uniq -c
