import numpy as np
import matplotlib.pyplot as plt

# load the data from the file
data = np.loadtxt('diffusion_data.txt')

# assuming the number of grid points and time steps is known
N = len(data[0])  # number of grid points (columns)
nStep = len(data)  # number of time steps (rows)

# create a meshgrid for space and time
time = np.arange(nStep)
space = np.linspace(0, 1, N)  # space is between 0 and L (1.0 in the code)

# plotting the contour
plt.figure(figsize=(8, 6))
plt.contourf(space, time, data, 20, cmap='inferno')  # 20 levels for contours
plt.colorbar(label='Temperature')
plt.xlabel('Space (x)')
plt.ylabel('Time steps')
plt.title('Contour Plot of Diffusion Process')
plt.show()

