# **FretBuzz OpenGL Game Engine**

A game engine made to create 2D and 3D games.

## **Notes**
1. To create the solution, run the file FretBuzz->ProjectGenerator.bat. A Visual Studio 2019 solution will be created with the startup project 'Sandbox' as a testing project and the engine project 'FretBuzzFramework' as a reference.
1. On building the project in either of the build conifigurations, the 'Resources' folder (which holds all the assets) is copied to the 'Output' directory of that configuration.

## **Resources/Libs::**
	*Build system		:: Premake 5
	*Graphics API 		:: Open GL, GLEW, GLFW
	*Image        		:: FreeImage
	*Audio        		:: irrKlang
	*Math         		:: GLM
	*Physics/Collisions	:: Box2D 
	*XML parser 		:: pugixml
	*Model loader 		:: Assimp
	*Engine Editor UI 	:: ImGui
	*Logging		:: spdlog
