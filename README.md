# DYDAMA - DYnamics of DArk MAtter

A simple particle code that came to life while studying the dynamics of dark matter clumps. However it can be used to study various other objects such the planets in the solar system.

To compile the code, `cd` into the directory and type

```bash
make dydama
```
Prerequisite is the GNU compiler `gcc-6`. Make according adjustments to the `Makefile` if you want to use another compiler.

Another requirement is the c-library `<SDL2/SDL.h>`, for real-time graphics.

### Side note

If the code crashes and gives a `bus error: 10`, the non-main pthread stack size might be too small.
MacOS is particularly prone to this problem. Luckily, it is easily bypassed by adding

```bash
export GOMP_STACKSIZE=16384
```
or something equivalent for non-GNU compilers to your `.bash_profile`, `.bashrc`, or some equivalent dotfile.
