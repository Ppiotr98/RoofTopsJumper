# RoofTopsJumper
My first simple 3D game

1. Create empty VS project.
2. Copy downloaded files.
3. Include dirs:
    Dependencies\glew-2.1.0\include
    Dependencies\GLFW\include
    src
    src\vendor
4. Lib dirs:
    Dependencies\glew-2.1.0\lib\Release\Win32
    Dependencies\GLFW\lib-vc2019
5. Additional dependencies:
    glew32s.lib;
    glfw3.lib;
    kernel32.lib;
    user32.lib;
    gdi32.lib;
    winspool.lib;
    comdlg32.lib;
    advapi32.lib;
    shell32.lib;
    ole32.lib;
    oleaut32.lib;
    uuid.lib;
    odbc32.lib;
    odbccp32.lib;
    opengl32.lib
6. Add preprocessor definition:
    GLEW_STATIC
7. Include in proj src, but from vendor only stb_image
