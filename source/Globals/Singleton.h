#pragma once

namespace EG
{
	template <typename T>
	class Singleton
	{
	public:
		static void Initialize();
		static void Uninitialized();

		static T* GetInstancePtr();
		static T& GetInstance();

	private:
		static T* m_pInstance;
	};

	template <typename T>
	T* Singleton<T>::m_pInstance = nullptr;

	template <typename T>
	void Singleton<T>::Initialize()
	{
		m_pInstance = new T();
	}

	template <typename T>
	void Singleton<T>::Uninitialized()
	{
		delete m_pInstance;
	}

	template <typename T>
	T* Singleton<T>::GetInstancePtr()
	{
		return m_pInstance;
	}

	template <typename T>
	T& Singleton<T>::GetInstance()
	{
		return *m_pInstance;
	}
}
