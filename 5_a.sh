#! /bin/bash
#program to generate prime numbers

echo "Enter lower bound: "
read n1
echo "Enter higher bound: "
read n2;
 
for (( i=n1 ; i<=n2 ; i++ ))
do
    flag=0
    for (( j=2 ; j<=i/2 ; j++ ))
    do 
        if [[ $(( i%j )) -eq 0 ]]
        then
            flag=1
            break
        fi
    done
    if [[ ${flag} -eq 0 && ${i} -ne 1 ]]
    then 
        echo -ne "$i "
    fi
done