#include "window.hpp"
namespace zx::platform::windows
{
	class WindowsWindow: public zx::window
	{
	public:
		WindowsWindow(){
			stackKey() = "zx glfw window";
		}

		void initialize() override;
		void update() override;
		void late_update() override;
		void exit() override;
		void pre_render() override;
		void post_render() override;

		vector2 mousePos() override;
	protected:
		bool NativeInitialization() override;
		void NativeDispose() override;

		friend class zx::application;
	};
}