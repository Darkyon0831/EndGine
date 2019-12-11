#pragma once

namespace EG
{
	class IEntity
	{
	public:
		IEntity() = default;
		virtual ~IEntity() = default;

		virtual void PreStart() { }
		virtual void Start() { }
		virtual void PostStart() { }

		virtual void PreUpdate() { }
		virtual void Update() { }
		virtual void PostUpdate() { }
	};
}