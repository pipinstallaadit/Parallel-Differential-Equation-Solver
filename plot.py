import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm # Color maps

print("Loading data for all 3 slices...")
# Load the data from the three files
try:
    data_yz = np.loadtxt('slice_YZ.dat')
    data_xz = np.loadtxt('slice_XZ.dat')
    data_xy = np.loadtxt('slice_XY.dat')
except IOError as e:
    print(f"Error loading files: {e}")
    print("Please make sure 'slice_YZ.dat', 'slice_XZ.dat', and 'slice_XY.dat' exist.")
    exit()

print("Generating 3D surface plots...")

# --- Create a figure with 3 subplots ---
# We add the 'projection="3d"' to each subplot individually
fig = plt.figure(figsize=(20, 7))

# --- Helper function to create coordinate grids ---
def get_meshgrid(data):
    grid_size_x = data.shape[0]
    grid_size_y = data.shape[1]
    X = np.arange(0, grid_size_x)
    Y = np.arange(0, grid_size_y)
    X, Y = np.meshgrid(Y, X)
    return X, Y

# --- Plot 1: YZ Slice ---
ax1 = fig.add_subplot(131, projection='3d')
X_yz, Y_yz = get_meshgrid(data_yz)
Z_yz = data_yz
surf1 = ax1.plot_surface(X_yz, Y_yz, Z_yz, cmap='hot', 
                         rstride=5, cstride=5, linewidth=0, antialiased=False)
ax1.set_title('YZ Slice')
ax1.set_xlabel('Z Position')
ax1.set_ylabel('Y Position')
ax1.set_zlabel('Temperature (°C)')
fig.colorbar(surf1, ax=ax1, shrink=0.5, aspect=10, label='Temp')

# --- Plot 2: XZ Slice ---
ax2 = fig.add_subplot(132, projection='3d')
X_xz, Y_xz = get_meshgrid(data_xz)
Z_xz = data_xz
surf2 = ax2.plot_surface(X_xz, Y_xz, Z_xz, cmap='hot', 
                         rstride=5, cstride=5, linewidth=0, antialiased=False)
ax2.set_title('XZ Slice')
ax2.set_xlabel('Z Position')
ax2.set_ylabel('X Position')
ax2.set_zlabel('Temperature (°C)')
fig.colorbar(surf2, ax=ax2, shrink=0.5, aspect=10, label='Temp')

# --- Plot 3: XY Slice ---
ax3 = fig.add_subplot(133, projection='3d')
X_xy, Y_xy = get_meshgrid(data_xy)
Z_xy = data_xy
surf3 = ax3.plot_surface(X_xy, Y_xy, Z_xy, cmap='hot', 
                         rstride=5, cstride=5, linewidth=0, antialiased=False)
ax3.set_title('XY Slice')
ax3.set_xlabel('Y Position')
ax3.set_ylabel('X Position')
ax3.set_zlabel('Temperature (°C)')
fig.colorbar(surf3, ax=ax3, shrink=0.5, aspect=10, label='Temp')

# --- Final Touches ---
plt.suptitle('3D Laplace Equation - Center Slices (Surface Plots)', fontsize=16)
plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Adjust layout to make room for title

print("Displaying plot. You can click and drag each plot to rotate it.")
plt.show()