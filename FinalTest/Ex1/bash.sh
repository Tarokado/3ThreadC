# Tran Vu Hong Phuc - 21ES - 123210021
# Exercise 1: Password Validation Script

#!/bin/bash

# Check if a password is provided as a command-line argument
if [ -z "$1" ]; then
  # If no password is provided, prompt the user to enter one
  echo -n "Enter your password: "
  read password # Read password input from the user
  echo # Print a newline for better formatting
else
  # If a password is provided as an argument, use it
  password="$1"
fi

# Check if the password meets the minimum length requirement
if [[ ${#password} -lt 8 ]]; then
  # Password must be at least 8 characters long
  echo "Password does not meet the condition: At least 8 characters."
  exit 1 # Exit with error code 1
fi

# Check if the password contains at least one numeric digit
if ! [[ "$password" =~ [0-9] ]]; then
  echo "Password does not meet the condition: At least 1 digit."
  exit 1 # Exit with error code 1
fi

# Check if the password contains at least one uppercase letter
if ! [[ "$password" =~ [A-Z] ]]; then
  echo "Password does not meet the condition: At least 1 uppercase letter."
  exit 1 # Exit with error code 1
fi

# Check if the password contains at least one lowercase letter
if ! [[ "$password" =~ [a-z] ]]; then
  echo "Password does not meet the condition: At least 1 lowercase letter."
  exit 1 # Exit with error code 1
fi

# Check if the password contains at least one special character
if ! [[ "$password" =~ [\@\#\$\%\^\&\*\!] ]]; then
  echo "Password does not meet the condition: At least 1 special character (@#$%^&*!)."
  exit 1 # Exit with error code 1
fi

# Check if the password contains any whitespace
if [[ "$password" =~ [[:space:]] ]]; then
  echo "Password does not meet the condition: No spaces allowed."
  exit 1 # Exit with error code 1
fi

# If all conditions are met, display a success message
echo "Password meets all conditions."
