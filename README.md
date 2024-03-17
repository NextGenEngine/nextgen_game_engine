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

## Install latest LLVM toolchain for best developer experience

I'm developing using LLVM/Cland. Build controlled with Bazel, and toolchain
is configured there separately. But for IDE support for linting, cleanup code
suggestions, warnings and autoformatting I'm using LLVM/Clang:
clangd, clang-tidy, ... etc.

Stable releases of Ubuntu (and probably other distributions) and also even
IntelliJ Idea are not shipped with latest versions of LLVM.

Here are the steps to install latest version of toolchain on Ubuntu 22.04 Jammy
for the best developer experience. For other distributions check official
LLVM documentation:

`https://apt.llvm.org/` - Debian based

`https://llvm.org/docs/index.html` - Documentation

### LLVM toolchain on Ubuntu 22.04

Check versions:

```bash
clangd --version
clang-tidy --version
```

Remove your existing toolchain. It is optional step. If you do not remove
default Ubuntu distribution toolchain, then after installing new one,
you need to configure alternatives:

```bash
sudo apt-get install clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python3-clang
sudo apt-get purge clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python3-clang
sudo apt autoremove
```

Add LLVM Official APT repository and install toolchain:

```bash
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo gpg --dearmor -o /usr/share/keyrings/llvm-archive-keyring.gpg

echo -e "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] https://apt.llvm.org/jammy/ llvm-toolchain-jammy main\ndeb-src [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy main" | sudo tee /etc/apt/sources.list.d/llvm.list

sudo apt update

sudo apt install clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld  llvm-dev llvm-runtime llvm python3-clang

Bug:

sudo apt-get install lldb-19 <use latest version here>
```

I had problem installing lldb-19, so in my case I solved it installing
'python3-lldb-19' and `lldb-19` separately with apt commands (you can see them
in commands list above). Maybe you are lucky and in your case you can just add
`lldb` to the list of other packages and it will be installed without issues.

Configure alternatives (in case you do not remove default toolchain):

```bash
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-<version> 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-<version> 100
sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-<version> 100
... probably more alternaives to setup here
```

Check versions:

```bash
clangd --version
clang-tidy --version
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

## Merge Queue

Use Trunk.io Merge Queue, when working in large teams (10 and more engineers):

`https://docs.trunk.io/merge/set-up-trunk-merge`

`https://docs.trunk.io/merge/set-up-trunk-merge/merge-+-bazel`

## IDEs recommendations

Sublime Text:

- auto-save
- BazelSyntax
- Gitignored File Excluder
- SublimeLinter
- SublimeLinter-contrib-clang-tidy
- LSP
- LSP-clangd
- LSP-cspell

VSCode:

- clangd (disable Microsoft C/C++ extension)
- clang-tidy
- bazel
- trunk
- ... list is long, I'm specifying here mandatory ones
