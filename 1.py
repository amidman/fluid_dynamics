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
#fig2, ax2 = plt.subplots()


x = np.arange(0, 500, 1)
y = np.arange(0, 500, 1)

Y, X = np.meshgrid(x, y, indexing='ij')

#ax1.plot(open_bin("./saves/141.bin")[10,:,0])
#ax1.plot(open_bin("./saves/151.bin")[10,:,0])
#ax1.plot(open_bin("./saves/161.bin")[10,:,0])
#ax1.plot(open_bin("./saves/171.bin")[10,:,0])
#ax1.plot(open_bin("./saves/181.bin")[10,:,0])
#ax1.plot(open_bin("./saves/191.bin")[10,:,0])

data = open_bin("./saves/1001.bin")

print(data[:,:,2])

ax1.imshow(data[:,:,0], aspect='auto', interpolation='bicubic')
#ax1.quiver(X, Y, data[:,:,2], -data[:,:,3])
#
#ax2.imshow(data[:,:,1], aspect='auto')
#ax2.quiver(X, Y, data[:,:,2], -data[:,:,3])

plt.show()