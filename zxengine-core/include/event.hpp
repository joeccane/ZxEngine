#pragma once
#include "core.hpp"
#include "iLayer.hpp"
#include "id_counter.hpp"
namespace zx
{
	struct EventData
	{
		bool handled = false;
	};
	
	using subscriber_id = size_t;

	template<std::derived_from<EventData> T>
	class Event
	{
	public:
		struct Callback : public iLayer
		{
			[[nodiscard]] Callback(std::function<void(T&)>& function, size_t id, layer_id layer) noexcept
				: id(id), function(function), iLayer(layer)
			{}
			[[nodiscard]] Callback(std::function<void(T&)>&& function, size_t id, layer_id layer) noexcept
				: id(id), function(function), iLayer(layer)
			{}
			std::function<void(T&)> function;
			size_t id;
		};

		template<typename TFunc>
		requires requires(TFunc f, T data) { {f(data) } -> std::same_as<void>; }
		[[nodiscard]] subscriber_id Subscribe(TFunc& func, layer_id layer = 0) noexcept
		{
			auto id = pm_Counter.get();
			auto it = pm_CallbackList.emplace(id, Callback( func, id, layer ));
			pm_Callbacks.Add(&it.first->second);
			return id;
		}
		template<typename TFunc>
		requires requires(TFunc f, T data) { {f(data) } -> std::same_as<void>; }
		[[nodiscard]] subscriber_id Subscribe(TFunc&& func, layer_id layer = 0) noexcept
		{
			auto id = pm_Counter.get();
			auto it = pm_CallbackList.emplace(id, Callback( func, id, layer ));
			pm_Callbacks.Add(&it.first->second);
			return id;
		}
		[[nodiscard]] subscriber_id Subscribe(auto instance, auto func, layer_id layer = 0) noexcept
		{
			auto id = pm_Counter.get();
			auto invokerFunction = [=](T& data) { return (instance->*func)(data); };
			auto it = pm_CallbackList.emplace(id, Callback(invokerFunction, id, layer));
			pm_Callbacks.Add(&it.first->second);
			return id;
		}

		template<std::derived_from<iLayer> TLayer>
		/*[[nodiscard]] INTERNAL COMPILER ERROR*/ 
		subscriber_id Subscribe(TLayer* instance, auto func) noexcept
		{
			auto id = pm_Counter.get();
			auto invokerFunction = [=](T& data) { return (instance->*func)(data); };
			auto it = pm_CallbackList.emplace(id, Callback(invokerFunction, id, instance->layer()));
			pm_Callbacks.Add(&it.first->second);
			return id;
		}
		bool Unsubscribe(subscriber_id id) noexcept
		{
			if (!pm_CallbackList.contains(id))
				return false;
			pm_Callbacks.Remove(&pm_CallbackList[id]);
			pm_CallbackList.erase(id);
			return true;
		}

		void ChangeLayer(subscriber_id id, layer_id layer) noexcept
		{
			if (!pm_CallbackList.contains(id))
				return;

			pm_CallbackList[id].layer() = layer;
			pm_Callbacks.Sort();
		}

		template<typename TFunc>
		requires requires(TFunc f, T data) { {f(data) } -> std::same_as<void>; }
		[[nodiscard]] inline subscriber_id operator<<(TFunc& f) noexcept
		{
			return Subscribe(f);
		}
		template<typename TFunc>
		requires requires(TFunc f, T data) { {f(data) } -> std::same_as<void>; }
		[[nodiscard]] inline subscriber_id operator<<(TFunc&& f) noexcept
		{
			return Subscribe(f);
		}

		void Invoke(T& value) noexcept
		{
			for (Callback* c : pm_Callbacks)
			{
				c->function(value);
				if (value.handled)
					return;
			}
		}
		inline void InvokeIgnoreHandled(T& value) noexcept
		{
			for (auto& callback : pm_Callbacks)
				callback.function(value);
		}
	private:
		LayerGroup<Callback> pm_Callbacks;
		id_counter<size_t> pm_Counter;
		std::unordered_map<size_t, Callback> pm_CallbackList;

	};

	template<std::derived_from<EventData> T>
	class EventQueue
	{
	public:
		Event<T> event;

		inline void Enqueue(const T& data){
			ps_Queue.emplace(data);
		}
		inline void Enqueue(T&& data) {
			ps_Queue.emplace(std::forward<T>(data));
		}
		inline void InvokeAll(std::function<void(T&)> callback = std::function<void(T&)>())
		{
			while (ps_Queue.size() > 0)
			{
				auto& f = ps_Queue.front();
				event.Invoke(ps_Queue.front());
				if (callback)
					callback(f);
				ps_Queue.pop();
			}
		}
	private:
		std::queue<T> ps_Queue;
	};
}