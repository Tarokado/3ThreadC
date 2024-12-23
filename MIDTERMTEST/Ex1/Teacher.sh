#Tran Vu Hong Phuc - 21ES - Exercise1

#! /bin/bash

#2 Dataset of Teacher: Teacher file and Faculty files
Teacher_File="Teacher.txt"
Faculty_File="Faculty.txt"
#Function to take Teacher information
Teacher_info(){
    # Prompt the user to input the Faculty's name and read it from the keyboard
    read -p "Enter number of faculty: " Faculty_number
    # Prompt the user to input the position of teacher and read it from the keyboard
    read -p "Enter position of teacher: " Position_teacher
    # Prompt the user to input the name of teacher and read it from the keyboard
    read -p "Enter name of teacher: " Teacher_name
    # Write the information in "Faculty numbeer | Position of Teacher | Teacher name" format to the file
    echo "$Faculty_number | $Position_teacher | $Teacher_name" >> "$Teacher_File"
}
#Function to take Faculty information
Faculty_info(){
    # Prompt the user to input the Faculty number and read it from the keyboard
    read -p "Enter number of faculty: " Faculty_number
    # Prompt the user to input the Faculty name and read it from the keyboard
    read -p "Enter Faculty name: " Faculty_name
    # Prompt the user to input the header of faculty and read it from the keyboard
    read -p "Enter name of header: "  Faculty_header
    # Write the information in "Faculty number | Faculty name | Faculty header" format to the file
    echo "$Faculty_number | $Faculty_name | $Faculty_header" >> "$Faculty_File"
}
#Function to display teacher information
Display_Teacher_info(){
    #Use less to display all the data if the dataset is big, cover all information. Instead of using cat
    less $Teacher_File
    #cat $Teachers_File
    # After exiting less, print a message and return to the terminal
}
#Functionn to display faculty information
Display_Faculty_info(){
    #Use less to display all the data if the dataset is big, cover all information. Instead of using cat
    less $Faculty_File
    #cat $Teacher_File
}
#Function to print Teacher information
#i think printing information of the name of teacher it will print all information of that Teacher, 
#And some Teacher have same name with there related information
Search_Teacher_info(){
    #Enter a Teacher name:
    read -p "Enter the Teacher name you want to seach: " Teacher_search
    #Using grep to find for Teacher name in Teacher.txt files
    result=$(grep "$Teacher_search" "$Teacher_File")
    #condition to check for the Teacher in file. Match print all information have same name. If not print "not found" and exit
    if [ $? -eq 0 ]; then
        echo "----Teacher found----"
        # Print each matching result
        echo "$result"
    else
        # If teacher is not found
        echo "Teacheer not found."
    fi
}
#Function to print faculty information, 
#i think printing information of the faculty it will print all information of that Faculty, 
#And some Faculty have same name with there related information
Search_Faculty_info(){
    #Enter a Faculty you want to search
    read -p "Enter the Faculty name you want to search: " Faculty_search
    #does the same things with search for Teacher information
    result=$(grep "$Faculty_search" "$Faculty_File")
    if [ $? -eq 0 ]; then
        echo "----Faculty found----"
        # Print each matching result
        echo "$result"
    else
        # If Faculty is not found
        echo "Faculty not found."
    fi
}
#Building main menu, for administrator management all infor mation, update information, check for Teacher or Faculty,...
Main_menu(){
    #start an infinite loop to continuously display the main menu until the user decides to exit
    while true; do
    
    # Print the main menu options to the terminal
    echo "--------Main Menu---------"
    echo "1. Update Teacher information"
    echo "2. Update Faculty information"
    echo "3. Display Teacher information"
    echo "4. Display Faculty information"
    echo "5. Search Teacher information"
    echo "6. Search Faculty information:"
    echo "7. Exit/Stop"
    # Prompt the user to select an option and read the input into the variable 'choice'
    read -p "Choose an option: " choice
    #Create case with 7 options for administrators
    case $choice in
        # If the user selects option 1, call the function `Teacher_info` to update Teacher information
        1) Teacher_info;;

        # If the user selects option 2, call the function `Faculty_info` to update Faculty information
        2) Faculty_info;;

        # If the user selects option 3, call the function `Display_Teacher_info` to display Teacher information
        3) Display_Teacher_info;;

        # If the user selects option 4, call the function `Display_Faculty_info` to display Faculty information
        4) Display_Faculty_info;;

        # If the user selects option 5, call the function `Search_Teacher_info` to search for Teacher information
        5) Search_Teacher_info;;

        # If the user selects option 6, call the function `Search_Faculty_info` to search for Faculty information
        6) Search_Faculty_info;;

        # If the user selects option 7, exit the script with a success status
        7) exit 0;;

        # If the user enters an invalid option, print an error message and prompt them to choose again
        *) echo "Invalid!!! Please choose again.";;
        esac
    done
}

Main_menu
