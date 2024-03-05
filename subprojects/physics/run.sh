# Install Rust and Cargo using rustup (assumes rustup is already installed)
rustup update
rustup install stable

# Navigate to the physics_engine directory
cd physics_engine

# Build the project and its dependencies
cargo build

# Run tests
cargo test

# Run the physics_engine_demo executable (assuming there is a main.rs with a main function)
cargo run --bin physics_engine_demo
