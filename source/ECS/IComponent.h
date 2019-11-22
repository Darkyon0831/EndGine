#pragma once

namespace EG
{
	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;

		virtual void PreStart() { }
		virtual void Start() { }
		virtual void PostStart() { }

		virtual void PreUpdate() { }
		virtual void Update() { }
		virtual void PostUpdate() { }
	};
}