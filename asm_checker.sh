
#!/bin/bash

counter=0
for filename in vm_champs/champs/*.s; do
       out=`./vm_champs/asm "$filename"`;
        if [ out -eq 0 ]; then
            echo "success"
        fi
       echo "$out"
       #./vm_champs/asm "$filename";
       counter=$((counter+1))
done

for i in `seq 1 $counter`
do
    echo "$i"
done

counter=0
for filename in vm_champs/champs/examples/*.s; do
       ./asm "$filename";
       ./vm_champs/asm "$filename";
       counter=$((counter+1))
done

for i in `seq 1 $counter`
do
    echo "$i"
done


    # print(file)
    # if (./asm == ./vm_champs/asm)
        # print(return EQUAL[+]);
    # else
        # print(return NOT_EQUAL[-]);
    # if (!diff)
        # print(NO_DIFF [+])
    # else
        # print(DIFF [-])