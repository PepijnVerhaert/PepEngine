#pragma once
#include <memory>
#include <vector>

namespace pep
{
	class Observer;
	struct BaseObserverEvent;
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;


		void AddObserver(const std::shared_ptr<Observer>& pObserver);
		void RemoveObserver(const std::shared_ptr<Observer>& pObserver);
	protected:
		void Notify(const std::shared_ptr<BaseObserverEvent>& pEvent);
	private:
		std::vector<std::weak_ptr<Observer>> m_pObservers;
	};
}