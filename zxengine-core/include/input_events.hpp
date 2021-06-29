#pragma once
#include "event.hpp"
#include "input_codes.hpp"
#include "math.hpp"
namespace zx
{
	enum class buttonAction {
		none,
		pressed,
		released
	};
	struct KeyEventData : public EventData
	{
		KeyEventData() = default;
		[[nodiscard]] inline KeyEventData(zx::key k) noexcept 
			: key(k) {}
		zx::key key;
	};
	struct KeyPressedEventData : public KeyEventData
	{
		KeyPressedEventData() = default;
		[[nodiscard]] inline KeyPressedEventData(zx::key k, bool repeat) noexcept
			: KeyEventData(k), repeat(repeat) {}
		bool repeat;
	};
	struct KeyReleasedEventData : public KeyEventData
	{
		KeyReleasedEventData() = default;
		[[nodiscard]] inline KeyReleasedEventData(zx::key k) noexcept 
			: KeyEventData(k) {}
	};

	struct MouseButtonEventData : public EventData
	{
		MouseButtonEventData() = default;
		[[nodiscard]] inline MouseButtonEventData(mousebutton b) noexcept 
			: button(b), action(buttonAction::none) {}
		mousebutton button;
		buttonAction action;
	};

	using KeyEvent = Event<KeyEventData>;
	using KeyPressedEvent = Event<KeyPressedEventData>;
	using KeyReleasedEvent = Event<KeyReleasedEventData>;

	using MouseButtonEvent = Event<MouseButtonEventData>;

	using KeyEventQueue = EventQueue<KeyEventData>;
	using KeyPressedEventQueue = EventQueue<KeyPressedEventData>;
	using KeyReleasedEventQueue = EventQueue<KeyReleasedEventData>;

	using MouseButtonEventQueue = EventQueue<MouseButtonEventData>;


	struct MouseMovedEventData : public EventData
	{
		MouseMovedEventData() = default;
		inline MouseMovedEventData(vector2 previous, vector2 current) noexcept
			: previousPosition(previous), position(current) {}
		const vector2 previousPosition;
		const vector2 position;

		[[nodiscard]] vector2 delta() const noexcept{ return previousPosition - position; }
	};
	using MouseMovedEvent = Event<MouseMovedEventData>;
	using MouseMovedEventQueue = EventQueue<MouseMovedEventData>;


	struct ScrollEventData : public EventData
	{
		ScrollEventData(const vector2& value) 
			: delta(value) {}
		const vector2 delta;
		float mouseScroll() { return delta.y; }
	};
	using ScrollEvent = Event<ScrollEventData>;
	using ScrollEventQueue = EventQueue<ScrollEventData>;
}