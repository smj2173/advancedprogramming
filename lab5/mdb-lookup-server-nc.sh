#!/bin/sh



chmod +x mdb-lookup-server-nc.sh

mkfifo mypipe-$$

cat mypipe-$$ | nc -l $1 | /home/jae/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe-$$

rm -f mypipe-$$
