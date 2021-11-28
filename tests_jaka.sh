#!/bin/bash


< infile cat | wc > outfile_orig
MY_EXITCODE=$?
./pipex infile cat wc outfile_mine
ORIG_EXITCODE=$?

echo $MY_EXITCODE
echo $ORIG_EXITCODE