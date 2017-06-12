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
	if (component->getId() == ComponentID::camera)
		assert(this->hasComponent(ComponentID::position));

	if (component->getId() == ComponentID::velocity)
		assert(this->hasComponent(ComponentID::position));

	if (component->getId() == ComponentID::keyboardInput)
		assert(this->hasComponent(ComponentID::velocity));


	this->mComponents[component->getId()] = component;
}
