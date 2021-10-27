## Areas

### Build
The project can be built using CMake with the provided CMakeLists.txt.
Alternatively, assuming GCC, running
```console
$> g++ -O3 -Wall -Wextra -pedantic -std=c++17 src/*.cpp -o areas
```
from the root directory should work as well.

It was built and tested with GCC 10.2.0 (from MSYS's MinGW) and MSVC 19.29.30136.0 (Visual Studio 2019).

### Run
To run areas you'll need the 2 input files in this order:
```console
$> areas <file.crd> <file.ebc>
```
Upon successful execution, a file named test.areas will be created in the current directory.
