#include <iostream>
#include <spdlog/spdlog.h>

int main() {
	std::cout << "Hello, World!\n" << std::endl;
	spdlog::info("Esto es una prueba de funcionamiento");
	spdlog::error("Esto es un fallo");
}
