#include <glfw3.h>
#include <iostream>

int main()
{
	if (glfwInit())
	{
		std::cout << "Success\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	system("pause");
	return 0;
}