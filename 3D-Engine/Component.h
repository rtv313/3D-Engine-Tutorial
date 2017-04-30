
#ifndef  COMPONENT_H
#define COMPONENT_H
#include "Globals.h"

enum ComponentType
{

};

class GameObject;

class Component
{

public:

	ComponentType type;
	bool active;
	GameObject* my_go;

	Component(GameObject* go):my_go(go)
	{
	}

	virtual ~Component() 
	{
		
	}

	virtual void Enable()
	{
		active = true;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual void Disable()
	{
		active = false;
	}

};

#endif // ! COMPONENT_H