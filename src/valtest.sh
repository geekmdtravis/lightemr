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
    # Add  patients to the database
    echo "TEST: Add patients to database."
    valgrind --leak-check=full ./lightemr < ./code_testing/valgrind/tests/add_patients.test 2> ./code_testing/valgrind/output/add_patients.txt  
    # Add  patients to the database with out of bounds requests
    echo "TEST: Add patients to database."
    valgrind --leak-check=full ./lightemr < ./code_testing/valgrind/tests/add_patients_oob.test 2> ./code_testing/valgrind/output/add_patients_oob.txt
    # Lookup a patient, view a note, then add a new note to database.
    echo "TEST: Lookup a patient, view the note, and then add a note to database."
    valgrind --leak-check=full ./lightemr < ./code_testing/valgrind/tests/lookup_viewnote_addnote.test 2> ./code_testing/valgrind/output/lookup_viewnote_addnote.txt

    # Calculate an anion gap x 2
    echo "TEST: Calculating the anion gap withOUT out of bounds values."
    valgrind --leak-check=full ./lightemr < ./code_testing/valgrind/tests/aniongap.test 2> ./code_testing/valgrind/output/aniongap.txt
        # Calculate an anion gap with out of bounds requests
    echo "TEST: Calculating the anion gap withOUT out of bounds values."
    valgrind --leak-check=full ./lightemr < ./code_testing/valgrind/tests/aniongap_oob.test 2> ./code_testing/valgrind/output/aniongap_oob.txt
else
    echo "Was unable to make LightEMR from source files."
fi
