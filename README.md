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

## Dotnet
We can do the same with the dotnet example:
```bash
mayhem package .\out\dotnet_fuzz_target.exe -o .\mayhem_dotnet_package
mayhem run .\mayhem_dotnet_package
```