#! /bin/bash
echo "Enter the number of elements: "
read n
echo "Enter the elements: "
for(( i=0 ; i<n ; i++))
do
    read a[${i}]
done
max=${a[0]}

for(( i=1 ; i<n; i++))
do
    if(( ${a[$i]}>$max ))
    then 
            max=${a[$i]}
    fi
done
echo "The largest number is $max"