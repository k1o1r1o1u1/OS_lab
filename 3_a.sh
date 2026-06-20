#! /bin/bash
#palindrome or NOT

echo "Enter a string: "
read str
len=${#str}

for(( i=len-1 ; i>=0 ; i--))
do  
    reverse=$reverse${str:i:1}
done
if [ "$reverse" == "$str" ]
then
    echo "The string is Palindrome."
else
    echo "The string is NOT a palindrome."
fi