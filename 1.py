import matplotlib.pyplot as plt
import numpy as np
import struct


def open_bin(file_name):
    with open(file_name, mode='rb') as file: # b is important -> binary
        fileContent = file.read()

    N,M = struct.unpack("ii", fileContent[:8])

    #data = np.array(struct.unpack("d"*N*M, fileContent[8:])).reshape((N, M))
    data = np.array(struct.unpack("d"*N*M*4, fileContent[8:])).reshape((N,M,4))
    return data

fig1, ax1 = plt.subplots()
fig2, ax2 = plt.subplots()


x = np.arange(0, 100, 1)
y = np.arange(0, 100, 1)

Y, X = np.meshgrid(x, y, indexing='ij')

#ax.plot(open_bin("./saves/100.bin")[10,:,1])
#ax.plot(open_bin("./saves/200.bin")[10,:,1])
#ax.plot(open_bin("./saves/500.bin")[10,:,1])
#ax.plot(open_bin("./saves/1000.bin")[10,:,1])
#ax.plot(open_bin("./saves/1500.bin")[10,:,1])
#ax.plot(open_bin("./saves/2000.bin")[10,:,1])

data = open_bin("./saves/2.bin")

print(data[:,:,2])

ax1.imshow(data[:,:,0], aspect='auto')
#ax.streamplot(X, Y, data[:,:,2], data[:,:,3], density=10)
ax1.quiver(X, Y, data[:,:,2], -data[:,:,3])

ax2.imshow(data[:,:,1], aspect='auto')
ax2.quiver(X, Y, data[:,:,2], -data[:,:,3])

plt.show()