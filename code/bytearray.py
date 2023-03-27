from bitstring import BitArray
f = open("bitcodes", "r")

b = f.read()
f.close()
print(b+"\n")
if len(b) % 8 != 0 :
    for i in range (len(b) % 8):
        b = b + "0"
print(b)
c = bytearray(int(b[x:x+8], 2) for x in range(0, len(b), 8))
print(c)

with open('binaryfile', 'wb') as f:
    BitArray(bin=b).tofile(f)