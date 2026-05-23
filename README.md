# Genetic Algorithm

A small C++ implementation of a binary-encoded genetic algorithm for optimizing a single-variable fitness function. The project reads its configuration from a text file, evaluates expressions with TinyExpr, and supports roulette selection with single-point or two-point crossover.

## Features

- Binary chromosome representation.
- Single-variable fitness functions using `x`.
- Configurable population size, precision, search range, crossover strategy, and number of generations.
- Roulette-wheel selection that also works when fitness values are negative.
- Reproducible runs with an optional random seed.
- Simple `Makefile` build.

## Requirements

- A C++17 compiler such as `g++`.
- A C99 compiler such as `gcc`.
- `make`.

## Build

```bash
make
```

The executable is created at:

```bash
build/ag
```

To remove build artifacts:

```bash
make clean
```

## Usage

Run the default example:

```bash
make run
```

Run the executable directly:

```bash
build/ag input/hojadecalculo.txt --generations 4
```

Use a fixed seed for reproducible output:

```bash
build/ag input/hojadecalculo.txt --generations 10 --seed 42
```

Show CLI help:

```bash
build/ag --help
```

## Input File Format

The input file must contain 9 non-empty lines:

```text
Population size
Number of variables
Variable name
Decimal precision
Fitness function
Range as: min max
Crossover type
Selection type
Crossover point(s)
```

Example:

```text
4
1
x
1
x^2
0 31
single-point
roulette
3
```

For `single-point`, the last line contains one crossover point. For `two-point`, it contains two points:

```text
6 14
```

## Supported Options

- Variable support: exactly one variable named `x`.
- Selection: `roulette`.
- Crossover: `single-point` or `two-point`.
- Fitness functions: any expression supported by TinyExpr, such as `x^2`, `sin(x)`, `cos(x)`, `sqrt(x)`, and arithmetic operators.

## Project Layout

```text
lib/      Public headers and TinyExpr header
src/      C++ implementation and TinyExpr C source
input/    Example configuration files and reference material
Makefile  Build, run, and clean targets
```

## Notes

The current implementation maximizes the fitness function. If you need minimization, transform the fitness function before passing it to the program, for example by negating the expression or using an inverse score.
