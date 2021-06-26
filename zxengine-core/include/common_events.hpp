#pragma once
#include "event.hpp"
namespace zx
{
	template<typename Sender>
	struct OnFocusEventData : public EventData{
		bool focused;
		Sender* sender;
	};
	template<typename Sender>
	using OnFocusEvent = Event<OnFocusEventData<Sender>>;
	template<typename Sender>
	using OnFocusEventQueue = EventQueue<OnFocusEventData<Sender>>;

	template<typename Sender>
	requires requires(const Sender s) { s.enabled(); }
	struct OnEnableEventData : public EventData {
		[[nodiscard]] OnEnableEventData() = default;

		[[nodiscard]] inline OnEnableEventData(Sender* sender) noexcept
			: sender(sender) {}
		Sender* sender;
		[[nodiscard]] inline bool enabled() const noexcept { return sender->enabled(); }
	};

	template<typename Sender>
	requires requires(const Sender s) { s.enabled(); }
	using OnEnableEvent = Event<OnEnableEventData<Sender>>;

	template<typename Sender>
	requires requires(const Sender s) { s.enabled(); }
	using OnEnableEventQueue = EventQueue<OnEnableEventData<Sender>>;

	template<typename Sender>
	struct OnDisposeEventData : public EventData
	{
		[[nodiscard]] OnDisposeEventData() = default;
		[[nodiscard]] inline OnDisposeEventData(Sender* sender) noexcept
			: sender(sender) {}
		Sender* sender;
	};

	template<typename Sender>
	using OnDisposeEvent = Event<OnDisposeEventData<Sender>>;
	template<typename Sender>
	using OnDisposeEventQueue = EventQueue<OnDisposeEventData<Sender>>;
}