all: test-encode1 test-encode2 test-encode3 test-encode4 test-decode4

test-encode1:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file1 "" "" "" 0
	rm bccbt
	py bytearray.py
test-encode2:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file2 "" "" "" 0
	rm bccbt
	py bytearray.py
test-encode3:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file3 "" "" "" 0
	rm bccbt
	py bytearray.py
test-encode4:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file4 "" "" "" 0
	py bytearray.py
test-pseudo-decode:
	gcc -o bccbt bccbt.c
	./bccbt "" bitcodes lvls freqs 1

clean:
	rm bccbt bitcodes lvls freqs output
