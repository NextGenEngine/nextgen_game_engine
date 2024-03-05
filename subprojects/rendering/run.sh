# Install Rust and Cargo (assumes rustup is already installed)
rustup update
rustup default stable

# Install Meson and Ninja (assumes Python and pip are already installed)
pip install --user meson ninja

# Install Vulkan development packages (assumes a package manager like apt, dnf, or pacman is available)
# This step is platform-dependent and may vary. The example below is for Ubuntu-like systems.
# Since we cannot use sudo or install globally, we cannot actually perform this step.
# However, if it were possible, the command would look like this:
# sudo apt install libvulkan-dev libglfw3-dev

# Build the C part of the codebase using Meson and Ninja
meson builddir
ninja -C builddir
