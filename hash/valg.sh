# valgrind --leak-check=full --show-leak-kinds=all listtest.sh
#valgrind --leak-check=full listtest.sh

#valgrind  test1
#valgrind test2
#valgrind test3
#valgrind test4
#valgrind test6
#valgrind test7
#valgrind test8
#valgrind test9
#valgrind test10*/
#valgrind --leak-check-full test2
#valgrind --leak-check-full test3
#valgrind --leak-check-full test4
#valgrind --leak-check-full test6
#valgrind --leak-check-full test7
#valgrind --leak-check-full test8
#valgrind --leak-check-full test9
#valgrind --leak-check-full test10

count=0  # Initialize a count variable

# Loop through your valgrind commands
for test_command in queue_test1 queue_test2 queue_test3 queue_test4; do
    # Run valgrind and count occurrences of "hi"
    occurrences=$(valgrind "$test_command" 2>&1 | grep -c "All heap blocks were freed -- no leaks are possible")

    # Increment the count variable by the number of occurrences
    count=$((count + occurrences))
done

# Print the total count
echo "Total 'All heap blocks were freed -- no leaks are possible' occurrences: $count"
