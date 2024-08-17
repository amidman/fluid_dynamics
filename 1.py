import matplotlib.pyplot as plt
import numpy as np
import struct

with open("./build/8.bin", mode='rb') as file: # b is important -> binary
    fileContent = file.read()

N,M = struct.unpack("ii", fileContent[:8])

#data = np.array(struct.unpack("d"*N*M, fileContent[8:])).reshape((N, M))
data = np.array(struct.unpack("d"*N*M*4, fileContent[8:])).reshape((N,M,4))

print(N,M)
print(data[:,:,2])

fig, ax = plt.subplots()

x = np.arange(0, N, 1)
y = np.arange(0, M, 1)

Y, X = np.meshgrid(x, y, indexing='ij')

ax.imshow(data[:,:,0], aspect='auto')
#ax.streamplot(X, Y, data[:,:,2], data[:,:,3], density=10)
ax.quiver(X, Y, data[:,:,2], data[:,:,3])

plt.show()