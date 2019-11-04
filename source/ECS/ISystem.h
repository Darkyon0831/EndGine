#pragma once

namespace EG
{
	class ISystem
	{
	public:
		ISystem() = default;
		virtual ~ISystem() = default;
		
		virtual void PreStart() { }
		virtual void Start() { }
		virtual void PostStart() { }

		virtual void PreUpdate() { }
		virtual void Update() { }
		virtual void PostUpdate() { }

		virtual void Render() { }
	};
}