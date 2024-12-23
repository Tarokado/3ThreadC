#! /bin/bash 
receive_input(){
    read -p "Enter first number: " -a num_1
    read -p "Enter second number: " -a num_2
}
# Function to perform addition
Addition() {
    sum=$((num_1 + num_2))
    echo "The sum of $num_1 and $num_2 is: $sum"
}

# Function to perform subtraction
Subtraction() {
    diff=$((num_1 - num_2))
    echo "The difference between $num_1 and $num_2 is: $diff"
}

# Function to perform multiplication
Multiplication() {
    product=$((num_1 * num_2))
    echo "The product of $num_1 and $num_2 is: $product"
}

# Function to perform division
Division() {
    if [ $num_2 -eq 0 ]; then
        echo "Error: Division by zero is not allowed."
    else
        quotient=$((num_1 / num_2))
        echo "The quotient of $num_1 divided by $num_2 is: $quotient"
    fi
}
Main_menu(){
    while true; do
    echo "--------Main Menu---------"
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo "5. Exit/Stop"
    read -p "Choose an option: " choice
    case $choice in
        1) Addition;;
        2) Subtraction;;
        3) Multiplication;;
        4) Division;;
        5) exit 0;;
        *) echo "Invalid. Please choose again.";;
    esac
    done
}

# First, receive input from the user
receive_input
# Then, display the main menu
Main_menu