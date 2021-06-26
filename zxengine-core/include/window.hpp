#pragma once
#include "system.hpp"
#include "iLayer.hpp"
#include "input_codes.hpp"
#include "event.hpp"
#include "input_events.hpp"
#include "common_events.hpp"

namespace zx
{
	namespace layers
	{
		inline const layer_id window = -500000;
	}
	class window;
	using WindowFocusEventData = OnFocusEventData<window>;
	
	class window : public iSystem
	{
	public:
		inline window() noexcept
			: iSystem(layers::window), pm_NativeWindow(nullptr), pm_ShouldClose(false) {}

		virtual vector2 mousePos() = 0;

		[[nodiscard]] inline void* nativeWindow() const { return pm_NativeWindow; }

		[[nodiscard]] inline auto& onKeyEvent() noexcept { return pm_KeyEvent; }
		[[nodiscard]] inline auto& onKeyPressed() noexcept { return pm_KeyPressedEvent.event; }
		[[nodiscard]] inline auto& onKeyReleased() noexcept { return pm_KeyReleasedEvent.event; }
		[[nodiscard]] inline auto& onMouseButtonPressed() noexcept { return pm_MouseButtonPressedEvent.event; }
		[[nodiscard]] inline auto& onMouseButtonReleased() noexcept { return pm_MouseButtonReleasedEvent.event; }
		[[nodiscard]] inline auto& onMouseMoved() noexcept { return pm_MouseMovedEvent.event; }
		[[nodiscard]] inline auto& onFocus() noexcept { return pm_OnFocusEvent.event; }
		[[nodiscard]] inline auto& onDispose() noexcept { return pm_OnDisposeEvent.event; }
		[[nodiscard]] inline auto& onScroll() noexcept { return pm_ScrollEvent.event; }
		
	protected:
		KeyEvent pm_KeyEvent;
		KeyPressedEventQueue pm_KeyPressedEvent;
		KeyReleasedEventQueue pm_KeyReleasedEvent;

		MouseButtonEventQueue pm_MouseButtonPressedEvent;
		MouseButtonEventQueue pm_MouseButtonReleasedEvent;

		ScrollEventQueue pm_ScrollEvent;

		OnFocusEventQueue<window> pm_OnFocusEvent;
		OnDisposeEventQueue<window> pm_OnDisposeEvent;

		MouseMovedEventQueue pm_MouseMovedEvent;
		virtual bool NativeInitialization() = 0;
		virtual void NativeDispose() = 0;

		void* pm_NativeWindow = nullptr;
		bool pm_ShouldClose = false;

		vector2 pm_PrevMousePos;

		friend class application;
	};

}