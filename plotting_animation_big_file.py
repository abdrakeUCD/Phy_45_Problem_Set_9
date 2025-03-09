import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# loading data
data = np.loadtxt("N=30000_diffusion_data.txt") # shape : (time steps, drid points)
num_steps, num_points = data.shape

# figure config
fig, ax = plt.subplots(figsize=(8,2)) # wide and this so it looks like the rod
rod = ax.imshow([data[0]], cmap = "hot", aspect = "auto", vmin =0, vmax=np.max(data))
ax.set_xticks([])
ax.set_yticks([])
ax.set_title("Heat Diffusion Along a Rod")

# animation update function
def update(frame):
    rod.set_array([data[frame]]) #update the heatmap
    ax.set_title(f"Heat Diffusion (Time Step {frame})")
    return rod,

# animation
ani = animation.FuncAnimation(fig, update, frames=num_steps, interval=50, blit=False)

plt.show()

ani.save("heat_diffusion.gif", writer="pillow", fps=30)
