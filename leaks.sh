valgrind -s --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=valgrind_readline_leaks_ignore.txt --trace-children=yes  ./minishell
