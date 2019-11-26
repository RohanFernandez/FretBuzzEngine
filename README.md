# **FretBuzz OpenGL Game Engine**

A game engine made to support 2D and 3D games.

## **Notes**
1. On building in either of the build conifigurations, the 'Resources' folder (which holds all the assets) is copied to the 'Output' directory using xcopy each time as a Post Build Event.
1. In the *'Debug'* configuration the preprocessor directive *'_IS_DEBUG'* is set. To not use *'_IS_DEBUG'* remove it from 
   *'Configuration Properties' -> 'C/C++' -> 'Preprocessor' -> 'Preprocessor Definitions'*


## **Engine/Game progress build**
[BUILD LINK](https://www.dropbox.com/s/2rbgrtq2f33v41i/FretBuzzEngine_Build.zip?dl=0)

*Controls:*
1. Mouse Left Click : Attack / Fire
1. Mouse Right Click : Pick Weapon / Throw Weapon
1. Movement : W,A,S,D 

## **Resources/Libs::**
	*Graphics API 		:: Open GL, GLEW, GLFW
    *Image        		:: FreeImage
	*Audio        		:: irrKlang
	*Math         		:: GLM
	*Physics/Collisions 	:: Box2D 
	*xml parser 		:: pugixml
	*Model loader 		:: Assimp
