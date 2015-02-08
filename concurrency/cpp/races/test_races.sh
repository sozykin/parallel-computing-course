for i in {1..1000}; do $1 ; done | sort | uniq -c
