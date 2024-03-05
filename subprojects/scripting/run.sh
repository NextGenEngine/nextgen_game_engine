# a) Install dependencies
cd scripting_engine
cargo build

# b) Run all necessary parts of the codebase
cargo run &
meson build && ninja -C build &
