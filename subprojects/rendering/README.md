# NextGen Game Engine

First draft of game engine

## Install Rust and Cargo (assumes rustup is already installed)

```bash
rustup update
rustup default stable
```

## Install Meson and Ninja (assumes Python and pip are already installed)

```bash
pip install --user meson ninja
```

## Install Vulkan development packages (assumes a package manager like apt, dnf, or pacman is available)

This step is platform-dependent and may vary. The example below is for Ubuntu-like systems.

```bash
sudo apt install libvulkan-dev libglfw3-dev
```

## Build project with Meson

GCC/MSVC:

```bash
meson builddir
meson compile -C builddir
```

LLVM/CLANG:

```bash
meson setup --cross-file clang_cross_file.txt builddir
meson compile -C builddir
```

Strip executable to remove debug symbols and make executable smaller:

GCC:

```bash
strip builddir/nextgen_game_engine
```

LLVM/CLANG:

```bash
llvm-strip-14 builddir/nextgen_game_engine
```

**_NOTE_**: Building with LLVM/CLang may require additional configuration
in `clang_cross_file.txt` file. For example, this line:

```bash
strip = 'llvm-strip-14' # or 'strip' if llvm-strip-14 is not available
```

is specific for LLVM version 14. If you have another version of LLVM/CLang,
then you must specify there another command for stripping

## Installing in current system

```bash
meson install
```

This command will strip executable automatically.
