#!/bin/bash
# Test your cowsay program.

OUTPUTFILE="output.txt"

print_and_run()
{
  COMMAND=$1
  echo ">$COMMAND"
  $COMMAND
}

print_and_run "python3 cowsay.py Hello World!" >> $OUTPUTFILE
print_and_run "python3 cowsay.py -n kitteh Hello World!" >> $OUTPUTFILE
print_and_run "python3 cowsay.py -l" >> $OUTPUTFILE
print_and_run "python3 cowsay.py -n ninja Hello world!" >> $OUTPUTFILE
print_and_run "python3 cowsay.py Hello -n kitteh" >> $OUTPUTFILE

less $OUTPUTFILE
