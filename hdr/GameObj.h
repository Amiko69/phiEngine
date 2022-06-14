#pragma once
#include<stdafx.h>


namespace phiE{
	class GameObject;
	class Component {
	public:
		Component();
		virtual ~Component();
		virtual void update() = 0;
		virtual std::string getInfo() = 0;
		
		std::unique_ptr<GameObject> gameObject;

	};
	class Transform: public Component {
		public:
		Transform();
		Transform(Eigen::Vector2i position, Eigen::Vector2f scale, short rotation = 0);
		virtual ~Transform();
		void update();
		inline std::string getInfo() {
			std::stringstream ss;
			ss << "Transform: (" << position.x() << ", " << position.y() << ") ("
				<< scale.x() << ", " << scale.y() << ") " << rotation<<'\n';
			return ss.str();
		}
		
		Eigen::Vector2i position;
		Eigen::Vector2f scale;
		short rotation;
	};
	
	class Sprite : public Component {
	public:
		Sprite();
		//Sprite(std::string texturePath);
		virtual ~Sprite();
		void update();
		inline std::string getInfo() {
			std::stringstream ss;
			ss << "Sprite: " << ' ' << '\n';
			return ss.str();
		}

	};
	
	
	class GameObject{
	public:
		GameObject();
		virtual ~GameObject();
		void addComponent(std::shared_ptr<Component> component);
		void update();
		
		inline std::string getInfo() {
			std::stringstream ss;
			for (auto& component : components) {
				ss << component->getInfo();
			}
			return ss.str();
		}
		
		template<typename T>
		std::shared_ptr<T> getComponent(){
			for(auto component : components){
				if(std::dynamic_pointer_cast<T>(component)) 
					return std::dynamic_pointer_cast<T>(component);
			}
			return nullptr;
		}
		
		std::vector<std::shared_ptr<Component>> components;

	};

	//======================================================

	typedef std::shared_ptr<Component> sharedCompPtr;
}

#define MK_SHRD(type, ...) std::make_shared<type>(__VA_ARGS__)
	
	
