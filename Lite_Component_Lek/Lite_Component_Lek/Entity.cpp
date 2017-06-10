#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	for (auto const &key : mComponents) 
	{
		if (key.second)
			delete key.second;
	}
}

Component* Entity::getComponent(int id)
{
	return this->mComponents[id];
}

bool Entity::hasComponent(int id)
{
	if (this->mComponents[id])
		return true;

	return false;
}

void Entity::addComponent(Component* component)
{
	this->mComponents[component->getId()] = component;
}
