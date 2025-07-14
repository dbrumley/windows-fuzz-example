# Windows Fuzzing Example

This is a simple example C++ project designed for fuzz testing with [Mayhem](https://forallsecure.com).


## Quick Start

**Option: Command Line**:

```bash
cmake -S . -B build
cmake --build build
```

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
 

## Fuzzing Support with Mayhem

| Compiler               | Binary       | Sanitizers  | 
|------------------------|--------------|-------------|
| MSVC 2022 (cl.exe v19) | Untested     | Untested    |
| clang 10+ (MSVC)       | Untested     | Untested    |
| gcc 12.4 (cygwin)      | Untested     | Untested    |



**clang8 and cygwin**: cygwin installs clang8, which does not support 
`libfuzzer` or `ASAN`.  To use `libfuzzer` or `ASAN`, you need to install:
    * clang 10+ 
	* built with the `libclang_rt` library.

MSVC will install a supported version of clang, and you can also install
from the [GitHub release page](https://github.com/llvm/llvm-project/releases)

## Windows Behaviors

Windows behaviors are different than Linux. In Linux, `assert` and `abort`
crash with a signal, but in Windows they are silently wrapped.

| Case                            | Linux Behavior         | Windows MSVC Default        | With `crash_config.cpp`         |
|---------------------------------|------------------------|-----------------------------|----------------------------------|
| `abort()`                       | Raises signal, exits   | Shows dialog, exits code 3  | Crashes cleanly (no dialog)      |
| `assert()`                      | Raises SIGABRT         | May no-op in release        | Crashes cleanly (even in release)|
| `throw std::runtime_error`      | Uncaught → terminate() | Exits silently (code 1/3)   | Calls `abort()` via `terminate()`|
| Null pointer dereference        | Crashes                | Crashes                     | Crashes                          |
| OOB heap write (with ASAN)      | Detected by ASAN       | Detected by ASAN (Clang)    | Detected by ASAN (Clang)         |
| `RaiseFailFastException()`      | Not applicable         | Crashes with fast fail      | Crashes with fast fail           |

