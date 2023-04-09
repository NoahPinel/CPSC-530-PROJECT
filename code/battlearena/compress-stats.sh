#!/bin/bash

# Get the initial size of the file
init_size=$(du -b "$1" | cut -f1)

echo "INITIAL SIZE:"
echo "$init_size"

echo " "
echo "COMPRESS:"
time gzip "$1"

echo " "
echo "COMPRESSED SIZE:"
compressed_size=$(du -b "$1".gz | cut -f1)
echo "$compressed_size"

echo " "
echo "DECOMPRESS:"
time gzip -d "$1".gz

echo " "
echo "SAVING PERCENT:"
saving_percent=$(echo "scale=4;($init_size - $compressed_size) / $init_size * 100" | bc | awk '{ printf("%.2f",$1)}')
echo "$saving_percent%"

echo " "
echo "COMPRESSION RATIO:"
compression_ratio=$(echo "scale=4;$compressed_size / $init_size * 100" | bc | awk '{ printf("%.2f",$1)}')
echo "$compression_ratio%"

