# Algorithm-Practice
Algorithm problem set and solutions written in C++

## Environment
`	std::cout << '\n' << "C++ default standard in g++ compiler is: " << __cplusplus << '\n';`
### Windows
Windows 11 Pro 21H2, OS build 22000.1042
```
#include <windows.h>
#include <tchar.h>
#define BUFSIZE MAX_PATH
int main(){
	TCHAR buffer[BUFSIZE];
	DWORD dwRet = GetCurrentDirectory(BUFSIZE, buffer);
	cout << "CWD: "<< buffer << endl;
}
```
**Developed under Visual Studio 2022**
<br>
Access info from `Project Properties > Configuration Properties > C/C++ > General`
  - Windows SDK Version, 10.0 (latest installed version)
  - Platform Toolset, Visual Studio 2022 (v143)
  - C++ Language Standard, ISO C++14 Standard
  - C Language Standard, Legacy MSVC

**Developed under Visual Studio Code**
```
> msys\usr\bin\g++.exe -fdiagnostics-color=always -g SOURCE -o OBJECT
> g++ --version
g++ (GCC) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
> gcc --version
gcc (GCC) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
> g++ -x c++ -E -dM /dev/null | grep -F __cplusplus
#define __cplusplus 201703L
```

### MacOS
Monterey 12.6 
<br>
Darwin MacBook-Air-M2.local 21.6.0 Darwin Kernel Version 21.6.0: Mon Aug 22 20:20:07 PDT 2022; root:xnu-8020.140.49~2/RELEASE_ARM64_T8110 arm64 

**Developed under Visual Studio Code**
```
> /usr/bin/g++ -fdiagnostics-color=always -g SOURCE -o OBJECT -std=c++17
> g++ --version
> gcc --version
Apple clang version 14.0.0 (clang-1400.0.29.102)
Target: arm64-apple-darwin21.6.0
Thread model: posix
InstallerDir: /Library/Developer/CommandLineTools/usr/bin
> g++ -x c++ -E -dM /dev/null | grep -F __cplusplus
#define __cplusplus 199711L
```
## Note
- `error 'iostream' file not found.` Configuration file is not correctly set up in local machine.
- `ssh: connect to host github.com port 22: Operation timed out.` Local network blocked the request from ssh connection
## Acknowledgement
- Classnote is provided by professor Roger Chen who is the instructor of course CSE674\
https://ecs.syracuse.edu/faculty-staff/c-y-roger-chen
- Code writted is based on the topic and requirement of homework