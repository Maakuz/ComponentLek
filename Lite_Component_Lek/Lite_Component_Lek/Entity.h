#ifndef ENTITY_H
#define ENTITY_H
#include "Mesh.h"
#include <assert.h>
#include <map>

class Entity
{
private:
	std::map<int, Component*> mComponents;

public:
	Entity();
	virtual ~Entity();

	Component* getComponent(int id);
	bool hasComponent(int id);
	void addComponent(Component* component);

};

#endif