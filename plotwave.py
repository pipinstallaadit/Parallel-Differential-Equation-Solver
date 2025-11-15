import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import glob
import os

print("Finding data files...")
files = sorted(glob.glob('wave_output/wave_*.dat'))

if not files:
    print("Error: No data files found in 'wave_output/'.")
    print("Did you run the C++ program first?")
    exit()

print(f"Found {len(files)} data files.")

# --- Set up the plot ---
fig, ax = plt.subplots()

# Load the first frame to set up the plot
data = np.loadtxt(files[0])
im = ax.imshow(data, cmap='RdBu', vmin=-50, vmax=50) 
fig.colorbar(im, label='Amplitude')

def update(frame):
    data = np.loadtxt(files[frame])
    im.set_data(data)
    time_step = int(os.path.basename(files[frame])[5:-4])
    ax.set_title(f'2D Wave Equation - Time Step {time_step}')
    return [im]

# --- Create and run the animation ---

ani = animation.FuncAnimation(fig, update, frames=len(files), 
                              interval=30, blit=True)

print("Starting animation... Close the window to stop.")
plt.show()

print("Saving animation to wave_animation.mp4...")
ani.save('wave_animation.mp4', writer='ffmpeg', fps=30)
print("Done saving.")