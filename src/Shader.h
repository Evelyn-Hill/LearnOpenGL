#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

class Shader {
public: 
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};


