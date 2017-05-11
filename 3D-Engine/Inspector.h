#ifndef INSPECTOR_H
#define INSPECTOR_H

class GameObject;
class Inspector
{
public:
	
	GameObject* gameObjectActual = nullptr;
	Inspector();
	~Inspector();
	void Draw();
	void ChangeObject(GameObject * const newGameObject);

};

#endif // !INSPECTOR_H
