#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:	
	
	float vertices[2];

	int drawLayer;

public:
	void SetDrawLayer(int newDrawLayer);
	
	int GetDrawLayer();

	virtual void Draw() = 0;
};

#endif // !ENTITY_H