# Libfoxutils

**Libfoxutils** is a utility library written in and for C released under the Apache 2.0 license.

## Features

- Dynamic array (FoxArray).
- Open hash table (FoxMap).
- **Non**-cryptographic hashing functions.
- Both static and dynamic versions of library.

## Build + Installation

### Standard (Library + Headers)

```bash
$ make
# make install
```

### Library

```bash
$ make
# make install-symlinks
```

### Library (32-bit)

```bash
$ make CFLAGS="-Wall -Wextra -O3 -m32 -fno-stack-protector" LDFLAGS="--export-dynamic -m elf_i386"
# make libdir='$(exec_prefix)/lib32' install-symlinks
```

### Headers

```bash
# make install-headers
```

### Documentation

```bash
$ make docs
```
