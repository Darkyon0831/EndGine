#pragma once

namespace EG
{
	class GameObject;
	class Entity;
	
	class IComponent
	{
	public:
		friend class ComponentManager;
		
		IComponent() = default;
		virtual ~IComponent() = default;

		virtual void PreStart() { }
		virtual void Start() { }
		virtual void PostStart() { }

		virtual void PreUpdate() { }
		virtual void Update() { }
		virtual void PostUpdate() { }

		GameObject* GetGameObject() const;

	private:
		Entity* m_pEntity;
	};
}
