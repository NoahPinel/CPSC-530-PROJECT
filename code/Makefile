all: test-encode1 test-encode2

test-encode1:
	gcc -o bccbt bccbt.c
	./bccbt test_file1 "" "" "" 0

test-encode2:
	gcc -o bccbt bccbt.c
	./bccbt test_file2 "" "" "" 0

clean:
	rm bccbt
