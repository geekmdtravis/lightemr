#!/bin/bash

# Remove the database
if [ -e "lightemr.data" ]
then
    echo "Removing file."
    rm -f lightemr.data
else
    echo "Database lightemr.data does not exist."
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
    valgrind ./lightemr < ./code_testing/valgrind/tests/add_patients.test 2> ./code_testing/valgrind/output/add_patients.txt  
    # Lookup two patients from the database
    valgrind ./lightemr < ./code_testing/valgrind/tests/lookup_patients.test 2> ./code_testing/valgrind/output/lookup_patient.txt
    # Calculate an anion gap x 2
    valgrind ./lightemr < ./code_testing/valgrind/tests/aniongap.test 2> ./code_testing/valgrind/output/aniongap.txt
else
    echo "Was unable to make LightEMR from source files."
fi
