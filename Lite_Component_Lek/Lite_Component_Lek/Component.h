#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentID
{
	camera = 0,
	mesh = 1
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