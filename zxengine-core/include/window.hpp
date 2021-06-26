#pragma once
#include "system.hpp"
#include "iLayer.hpp"
namespace zx
{
	namespace layers
	{
		inline const layer_id window = -500000;
	}

	class window : public iSystem
	{
	public:
		inline window() noexcept
			: iSystem(layers::window), pm_NativeWindow(nullptr), pm_ShouldClose(false) {}
		[[nodiscard]] inline void* nativeWindow() const { return pm_NativeWindow; }

	protected:

		virtual bool NativeInitialization() = 0;
		virtual void NativeDispose() = 0;

		void* pm_NativeWindow = nullptr;
		bool pm_ShouldClose = false;

		friend class application;
	};

}