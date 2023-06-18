#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:	
	int drawLayer;

public:
	void SetDrawLayer(int newDrawLayer);
	
	int GetDrawLayer();

	virtual void Draw();
};

#endif // !ENTITY_H
