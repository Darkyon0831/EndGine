#pragma once

namespace EG
{
	class ICompoent
	{
	public:
		ICompoent() = default;
		virtual ~ICompoent() = default;

		virtual void PreStart() { }
		virtual void Start() { }
		virtual void PostStart() { }

		virtual void PreUpdate() { }
		virtual void Update() { }
		virtual void PostUpdate() { }
	};
}