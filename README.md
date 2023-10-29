# brainduck 🧠🦆

**brainduck** is a [brainfuck](https://esolangs.org/wiki/Brainfuck) interpreter. brainfuck is an esoteric programming
language that features only eight commands that control a single
pointer to big or infinite array of bytes. There is no official
specification for brainfuck, but brainduck is based on
[brain-lang](https://github.com/brain-lang)'s specification,
which can be found
[here](https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md).

Many implementations of brainfuck create a long array in which
the memory pointer can wrap around. However, by default,
brainduck represents memory as an array that arbitrarily grows
in each side. This allows brainfuck to be closer to being
[Turing-complete](https://en.wikipedia.org/wiki/Turing_completeness).
As some brainfuck programs require the memory pointer to wrap
around memory to work, the circular implementation is left as
an option.

## Compilation

To compile brainfuck, clone this repository and simply run:

```bash
make
```

If you don't want to use make, you can compile it like this:

```bash
g++ src/Configuration.cpp src/Interpreter.cpp src/Memory.cpp src/SourceFile.cpp src/main.cpp -o brainduck -ansi -pedantic -Wall -std=c++11 -O3
```

## Usage

After compiling, you can run a brainfuck program, say
`hello-world.bf`, like this:

```
./brainduck hello-world.bf
```

You can also pass options to the interpreter, as described in
the next section.

## Command line options

When executing brainduck, you can pass some options to configure
the interpreter's behavior. These are:

| Option                   | Aliases                          | Possible values            | Default                                                                    | Definition
|--------------------------|----------------------------------|----------------------------|----------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `--memory-type`          | `--mt`                           | `expanding`, `circular`    | `expanding`                                                                | Defines the memory implementation to be used. <ul><li>`expanding`: Use the arbitrarily exapanding memory implementation.</li><li>`circular`: Use the circular static memory implementation.</li></ul> |
| `--initial-memory-size`  | `--memory-size`, `--ims`, `--ms` | non-zero unsigned integer  | `1024` for `--memory-type expanding`, `30000` for `--memory-type circular` | Defines the number of bytes the memory has at the start of the program. If memory type is circular, the size stays the same during execution.                                                         |
| `--memory-growth-factor` | `--mgf`                          | real number greater than 1 | `1.5F`	                                                                | Defines the memory size multiplier used to expand the memory array when needed. Only applicable when memory type is expanding.                                                                        |
