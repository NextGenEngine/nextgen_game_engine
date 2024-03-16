# NextGen Game Engine

First draft of game engine

## Install Bazel

Use installation instrutions from official Bazel website -
`https://bazel.build/install`

Recommended way is to install Bazelisk (no need to configure it -
just call it just like you would call Bazel)

On macOS:

```bash
brew install bazelisk
```

On Windows:

```bash
choco install bazelisk
```

On Linux: You can download Bazelisk binary on our Releases page and add it to your PATH manually, which also works on macOS and Windows.

Bazelisk is also published to npm. You may want to install it with

```bash
npm install -g @bazel/bazelisk
```

## Install Vulkan development packages (assumes a package manager like apt, dnf, or pacman is available)

This step is platform-dependent and may vary. The example below is for Ubuntu-like systems.

```bash
sudo apt install libvulkan-dev libglfw3-dev
```

## Generate compile_commands.json

Bazel is supported with plugins in many different IDEs, including
CLion, Visual Studio, VSCode, Eclipse, Emacs and Vim

For VSCode and Sublime Text the preferred way is to use Clangd server
for C/C++ language support. Obviously you want to have code navigation,
auto-completion and refactoring features. For this you need to generate
`compile_commands.json`:

```bash
bazel run @hedron_compile_commands//:refresh_all
```

## Build and test project with Bazel

```bash
bazel test //components/engine:tests
bazel build //components/engine:engine
```

## Code quality checking with Trunk

I use Trunk.io for this - `trunk.io`

To install and run it locally follow official documentation -
`https://docs.trunk.io/check/advanced-setup/cli`

With Bash:

```bash
curl https://get.trunk.io -fsSL | bash -s -- -y
```

With Npm:

```bash
npm install -D @trunkio/launcher
```

Executable name clashes with Rust Cargo's trunk package for WebAssembly
development - `trunk`. If you have this problem, then you need to find
a way to keep both of them in your system. Installation path is different,
so you only need to choose between them. In my case I just renamed Trunk.io
executable to `trunk_code`, and configured my IDE to use custom path for this.

Check code quality:

```bash
trunk check -a
```
