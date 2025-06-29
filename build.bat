@echo CACHE: %CACHE%
@echo LIBRARY: %LIBRARY%

rd /q/s "%CACHE%\RBKLib\build-release"
rd /q/s "%CACHE%\RBKLib\build-debug"

cmake -G "MinGW Makefiles" -B %CACHE%/RBKLib/build-release -DCMAKE_INSTALL_PREFIX=%LIBRARY%/RBKLib -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
cmake -G "MinGW Makefiles" -B %CACHE%/RBKLib/build-debug -DCMAKE_INSTALL_PREFIX=%LIBRARY%/RBKLib -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF