# Install Rust and Meson build system
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
export PATH="$HOME/.cargo/bin:$PATH"
pip3 install --user meson
export PATH="$HOME/.local/bin:$PATH"

# Install Ninja build system
pip3 install --user ninja

# Build the project using Meson and Ninja
meson builddir
ninja -C builddir

# Run the executable
./builddir/game_world_management