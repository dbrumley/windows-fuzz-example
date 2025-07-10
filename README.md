# Windows Fuzzing Example

This is a simple example C++ project designed for fuzz testing with [Mayhem](https://forallsecure.com).

## Build (MSVC or Clang)

```bash
cmake --preset x64-Debug
```


## Package
```bash
mayhem package .\out\fuzz_target.exe -o mayhem_package
```

## Mayhem It
```bash
mayhem run mayhem_package
```
_