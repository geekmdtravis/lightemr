#!/bin/bash

# remove the database
rm lightemr.data

# Add two patients to the database
valgrind ./lightemr < ./code_testing/valgrind/tests/addtwo.test 2> ./code_testing/valgrind/output/addtwo.txt

# Lookup two patients from the database
valgrind ./lightemr < ./code_testing/valgrind/tests/lookuptwo.test 2> ./code_testing/valgrind/output/lookuptwo.txt

