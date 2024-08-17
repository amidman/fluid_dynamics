import matplotlib.pyplot as plt
import numpy as np
import struct

with open("./build/foo.bin", mode='rb') as file: # b is important -> binary
    fileContent = file.read()

N,M = struct.unpack("ii", fileContent[:8])

data = np.array(struct.unpack("d"*N*M, fileContent[8:])).reshape((N, M))

print(N,M)
print(data)

fig, ax = plt.subplots()

ax.imshow(data)

plt.show()