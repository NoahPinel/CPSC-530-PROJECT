all: test-encode1 test-encode2

test-encode1:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file1 "" "" "" 0

test-encode2:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file2 "" "" "" 0

test-encode3:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file3 "" "" "" 0

test-encode4:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file4 "" "" "" 0

clean:
	rm bccbt bitcodes lvls freqs
