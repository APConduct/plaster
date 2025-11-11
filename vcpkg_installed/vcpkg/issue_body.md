Package: glfw3:x64-windows@3.4#1

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.44.35211.0
- CMake Version: 4.1.2
-    vcpkg-tool version: 2025-10-16-71538f2694db93da4668782d094768ba74c45991
    vcpkg-scripts version: 4db164a3fa 2025-11-11 (3 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached glfw-glfw-3.4.tar.gz
-- Cleaning sources at C:/msys64/home/aidan/vcpkg/buildtrees/glfw3/src/3.4-2448ff4533.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/msys64/home/aidan/vcpkg/downloads/glfw-glfw-3.4.tar.gz
-- Using source at C:/msys64/home/aidan/vcpkg/buildtrees/glfw3/src/3.4-2448ff4533.clean
-- Configuring x64-windows
-- Building x64-windows-dbg
CMake Error at scripts/cmake/vcpkg_execute_build_process.cmake:134 (message):
    Command failed: C:/msys64/ucrt64/bin/cmake.exe --build . --config Debug --target install -- -v -j17
    Working Directory: C:/msys64/home/aidan/vcpkg/buildtrees/glfw3/x64-windows-dbg
    See logs for more information:
      C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\install-x64-windows-dbg-out.log

Call Stack (most recent call first):
  C:/msys64/home/aidan/projects/CppPlace/plaster/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_build.cmake:74 (vcpkg_execute_build_process)
  C:/msys64/home/aidan/projects/CppPlace/plaster/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_install.cmake:16 (vcpkg_cmake_build)
  buildtrees/versioning_/versions/glfw3/d4bbd4f27c2ca619f57778985120cddcedadb1cc/portfile.cmake:49 (vcpkg_cmake_install)
  scripts/ports.cmake:206 (include)



```

<details><summary>C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\install-x64-windows-dbg-out.log</summary>

```
Change Dir: 'C:/msys64/home/aidan/vcpkg/buildtrees/glfw3/x64-windows-dbg'

Run Build Command(s): C:/msys64/home/aidan/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v -v -j17 install
[1/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\null_joystick.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\null_joystick.c
[2/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\init.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\init.c
[3/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\null_init.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\null_init.c
[4/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\vulkan.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\vulkan.c
[5/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\egl_context.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\egl_context.c
[6/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\context.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\context.c
[7/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\null_window.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\null_window.c
[8/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_time.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_time.c
[9/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\platform.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\platform.c
[10/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\null_monitor.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\null_monitor.c
[11/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\osmesa_context.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\osmesa_context.c
[12/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\monitor.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\monitor.c
[13/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\input.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\input.c
[14/24] RC C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src\glfw.rc src\CMakeFiles\glfw.dir\glfw.rc.res.d src\CMakeFiles\glfw.dir\glfw.rc.res "Note: including file: " "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe" "C:\PROGRA~2\Windows Kits\10\bin\10.0.22000.0\x64\rc.exe" -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src -c65001 /DWIN32 -D_DEBUG /fo src\CMakeFiles\glfw.dir\glfw.rc.res C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src\glfw.rc
FAILED: [code=1] src/CMakeFiles/glfw.dir/glfw.rc.res 
RC C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src\glfw.rc src\CMakeFiles\glfw.dir\glfw.rc.res.d src\CMakeFiles\glfw.dir\glfw.rc.res "Note: including file: " "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe" "C:\PROGRA~2\Windows Kits\10\bin\10.0.22000.0\x64\rc.exe" -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -I C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src -c65001 /DWIN32 -D_DEBUG /fo src\CMakeFiles\glfw.dir\glfw.rc.res C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src\glfw.rc
Microsoft (R) Windows (R) Resource Compiler Version 10.0.10011.16384
Copyright (C) Microsoft Corporation.  All rights reserved.

fatal error RC1107: invalid usage; use RC /? for Help
[15/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_thread.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_thread.c
[16/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\window.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\window.c
[17/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_init.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_init.c
[18/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_module.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_module.c
[19/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_joystick.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_joystick.c
[20/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_monitor.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_monitor.c
[21/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\wgl_context.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\wgl_context.c
[22/24] "C:\PROGRA~1\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"   -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_GLFW_BUILD_DLL -D_GLFW_WIN32 -D_UNICODE -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\include -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src -IC:\msys64\home\aidan\vcpkg\buildtrees\glfw3\x64-windows-dbg\src /nologo /DWIN32 /D_WINDOWS /utf-8 /MP  /MDd /Z7 /Ob0 /Od /RTC1  -MDd /W3 /showIncludes /Fosrc\CMakeFiles\glfw.dir\win32_window.c.obj /Fdsrc\CMakeFiles\glfw.dir\ /FS -c C:\msys64\home\aidan\vcpkg\buildtrees\glfw3\src\3.4-2448ff4533.clean\src\win32_window.c
ninja: build stopped: subcommand failed.
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "veldgui",
  "version": "0.1.0",
  "description": "VeldGUI - A lightweight, cross-platform hybrid-mode GUI library",
  "dependencies": [
    "glfw3",
    {
      "name": "bgfx",
      "features": [
        "multithreaded"
      ]
    },
    "lua",
    "glm",
    {
      "name": "raylib",
      "features": [
        "audio"
      ]
    }
  ],
  "builtin-baseline": "4db164a3fa24910f1a13f21348e2510eb1f78605"
}

```
</details>
