ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))


all: test-encode1 test-encode2 test-encode3 test-encode4 test-decode

test-encode1:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file1 "" "" "" 0
	python3 bytearray.py
	gzip lvls
	rm bccbt bitcodes
test-encode2:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file2 "" "" "" 0
	python3 bytearray.py
	gzip lvls
	rm bccbt bitcodes
test-encode3:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file3 "" "" "" 0
	python3 bytearray.py
	gzip lvls
	rm bccbt bitcodes
test-encode4:
	gcc -o bccbt bccbt.c
	./bccbt tests/test_file4 "" "" "" 0
	python3 bytearray.py
	gzip lvls
	rm bccbt bitcodes
test-decode:
	gzip -d lvls.gz
	python3 bitpull.py
	gcc -o bccbt bccbt.c
	./bccbt "" bitcodes lvls freqs 1
	rm bitcodes lvls freqs binaryfile bccbt
 
clean:
	rm bccbt bitcodes lvls freqs output binaryfile
