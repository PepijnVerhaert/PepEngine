#pragma once
class ServiceLocator final
{
public:
	ServiceLocator() = default;
	~ServiceLocator() = default;

	template <typename T>
	T* GetService()
	{
		return nullptr;
	}
};

