#! /bin/bash

Main_menu(){
    while true; do
    echo "--------Main Menu---------"
    echo "1. Hien thi thu muc hien hanh"
    echo "2. Nhap vao duong dan, chuyen den thu muc moi theo duong dan"
    echo "3. Tao thu muc moi"
    echo "4. Doi ten thu muc"
    echo "5. Xoa thu muc"
    echo "6. Liet ke thu muc va tap tin trong thu muc hien hanh"
    echo "7. Tao file moi"
    echo "8. Doi ten file"
    echo "9. Xoa file"
    echo "10. Xem noi dung file"
    echo "11. Cap nhat noi dung cua file"
    echo "12. Di chuyen file"
    echo "13. Copy file"
    echo "14. Exit"

    read -p "Choose an option: " choice
    case $choice in
        1) Current_dir;;
        2) Move_to_folder;;
        3) Create_folder;;
        4) Change_name_folder;;
        5) Del_Folder;;
        6) List_folder;;
        7) Create_new_file;;
        8) Change_name_file;;
        9) Del_File;;
        10) Content_file;;
        11) Update_content_file;;
        12) Move_File;;
        13) Copy_File;;
        14) exit 0;;
        *) echo "Invalid. Please choose again.";;
    esac
    done
}
Current_dir(){
    CURRENT=`pwd`
    BASENAME=`basename "$CURRENT"`
    echo "$BASENAME"
}
Move_to_folder(){
# Prompt the user to enter a directory path
read -p "Enter the directory path: " dir_path
# Check if the entered path starts with '/' (indicating an absolute path)
    if [[ "$dir_path" =~ ^/ ]]; then
        # Check if the entered path exists and is a directory
        if [ -d "$dir_path" ]; then
            # Move to the directory
            cd "$dir_path" || {
                echo "Failed to move to $dir_path";
                exit 1;
            }
            echo "Successfully moved to $dir_path"
        else
            echo "Directory not found: $dir_path"
        fi
        else
        echo "Invalid path format. Please enter an absolute path starting with '/'"
    fi
}
Create_folder(){
    read -p "Enter folder name you want to create: " folder_name
    mkdir -p "/home/tairo/Codebash/Homework2/$folder_name"
    if [ $? -eq 0 ]; then
        echo "Directory '/home/tairo/Codebash/Homework2/$folder_name' created successfully."
    else
        echo "Failed to create directory."
    fi
}
# Function to rename a folder
Change_name_folder(){
    # Prompt the user to enter the folder they want to rename
    read -p "Enter the folder name you want to rename: " old_name
    # Check if the old folder exists
    if [ -d "/home/tairo/Codebash/Homework2/$old_name" ]; then
        # Prompt the user to enter the new folder name
        read -p "Enter the new folder name: " new_name
        # Rename the folder
        mv "/home/tairo/Codebash/Homework2/$old_name" "/home/tairo/Codebash/Homework2/$new_name"
        # Check if the rename was successful
        if [ $? -eq 0 ]; then
            echo "Folder renamed to '/home/tairo/Codebash/Homework2/$new_name' successfully."
        else
            echo "Failed to rename the folder."
        fi
    else
        echo "Folder '/home/tairo/Codebash/Homework2/$old_name' does not exist."
    fi
}
Del_Folder(){
    read -p "Enter a folder path you want to delete: " folder_name
    #Check if the folder exists
    if [ -d "/home/tairo/Codebash/Homework2/$folder_name" ]; then
        # Delete the folder
        rm -rf "/home/tairo/Codebash/Homework2/$folder_name"
        
        if [ $? -eq 0 ]; then
            echo "Directory '/home/tairo/Codebash/Homework2/$folder_name' deleted successfully."
        else
            echo "Failed to delete directory."
        fi
    else
        echo "Directory '/home/tairo/Codebash/Homework2/$folder_name' does not exist."
    fi
}
List_folder(){
    # List existing folders for the user to select
    echo "Available folders in /home/tairo/Codebash/Homework2:"
    ls -d /home/tairo/Codebash/Homework2/*/
}
Create_new_file(){
    read -p "Enter a file name you want create: " file_name
    touch "/home/tairo/Codebash/Homework2/$file_name"
    # Allow the user to append more content interactively
    echo "Enter additional content(Ctrl+D to save):"
    cat >> "/home/tairo/Codebash/Homework2/$file_name"
}
Change_name_file(){
    read -p "Enter a file you want to change: " old_name
    if [ -f "/home/tairo/Codebash/Homework2/$old_name" ]; then
        read -p "Enter the new file name: " new_name
        #rename a file
        mv "/home/tairo/Codebash/Homework2/$old_name" "/home/tairo/Codebash/Homework2/$new_name"
        # Check if the rename was successful
        if [ $? -eq 0 ]; then
            echo "File renamed to '/home/tairo/Codebash/Homework2/$new_name' successfully."
        else
            echo "Failed to rename the file."
        fi
    else
        echo "File home/tairo/Codebash/Homework2/$old_name does not exist"
    fi
}
Del_File(){
    read -p "Enter a folder path you want to delete: " file_name
    #Check if the folder exists
    if [ -f "/home/tairo/Codebash/Homework2/$file_name" ]; then
        # Delete the folder
        rm -rf "/home/tairo/Codebash/Homework2/$file_name"
        
        if [ $? -eq 0 ]; then
            echo "Directory '/home/tairo/Codebash/Homework2/$file_name' deleted successfully."
        else
            echo "Failed to delete file."
        fi
    else
        echo "File '/home/tairo/Codebash/Homework2/$file_name' does not exist."
    fi
}
Content_file(){
    while true; do
        read -p "Enter a name of file you want to see content: " file_name
        if [ -f "/home/tairo/Codebash/Homework2/$file_name" ]; then
            less /home/tairo/Codebash/Homework2/$file_name 
            break
        else
            echo "File '/home/tairo/Codebash/Homework2/$file_name' does not exist. Please try again."
        fi
    done
}
Update_content_file(){
    while true; do
        read -p "Enter a name of file you want to see update: " file_name
        if [ -f "/home/tairo/Codebash/Homework2/$file_name" ]; then
            # Prompt for the new content to add to the file
            echo "Enter the new content for the file (Ctrl+D to save):"
            cat > "/home/tairo/Codebash/Homework2/$file_name"
            echo "File '/home/tairo/Codebash/Homework2/$file_name' updated successfully."
            break  # Exit the loop after updating
        else
            # If the file does not exist, prompt the user to try again
            echo "File '/home/tairo/Codebash/Homework2/$file_name' does not exist. Please try again."
        fi
    done
}
Move_File(){
    read -p "Enter the file name you want to move: " file_name
    read -p "Enter the target directory: " target_directory

    # Check if the file exists
    if [ -f "/home/tairo/Codebash/Homework2/$file_name" ]; then
        # Check if the target directory exists
        if [ -d "$target_directory" ]; then
            # Move the file to the target directory
            mv "/home/tairo/Codebash/Homework2/$file_name" "$target_directory/"
            echo "File moved to '$target_directory/$file_name'."
        else
            echo "Target directory '$target_directory' does not exist."
        fi
    else
        echo "File '/home/tairo/Codebash/Homework2/$file_name' does not exist."
    fi
}
Copy_File(){
    read -p "Enter the file name you want to copy: " file_name
    read -p "Enter the target directory: " target_directory

    # Check if the file exists
    if [ -f "/home/tairo/Codebash/Homework2/$file_name" ]; then
        # Check if the target directory exists
        if [ -d "$target_directory" ]; then
            # Copy the file to the target directory
            cp "/home/tairo/Codebash/Homework2/$file_name" "$target_directory/"
            echo "File copied to '$target_directory/$file_name'."
        else
            echo "Target directory '$target_directory' does not exist."
        fi
    else
        echo "File '/home/tairo/Codebash/Homework2/$file_name' does not exist."
    fi
}
Main_menu