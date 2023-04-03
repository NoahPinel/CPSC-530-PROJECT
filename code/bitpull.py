from bitstring import BitArray

bits = BitArray(filename='binaryfile')
bit_array = [int(b) for b in bits.bin]

bit_string = ''.join(str(b) for b in bit_array)

with open('lamont', 'w') as f:
    f.write(bit_string)
