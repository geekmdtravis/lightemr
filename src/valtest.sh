#!/bin/bash

# Remove the database
if [ -e "lightemr.data" ]
then
    echo "Removing file."
    rm -f lightemr.data
else
    echo "The file does not exist."
fi

if [ -e "lightemr" ]
then
    echo "Beginning Valgrind test script."
else
    echo "LightEMR binary does not exist. Attempting to make"
    make clean all
fi

if [ -e "lightemr" ]
then
    # Add two patients to the database
    valgrind ./lightemr < ./code_testing/valgrind/tests/addtwo.test 2> ./code_testing/valgrind/output/addtwo.txt  
    # Lookup two patients from the database
    valgrind ./lightemr < ./code_testing/valgrind/tests/lookuptwo.test 2> ./code_testing/valgrind/output/lookuptwo.txt
    # Calculate an anion gap x 2
    valgrind ./lightemr < ./code_testing/valgrind/tests/aniongap.test 2> ./code_testing/valgrind/output/aniongap.txt
else
    echo "Was unable to make LightEMR from source files."
fi
