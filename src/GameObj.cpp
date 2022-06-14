#include<stdafx.h>
#include<GameObj.h>


namespace phiE {
	Component::~Component(){}
	Component::Component() { gameObject = nullptr; }
	void Component::update(){}
	

	GameObject::GameObject(){} 
	GameObject::~GameObject(){}
	

	//===============
	void GameObject::addComponent(std::shared_ptr<Component> comp) {
		components.push_back(comp);
		comp->gameObject.reset(this);
	}
	void GameObject::update() {
		for (auto& comp : components) {
			comp->update();
		}
	}

}

namespace phiE {
	
	Transform::Transform():position(0,0), rotation(0), scale(1, 1)
	{}
	Transform::Transform(Eigen::Vector2i position, Eigen::Vector2f scale, short rotation)
		: position(position), scale(scale), rotation(rotation)
	{}	
	Transform::~Transform(){}
	void Transform::update(){}
	Sprite::Sprite(){};
	Sprite::~Sprite(){}
	void Sprite::update(){}
}
