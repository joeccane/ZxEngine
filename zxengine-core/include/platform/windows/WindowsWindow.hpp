#include "window.hpp"
namespace zx::platform::windows
{
	class WindowsWindow: public zx::window
	{
	public:
		WindowsWindow()
		{
			stackKey() = "zx glfw window";
		}
		void initialize() override;
		void update() override;
		void exit() override;
		void post_render() override;

	protected:
		bool NativeInitialization() override;
		void NativeDispose() override;

		friend class zx::application;
	};
}