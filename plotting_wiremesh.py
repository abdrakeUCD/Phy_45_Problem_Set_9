import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# read data from diffusion_data.txt
data = []
with open("diffusion_data.txt", "r") as file:
    for line in file:
        data.append(list(map(float, line.split())))

# make into numpy array for computer to read
data = np.array(data)

# create a meshgrid for single plane; x \sim space and y \sim time; data stored as (time, space) in txt file
time_steps = data.shape[0]
grid_points = data.shape[1]
X, Y = np.meshgrid(np.arange(grid_points), np.arange(time_steps))

# init 3D plot
fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111, projection='3d')

# plot wireframe
ax.plot_wireframe(X, Y, data, rstride=5, cstride=5, color='b')

# axes labels
ax.set_xlabel('Grid Points')
ax.set_ylabel('Time Steps')
ax.set_zlabel('Temperature')

# show plot
plt.show()

# save plot
plt.savefig("wiremesh_plot.png")
