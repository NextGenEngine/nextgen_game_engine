# Install Meson and Ninja build system
pip install --user meson ninja

# Setup the build directory
meson setup builddir

# Compile the project
meson compile -C builddir

# Run the executable
./builddir/game_engine
