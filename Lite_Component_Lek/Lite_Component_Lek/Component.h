#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentID
{
	camera = 0,
	mesh = 1,
	position = 2,
	velocity = 3,
	keyboardInput = 4,
	transformBuffer = 5,
	directionalLight = 6
};

class Component
{
private:
	int id;
public:
	Component(int id);
	virtual ~Component();

	int getId() const;


};

#endif