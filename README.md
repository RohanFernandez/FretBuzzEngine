# **FretBuzz OpenGL Game Engine**

A game engine made to support 2D and 3D games. 
All libraries are contained within the repository and should run out-of-the-box provided you use Visual Studio 2017, Platform toolset v141.

## **Notes**
1. On building in either of the build conifigurations, the 'Resources' folder (which holds all the assets) is copied to the 'Output' directory using xcopy each time as a Post Build Event.
1. In the *'Debug'* configuration the preprocessor directive *'_IS_DEBUG'* is set. To not use *'_IS_DEBUG'* remove it from 
   *'Configuration Properties' -> 'C/C++' -> 'Preprocessor' -> 'Preprocessor Definitions'*


## **Engine/Game progress build**
[BUILD LINK](https://www.dropbox.com/home/GameDev%20Projects/FretBuzzBuilds/FretBuzzBuilds_20180909)

## **Resources/Libs::**
	*Graphics API 		:: Open GL, GLEW, GLFW
    *Image        		:: FreeImage
	*Audio        		:: irrKlang
	*Math         		:: GLM
	*Physics/Collisions :: Box2D 
	*xml parser 		:: pugixml