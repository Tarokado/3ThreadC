#! /bin/bash

#2 Dataset of students: students file and classes files
students_File="students.txt"
classes_File="classes.txt"
#Function to take student information
Students_info(){
    # Prompt the user to input the student's name and read it from the keyboard
    read -p "Enter student name: " student_name
    # Prompt the user to input the student's address and read it from the keyboard
    read -p "Enter address: " student_address
    # Prompt the user to input the student's phone number and read it from the keyboard
    read -p "Enter phone number: " student_num
    # Write the information in "name | address | phone" format to the file
    echo "$student_name | $student_address | $student_num" >> "$students_File"
}
Classes_info(){
    # Prompt the user to input the class name and read it from the keyboard
    read -p "Enter class: " class_name
    # Prompt the user to input the room study and read it from the keyboard
    read -p "Enter room: " room_study
    # Prompt the user to input the class schedule and read it from the keyboard
    read -p "Enter class's schedule: " >> stu_schedule
    # Write the information in "name | address | phone" format to the file
    echo "$class_name | $room_study | $stu_schedule" >> "$classes_File"
}
Display_student_info(){
    #Use less to display all the data if the dataset is big, cover all information. Instead of using cat
    less $students_File
    #cat $students_File
    # After exiting less, print a message and return to the terminal
}
Display_class_info(){
    #Use less to display all the data if the dataset is big, cover all information. Instead of using cat
    less $classes_File
    #cat $student_File
}
#Function to print student information
#i think printing information of the name of student it will print all information of that student, 
#And some student have same name with there related information
Search_student_info(){
    #Enter a student name:
    read -p "Enter the Student name you want to seach: " search_stu
    #Using grep to find for student name in students.txt files
    result=$(grep "$search_stu" "$students_File")
    #condition to check for the student in file. Match print all information have same name. If not print "not found" and exit
    if [ $? -eq 0 ]; then
        echo "----Students found----"
        # Print each matching result
        echo "$result"
    else
        # If student is not found
        echo "Student not found."
    fi
}
#Function to print class information, 
#i think printing information of the class it will print all information of that class, 
#And some class have same name with there related information
Search_class_info(){
    #Enter a class you want to search
    read -p "Enter the class name you want to search: " class_search
    #does the same things with search for student information
    result=$(grep "$class_search" "$classes_File")
    if [ $? -eq 0 ]; then
        echo "----Class found----"
        # Print each matching result
        echo "$result"
    else
        # If class is not found
        echo "Class not found."
    fi
}
#Building main menu, for administrator management all infor mation, update information, check for student or class,...
Main_menu(){
    #start an infinite loop to continuously display the main menu until the user decides to exit
    while true; do
    
    # Print the main menu options to the terminal
    echo "--------Main Menu---------"
    echo "1. Update student information"
    echo "2. Update class information"
    echo "3. Display student information"
    echo "4. Display class information"
    echo "5. Search student information"
    echo "6. Search class information:"
    echo "7. Exit/Stop"
    # Prompt the user to select an option and read the input into the variable 'choice'
    read -p "Choose an option: " choice
    #Create case with 7 options for administrators
    case $choice in
        # If the user selects option 1, call the function `Students_info` to update student information
        1) Students_info;;

        # If the user selects option 2, call the function `Classes_info` to update class information
        2) Classes_info;;

        # If the user selects option 3, call the function `Display_student_info` to display student information
        3) Display_student_info;;

        # If the user selects option 4, call the function `Display_class_info` to display class information
        4) Display_class_info;;

        # If the user selects option 5, call the function `Search_student_info` to search for student information
        5) Search_student_info;;

        # If the user selects option 6, call the function `Search_class_info` to search for class information
        6) Search_class_info;;

        # If the user selects option 7, exit the script with a success status
        7) exit 0;;

        # If the user enters an invalid option, print an error message and prompt them to choose again
        *) echo "Invalid!!! Please choose again.";;
        esac
    done
}

Main_menu
