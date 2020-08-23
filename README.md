# Libfoxutils

**Libfoxutils** is a utility library written in and for C released under the Apache 2.0 license.

## Features

- Dynamic array (FoxArray).
- Open hash table (FoxMap).
- **Non**-cryptographic hashing functions.
- **Non**-cryptographic pseudo-random number generators and utilities.
- Both static and dynamic versions of library.

## Limitations

- Requires support for [Statement Expressions](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html).

## Build + Installation

### Standard (Library + Headers)

```
$ make
# make install
```

### Library

```
$ make
# make install-symlinks
```

### Library (32-bit)

```
$ make CFLAGS="-Wall -Wextra -O3 -m32" LDFLAGS="-rdynamic -m32"
# make libdir='$(exec_prefix)/lib32' install-symlinks
```

### Headers

```
# make install-headers
```

### Documentation

```
$ make docs
```
