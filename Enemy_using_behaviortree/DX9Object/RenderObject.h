#pragma once
#include <string>

class RenderObject
{
public:
	RenderObject(std::string ObjName) { meshkey_ = ObjName; }
	~RenderObject() {}

public:
	std::string meshkey_;
	std::string texturekey_;
};