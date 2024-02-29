#!/bin/bash

# Compile maze.c to generate the executable file maze
gcc maze.c -o maze

# Define test parameters for maze map files and commands
arg0="reg_5x5.txt"
arg1="reg_10x6.txt"
arg2="reg_15x8.txt"
arg3="q"  
arg4="w"  
arg5="a"  
arg6="d"  
arg7="s"  
arg8="m"  
arg9="nomap.txt"

echo -e "~~ Argument Tests ~~"

echo -n "Testing no arguments - "
# Test with no arguments
./maze > tmp
if grep -q "Usage: ./maze <map_file>" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing 2 arguments - "
# Test with 2 arguments
./maze x x > tmp
if grep -q "Usage: ./maze <map_file>" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\n~~ File Handling~~"

echo -n "Testing Error opening file - "
# Test error opening file
./maze nomap.txt > tmp
if grep -q "Failed to open file" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\n~~ Success ~~"

echo -e "\nTesting map display:"
# Test map display
timeout 0.2s ./maze $arg0 $arg8 > tmp
if grep -q "Current Map:" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\nTesting player movement functionality:"
# Test player movement functionality
timeout 0.2s ./maze $arg1 $arg4 > tmp 
if grep -q "Exiting the game. Goodbye !!!" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# Test reaching the end functionality
echo -e "\nTesting reaching the end functionality:"
timeout 0.2s ./maze $arg1 $arg4 $arg6 $arg6 $arg6 $arg6 > tmp 
if grep -q "Congratulations! You win!" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\nTesting invalid move:"
timeout 0.2s ./maze $arg0 $arg3 > tmp 
if grep -q "Invalid move. Use 'w', 'a', 's', or 'd'." tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# Remove the executable file
rm maze

# Check the exit status of the last command
if [ $? -eq 0 ]; then
    echo "Executable file 'maze' deleted successfully."
else
    echo "Failed to delete executable file 'maze'."
fi
