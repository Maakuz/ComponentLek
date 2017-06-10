#include "Component.h"

Component::Component(int id)
{
	this->id = id;
}

Component::~Component()
{
}

int Component::getId() const
{
	return this->id;
}
