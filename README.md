# GameEngine
 A simple game engine to create AI simulations


SFML info:
Get the SFML-Source code from: https://www.sfml-dev.org/download/sfml/2.5.1/
You have to install the MinGW 7.3.0 64bit compiler and CMake.

Copy the downloaded SFML-folder to this Repo.
Open QT and build SFML using:
File->open file or project, navigate to: SFML-2.5.1/CMakeLists.txt
Select your compiler and change the Build output path to: 
... GameEngine/extern/SFML-2.5.1/bin/Release
... GameEngine/extern/SFML-2.5.1/bin/Debug

Build the debug and release Version.

-----
Also you have to download Box2D: https://github.com/erincatto/box2d
Compile it like SFML, but in the folder: 
... GameEngine/extern/box2d/bin/Release
... GameEngine/extern/box2d/bin/Debug