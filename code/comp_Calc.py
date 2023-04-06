"""
Simple script to get values for our testing.
- Saving Percentage
- Compression Ratio

Note, 

ALL calculations are done at the bit level.

To run this you must first run some sort of
make test-encodeXXX since this relies on another 
program, read below.

this program relies on having path to the base file
and the 3 generated files from bccbt
- binaryfile
- freqs
- lvls.gz


Machine tested on:
OS: Debian GNU/Linux 11 (bullseye)
Kernel: 5.15.90.1-microsoft-standard-WSL2

Author: Noah Pinel
Date: 2023-04-05
Version: 1.0
"""
import os
import datetime

def file_size(file_path):
    if os.path.isfile(file_path):
        file_info = os.stat(file_path)
        return file_info.st_size

def saving_Per(orig_file, comp_file):
    numerator = float(orig_file) - float(comp_file)
    sav_per = (numerator / orig_file) * 100
    rounded_sav_per = round(sav_per, 2)
    return "Saving Percentage: {:.2f}%".format(rounded_sav_per)

def comp_ratio(orig_file, comp_file):
    ratio = (float(comp_file) / float(orig_file)) * 100
    rounded_ratio = round(ratio, 2)
    return "Compression Ratio: {:.2f}%".format(rounded_ratio)


def output(orig_path,output_list,orig_size,sum_trio):
    program_name = "Compression Stats"
    version = "V 1.0"
    now = datetime.datetime.now()
    date_time = now.strftime("%Y-%m-%d %H:%M:%S")

    print("============================")
    print("{}".format(program_name))
    print("{}".format(version))
    print("{}".format(date_time))
    print("============================\n")
    print("Original file name: \n- " + orig_path +" "+ '('+ str(orig_size) + ' bits)')
    print('\n')
    print("Compressed file names: \n- " + "\n- ".join(output_list))
    print('\n')
    print("Size of the compressed trio:\n- " + str(sum_trio) +' bits')
    print('\n')
    print(saving_Per(orig_size, sum_trio))
    print(comp_ratio(orig_size, sum_trio))
def main():

    orig_path = r"battlearena/1MB.txt"
    comp_paths = [r"binaryfile", r"freqs", r"lvls.gz"]
    size_bytes = []
        

    for path in comp_paths:
        size_bytes.append(file_size(path))
    
    
    sum_trio = sum(size_bytes)
    orig_size = file_size(orig_path)

    
    output_list = []
    for path, size in zip(comp_paths, size_bytes):
        output_list.append("{} ({} bits)".format(path, size))
    
    output(orig_path,output_list,orig_size,sum_trio)


main()