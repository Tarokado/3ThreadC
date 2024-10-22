#! /bin/bash
#void to print max number
max_number(){
    arr=(12 123 4 32 12 43 159)
    max=${arr[0]}
    for v in "${arr[@]}"; do  # Use quotes around "${arr[@]}"
        if (( v > max )); then
            max=$v
        fi
    done
    echo "The maximum number is: $max"
}
max_number
#Void calculate total number
ToTal_Nmb(){
    read -p "Enter numbers (e.g., 1234): " -a num_input
    sum=0
    for ((i=0;i<${num_input[@]};i++)); do
        num="${num_input:$i:1}"
        sum=$((sum + num))
    done
    echo "The total is: $sum" 
}
ToTal_Nmb
Date_time(){
    CURRENTDATE=`date +"%Y-%m-%d %T"`
    CURRENTDATEONLY=`date +"%b %d, %Y"`
    CURRENTEPOCTIME=`date +"%Y-%m-%d %T"`

    echo Current Date is: ${CURRENTDATEONLY}
    echo Current Date and Time is: `date +"%Y-%m-%d %T"`
    echo Current Date and Time is: ${CURRENTDATE}
}
All_files(){
    yourfilenames=`ls ./*.txt`
    for eachfile in $yourfilenames; do
        echo $eachfile
    done
}

Main_menu(){
    while true; do
    echo "--------Main Menu---------"
    echo "1. Show Today Date/Time"
    echo "2. Show all files in current directory"
    echo "3. Show users"
    echo "4. Show calendar"
    echo "5. Exit/Stop"

    read -p "Choose an option: " choice
    case $choice in
        1) Date_time;;
        2) All_files;;
        3) Show_users;;
        4) calendar;;
        5) exit 0;;
        *) echo "Invalid. Please choose again.";;
    esac
    done
}
Main_menu