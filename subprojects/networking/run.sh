# Install Rust and Cargo using rustup (assumes rustup is already installed)
rustup update
rustup install stable

# Install Meson build system (assumes Python and pip are already installed)
pip install --user meson

# Install Ninja build system (assumes a package manager like brew is available)
brew install ninja

# Install dependencies using Cargo
cargo fetch

# Build the project using Meson and Ninja
meson builddir
ninja -C builddir