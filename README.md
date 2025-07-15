# Windows Fuzzing Example

This is a simple example C++ project designed for fuzz testing with [Mayhem](https://forallsecure.com).


## Quick Start


**Option: Visual Studio Developer Powershell**
```bash
cmake -G "NMake Makefiles" -B build
cmake --build build
```

This should build x86 (not x64) binaries, and generate mayhem packages.

Run the packages with `mayhem run <package>`

**Option: Visual Studio**: 
  1. Open this as a directory. Visual studio should recognize cmake and set 
	 up everything for you.
  2. To compile, run "Build->Build All".


Then run:
```bash
mayhem package -o mayhem_package out/fuzz_target_<name>.exe
copy testsuite/* mayhem_package/testsuite
mayhem run mayhem_package
```

**Option: cgwin command line**:

```bash
cmake -S . -B build
cmake --build build
```

Then run:
```bash
mayhem package -o mayhem_package_gplusplus out/fuzz_target_gplusplus.exe
copy testsuite/* mayhem_package/testsuite
mayhem run mayhem_package_gplusplus
```

## Fuzzing Support with Mayhem

| Compiler               | Binary       | Sanitizers  | 
|------------------------|--------------|-------------|
| MSVC 2022 (cl.exe v19) x32 | Failing     | Failing    |
| clang 10+ (MSVC)    x32   | Supported     | Failing    |
| gcc 12.4 (cygwin)   x32   | Failing     | Failing    |
| gcc 15.1 (mingw) x64     |  Supported     | N/A. Linking fails    |


**clang8 and cygwin**: cygwin installs clang8, which does not support 
`libfuzzer` or `ASAN`.  To use `libfuzzer` or `ASAN`, you need to install:
    * clang 10+ 
	* built with the `libclang_rt` library.

MSVC will install a supported version of clang, and you can also install
from the [GitHub release page](https://github.com/llvm/llvm-project/releases)

## Windows Behaviors

Windows behaviors are different than Linux. In Linux, `assert` and `abort`
crash with a signal, but in Windows they are silently wrapped.

| Case                            | Linux Behavior         | Windows MSVC Default        | Supported | 
|---------------------------------|------------------------|-----------------------------|-----------|
| `abort()`                       | Raises signal, exits   | Shows dialog, exits code 3  | No        |
| `assert()`                      | Raises SIGABRT         | May no-op in release        | No        |
| `throw std::runtime_error`      | Uncaught → terminate() | Exits silently (code 1/3)   | Yes	     |
| Null pointer dereference        | Crashes                | Crashes                     | Yes       | 
| OOB heap write (with ASAN)      | Detected by ASAN       | Detected by ASAN (Clang)    | No        | 
| `RaiseFailFastException()`      | Not applicable         | Crashes with fast fail      | No        | 

