#pragma once
#include <string>

class RenderObject
{
public:
	RenderObject() { meshkey_ = "Cube"; }
	~RenderObject() {}

public:
	std::string meshkey_;
	std::string texturekey_;
};