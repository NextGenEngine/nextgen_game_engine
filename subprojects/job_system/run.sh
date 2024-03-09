# Install Meson and Ninja build system
pip install meson ninja

apt install libboost-f-dev
apt install libboost-dev
apt install libboost-fiber-dev
apt install libhwloc-dev

# Setup the build directory
meson setup builddir

# Build the project
meson compile -C builddir

# Run the executable
./builddir/green_threads_job_system
