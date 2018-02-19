#pragma once
#include <iostream>
#include "static_obj.h"

class finalf : public static_obj
{
	void show() { std::cout << "."; }
};
