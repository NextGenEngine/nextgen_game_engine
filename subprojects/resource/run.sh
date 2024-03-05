# Install Rust and Cargo using rustup (assumes rustup is already installed)
rustup update
rustup install stable

# Install Meson build system (assumes Python and pip are already installed)
pip install --user meson

# Install dependencies using Cargo
cargo check

# Build the project using Meson
meson builddir
ninja -C builddir

# Run tests (if any) using Cargo in parallel
cargo test -- --test-threads=4
