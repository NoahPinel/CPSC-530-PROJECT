from bitstring import BitArray
f = open("bitcodes", "r")

b = f.read()
f.close()

#Dont think this is even needed using bitstring module
#if len(b) % 8 != 0 :
#    for i in range (len(b) % 8):
#        b = b + "0"

with open('binaryfile', 'wb') as f:
    BitArray(bin=b).tofile(f)