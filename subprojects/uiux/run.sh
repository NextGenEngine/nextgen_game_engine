# Install Meson build system and Ninja
pip install meson ninja

# Configure the Meson build directory
meson setup builddir

# Compile the codebase using Meson and Ninja
meson compile -C builddir
