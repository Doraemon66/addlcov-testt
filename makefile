CC	= gcc
CFLAG = -fPIC -fprofile-arcs -ftest-coverage
RM	= rm -rf

help: ## Makefile help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

main.o: main.c
	$(CC) $(CFLAG) -c -Wall -Werror main.c

foo.o: foo.c
	$(CC) $(CFLAG) -c -Wall -Werror foo.c

fib.o: fib.c
	$(CC) $(CFLAG) -c -Wall -Werror fib.c

build: main.o foo.o fib.o## Make build
	$(CC) $(CFLAG) -c -Wall -Werror main.c
	$(CC) $(CFLAG) -o main main.o foo.o fib.o

gcov: ## Run code coverage
	gcov main.c foo.c fib.c

coverage.info: gcov
	lcov --capture --directory . --output-file coverage.info

report: coverage.info ## Generate report
	genhtml coverage.info --output-directory out

clean: ## Clean all generate files
	$(RM) main *.o *.so *.gcno *.gcda *.gcov coverage.info out
