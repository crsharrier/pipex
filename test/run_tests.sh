#!/bin/bash

# Set the directory containing test files (modify if needed)
TEST_FILES_DIR="./testfiles/"

RED='\033[0;31m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
RESET='\033[0m'

# Initialize counter
counter=0

ln -s ../pipex .

# Loop through each line in the test cases file
while IFS= read -r line; do
  # Increment counter
  ((counter++))

  # Print test case information based on counter
  case $((counter % 4)) in
    1)
      test_case_num=$(echo "$line")
      ;;
    2)
      bash_cmd=$(echo "$line")
      ;;
    3)
      pipex_cmd=$(echo "$line")
      ;;
    0)
      # Execute bash command
      # echo -e "Bash Command: ${CYAN} $bash_cmd ${RESET}"
      eval $bash_cmd  # Execute the command

      # Execute pipex command
      # echo -e "Pipex Command: ${GREEN} $pipex_cmd ${RESET}"
      eval $pipex_cmd  # Execute the command

      # Compare output files
      # echo "Comparing outputs..."
      ./compare_files "$test_case_num" "${TEST_FILES_DIR}/outfile.txt" "${TEST_FILES_DIR}/ft_outfile.txt"

      # Clear output files for next test case
      rm -f "${TEST_FILES_DIR}/outfile.txt" "${TEST_FILES_DIR}/ft_outfile.txt"
      ;;
  esac

done < "test_cases.txt"

rm pipex

echo "Test cases completed."
