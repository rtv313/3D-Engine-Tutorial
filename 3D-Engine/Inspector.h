#ifndef INSPECTOR_H
#define INSPECTOR_H

class GameObject;
class Inspector 
{
public:
	GameObject* gameObject = nullptr;
	Inspector();
	~Inspector();
	void Draw();
};

#endif // !INSPECTOR_H
