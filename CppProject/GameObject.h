#pragma once

#include "Defined.h"

#include <string>
//class GameState;
class GameState;

class GameObject {
	static int m_next_id;

protected:
	
	std::string m_name;
	bool m_active = true;

public:

	int m_id = 0;
	class GameState* m_state;
	GameObject(const std::string& name = "");
	virtual void update(float dt) {};
	virtual void draw() {};
	virtual void init() {};
	virtual ~GameObject() {};
	bool isActive() { return m_active; };
	void setActive(bool a) { m_active = a; }
};