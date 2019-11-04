#include "ECS/Component.h"

namespace EG
{
	class TestComponent : public Component<TestComponent>
	{
	public:
		TestComponent(int test);
		~TestComponent() = default;
		
	private:
		int m_test;
	};
	
}