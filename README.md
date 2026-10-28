# About
Simple Wordle player, written in C.

# Compatability
Needs a C compiler and support for ANSI escape sequences.

Windows 11 supports ANSI escape sequences out-of-the-box.
macOS, Linux, and the BSDs have supported them for decades.
Pretty much everything under the sun has a C compiler.

# Word List
The program uses a modified version of this list: https://gist.github.com/shmookey/b28e342e1b1756c4700f42f17102c2ff
I manually read through it, deleting offensive or potentially offensive words from the list.
I then used AI to double-check I didn't miss anything.

# Compilation

To build this program, you need a C compiler, CMake, and a build tool of choice.
For a build tool, `make` is preinstalled on most *nix systems, and `MSBuild` comes with the Visual Studio install on Windows.
This command *should* work in both Windows *Developer* Powershell and Bash.
`mkdir build ; cd build ; cmake .. ; cmake --build .`