cd code/bin
./mainInput ../tests/$1
./minisat ../tests/$1.satinput ../tests/$1.satoutput
./mainOutput ../tests/$1