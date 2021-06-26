#pragma once
#include <string_view>
namespace zx
{
	enum class inputcode_type : unsigned char {
		none,
		key,
		mouse
	};
	struct inputcode
	{
		constexpr inputcode(inputcode_type type, size_t value) 
			: type(type), value(value) {}
		inputcode_type type;
		size_t value;
		virtual const std::string_view toString() const = 0;
	};
	struct inputcode_key : public inputcode
	{
		constexpr inputcode_key() : inputcode(inputcode_type::key, 0)
		{

		}
		inputcode_key(size_t value) : inputcode(inputcode_type::key, value) {
			if (!ps_FromValueMap.contains(value))
				ps_FromValueMap[value] = this;
		}
	private:
		inline static std::unordered_map<size_t, inputcode_key*> ps_FromValueMap;

		friend struct key;
	};
	struct inputcode_mouse_button : public inputcode
	{
		constexpr inputcode_mouse_button() : inputcode(inputcode_type::mouse, 0) {}

		inputcode_mouse_button(size_t vlaue) : inputcode(inputcode_type::mouse, value) {
			if (!ps_FromValueMap.contains(value))
				ps_FromValueMap[value] = this;
		}

	private:
		inline static std::unordered_map<size_t, inputcode_mouse_button*> ps_FromValueMap;

		friend struct mousebutton;
	};

#define ZX_KEYCODE_DETAIL(NAME, TYPE, VALUE, STRINGVALUE)\
	struct inputcode_type_##NAME : public inputcode_key {\
	inputcode_type_##NAME()\
		: inputcode_key(VALUE) {}\
	constexpr const std::string_view toString() const override { return STRINGVALUE; }\
	};\
	inline const inputcode_type_##NAME NAME##Value = inputcode_type_##NAME()\


	namespace keycode::detail
	{
		ZX_KEYCODE_DETAIL(none, key, 0, "none");
		ZX_KEYCODE_DETAIL(space, key, 32, "space");
		ZX_KEYCODE_DETAIL(apostrophe, key, 39, "\'");
		ZX_KEYCODE_DETAIL(comma, key, 44, ",");
		ZX_KEYCODE_DETAIL(minus, key, 45, "-");
		ZX_KEYCODE_DETAIL(period, key, 46, ".");
		ZX_KEYCODE_DETAIL(slash, key, 47, "/");
		ZX_KEYCODE_DETAIL(zero, key, 48, "0");
		ZX_KEYCODE_DETAIL(one, key, 49, "1");
		ZX_KEYCODE_DETAIL(two, key, 50, "2");
		ZX_KEYCODE_DETAIL(three, key, 51, "3");
		ZX_KEYCODE_DETAIL(four, key, 52, "4");
		ZX_KEYCODE_DETAIL(five, key, 53, "5");
		ZX_KEYCODE_DETAIL(six, key, 54, "6");
		ZX_KEYCODE_DETAIL(seven, key, 55, "7");
		ZX_KEYCODE_DETAIL(eight, key, 56, "8");
		ZX_KEYCODE_DETAIL(nine, key, 57, "9");
		ZX_KEYCODE_DETAIL(semicolon, key, 59, ";");
		ZX_KEYCODE_DETAIL(equal, key, 61, "=");
		ZX_KEYCODE_DETAIL(a, key, 65, "a");
		ZX_KEYCODE_DETAIL(b, key, 66, "b");
		ZX_KEYCODE_DETAIL(c, key, 67, "c");
		ZX_KEYCODE_DETAIL(d, key, 68, "d");
		ZX_KEYCODE_DETAIL(e, key, 69, "e");
		ZX_KEYCODE_DETAIL(f, key, 70, "f");
		ZX_KEYCODE_DETAIL(g, key, 71, "g");
		ZX_KEYCODE_DETAIL(h, key, 72, "h");
		ZX_KEYCODE_DETAIL(i, key, 73, "i");
		ZX_KEYCODE_DETAIL(j, key, 74, "j");
		ZX_KEYCODE_DETAIL(k, key, 75, "k");
		ZX_KEYCODE_DETAIL(l, key, 76, "l");
		ZX_KEYCODE_DETAIL(m, key, 77, "m");
		ZX_KEYCODE_DETAIL(n, key, 78, "n");
		ZX_KEYCODE_DETAIL(o, key, 79, "o");
		ZX_KEYCODE_DETAIL(p, key, 80, "p");
		ZX_KEYCODE_DETAIL(q, key, 81, "q");
		ZX_KEYCODE_DETAIL(r, key, 82, "r");
		ZX_KEYCODE_DETAIL(s, key, 83, "s");
		ZX_KEYCODE_DETAIL(t, key, 84, "t");
		ZX_KEYCODE_DETAIL(u, key, 85, "u");
		ZX_KEYCODE_DETAIL(v, key, 86, "v");
		ZX_KEYCODE_DETAIL(w, key, 87, "w");
		ZX_KEYCODE_DETAIL(x, key, 88, "x");
		ZX_KEYCODE_DETAIL(y, key, 89, "y");
		ZX_KEYCODE_DETAIL(z, key, 90, "z");
		ZX_KEYCODE_DETAIL(leftBracket, key, 91, "[");
		ZX_KEYCODE_DETAIL(backslash, key, 92, "\\");
		ZX_KEYCODE_DETAIL(rightBracket, key, 93, "]");
		ZX_KEYCODE_DETAIL(graveAccent, key, 96, "`");
		ZX_KEYCODE_DETAIL(world1, key, 161, "world1");
		ZX_KEYCODE_DETAIL(world2, key, 162, "world2");
		ZX_KEYCODE_DETAIL(esc, key, 256, "escape");
		ZX_KEYCODE_DETAIL(enter, key, 257, "enter");
		ZX_KEYCODE_DETAIL(tab, key, 258, "tab");
		ZX_KEYCODE_DETAIL(backspace, key, 259, "backspace");
		ZX_KEYCODE_DETAIL(insert, key, 260, "insert");
		ZX_KEYCODE_DETAIL(del, key, 261, "delete");
		ZX_KEYCODE_DETAIL(rightArrow, key, 262, "right arrow");
		ZX_KEYCODE_DETAIL(leftArrow, key, 263, "left arrow");
		ZX_KEYCODE_DETAIL(downArrow, key, 264, "downArrow");
		ZX_KEYCODE_DETAIL(upArrow, key, 265, "up arrow");
		ZX_KEYCODE_DETAIL(pageUp, key, 266, "page up");
		ZX_KEYCODE_DETAIL(pageDown, key, 267, "page down");
		ZX_KEYCODE_DETAIL(home, key, 268, "home");
		ZX_KEYCODE_DETAIL(end, key, 269, "end");
		ZX_KEYCODE_DETAIL(capsLock, key, 280, "caps lock");
		ZX_KEYCODE_DETAIL(scrollLock, key, 281, "scroll lock");
		ZX_KEYCODE_DETAIL(numLock, key, 282, "number lock");
		ZX_KEYCODE_DETAIL(printScreen, key, 283, "print screen");
		ZX_KEYCODE_DETAIL(pause, key, 284, "pause");
		ZX_KEYCODE_DETAIL(f1, key, 290, "F1");
		ZX_KEYCODE_DETAIL(f2, key, 291, "F2");
		ZX_KEYCODE_DETAIL(f3, key, 292, "F3");
		ZX_KEYCODE_DETAIL(f4, key, 293, "F4");
		ZX_KEYCODE_DETAIL(f5, key, 294, "F5");
		ZX_KEYCODE_DETAIL(f6, key, 295, "F6");
		ZX_KEYCODE_DETAIL(f7, key, 296, "F7");
		ZX_KEYCODE_DETAIL(f8, key, 297, "F8");
		ZX_KEYCODE_DETAIL(f9, key, 298, "F9");
		ZX_KEYCODE_DETAIL(f10, key, 299, "F10");
		ZX_KEYCODE_DETAIL(f11, key, 300, "F11");
		ZX_KEYCODE_DETAIL(f12, key, 301, "F12");
		ZX_KEYCODE_DETAIL(f13, key, 302, "F13");
		ZX_KEYCODE_DETAIL(f14, key, 303, "F14");
		ZX_KEYCODE_DETAIL(f15, key, 304, "F15");
		ZX_KEYCODE_DETAIL(f16, key, 305, "F16");
		ZX_KEYCODE_DETAIL(f17, key, 306, "F17");
		ZX_KEYCODE_DETAIL(f18, key, 307, "F18");
		ZX_KEYCODE_DETAIL(f19, key, 308, "F19");
		ZX_KEYCODE_DETAIL(f20, key, 309, "F20");
		ZX_KEYCODE_DETAIL(f21, key, 310, "F21");
		ZX_KEYCODE_DETAIL(f22, key, 311, "F22");
		ZX_KEYCODE_DETAIL(f23, key, 312, "F23");
		ZX_KEYCODE_DETAIL(f24, key, 313, "F24");
		ZX_KEYCODE_DETAIL(f25, key, 314, "F25");
		ZX_KEYCODE_DETAIL(kp0, key, 320, "keypad 0");
		ZX_KEYCODE_DETAIL(kp1, key, 321, "keypad 1");
		ZX_KEYCODE_DETAIL(kp2, key, 322, "keypad 2");
		ZX_KEYCODE_DETAIL(kp3, key, 323, "keypad 3");
		ZX_KEYCODE_DETAIL(kp4, key, 324, "keypad 4");
		ZX_KEYCODE_DETAIL(kp5, key, 325, "keypad 5");
		ZX_KEYCODE_DETAIL(kp6, key, 326, "keypad 6");
		ZX_KEYCODE_DETAIL(kp7, key, 327, "keypad 7");
		ZX_KEYCODE_DETAIL(kp8, key, 328, "keypad 8");
		ZX_KEYCODE_DETAIL(kp9, key, 329, "keypad 9");
		ZX_KEYCODE_DETAIL(kpDecimal, key, 330, "keypad .");
		ZX_KEYCODE_DETAIL(kpDivide, key, 331, "keypad /");
		ZX_KEYCODE_DETAIL(kpMultiply, key, 332, "keypad *");
		ZX_KEYCODE_DETAIL(kpSubtract, key, 333, "keypad -");
		ZX_KEYCODE_DETAIL(kpAdd, key, 334, "keypad +");
		ZX_KEYCODE_DETAIL(kpEnter, key, 335, "keypad enter");
		ZX_KEYCODE_DETAIL(kpEqual, key, 336, "keypad equal");
		ZX_KEYCODE_DETAIL(leftShift, key, 340, "left shift");
		ZX_KEYCODE_DETAIL(leftControl, key, 341, "left control");
		ZX_KEYCODE_DETAIL(leftAlt, key, 342, "left alt");
		ZX_KEYCODE_DETAIL(leftSuper, key, 343, "left super");
		ZX_KEYCODE_DETAIL(rightShift, key, 344, "right shift");
		ZX_KEYCODE_DETAIL(rightControl, key, 345, "right control");
		ZX_KEYCODE_DETAIL(rightAlt, key, 346, "right alt");
		ZX_KEYCODE_DETAIL(rightSuper, key, 347, "right super");
		ZX_KEYCODE_DETAIL(menu, key, 348, "menu");
	}

#define ZX_KEYCODE_DEF(NAME) inline static const inputcode_key& NAME = keycode::detail::NAME##Value;

	struct key
	{
		key() : code(&none) {}
		key(const inputcode_key& code) : code(&code)
		{
			
		}
		const std::string_view toString() const { return code->toString(); }
		const inputcode_key* code;
		[[nodiscard]] inline bool operator==(const key& other) const noexcept { return code->value == other.code->value; }
		[[nodiscard]] inline bool operator!=(const key& other) const noexcept { return code->value == other.code->value; }
		inline static key Get(size_t value) { return *inputcode_key::ps_FromValueMap[value]; }
		ZX_KEYCODE_DEF(none);
		ZX_KEYCODE_DEF(space);
		ZX_KEYCODE_DEF(apostrophe);
		ZX_KEYCODE_DEF(comma);
		ZX_KEYCODE_DEF(minus);
		ZX_KEYCODE_DEF(period);
		ZX_KEYCODE_DEF(slash);
		ZX_KEYCODE_DEF(zero);
		ZX_KEYCODE_DEF(one);
		ZX_KEYCODE_DEF(two);
		ZX_KEYCODE_DEF(three);
		ZX_KEYCODE_DEF(four);
		ZX_KEYCODE_DEF(five);
		ZX_KEYCODE_DEF(six);
		ZX_KEYCODE_DEF(seven);
		ZX_KEYCODE_DEF(eight);
		ZX_KEYCODE_DEF(nine);
		ZX_KEYCODE_DEF(semicolon);
		ZX_KEYCODE_DEF(equal);
		ZX_KEYCODE_DEF(a);
		ZX_KEYCODE_DEF(b);
		ZX_KEYCODE_DEF(c);
		ZX_KEYCODE_DEF(d);
		ZX_KEYCODE_DEF(e);
		ZX_KEYCODE_DEF(f);
		ZX_KEYCODE_DEF(g);
		ZX_KEYCODE_DEF(h);
		ZX_KEYCODE_DEF(i);
		ZX_KEYCODE_DEF(j);
		ZX_KEYCODE_DEF(k);
		ZX_KEYCODE_DEF(l);
		ZX_KEYCODE_DEF(m);
		ZX_KEYCODE_DEF(n);
		ZX_KEYCODE_DEF(o);
		ZX_KEYCODE_DEF(p);
		ZX_KEYCODE_DEF(q);
		ZX_KEYCODE_DEF(r);
		ZX_KEYCODE_DEF(s);
		ZX_KEYCODE_DEF(t);
		ZX_KEYCODE_DEF(u);
		ZX_KEYCODE_DEF(v);
		ZX_KEYCODE_DEF(w);
		ZX_KEYCODE_DEF(x);
		ZX_KEYCODE_DEF(y);
		ZX_KEYCODE_DEF(z);
		ZX_KEYCODE_DEF(leftBracket);
		ZX_KEYCODE_DEF(backslash);
		ZX_KEYCODE_DEF(rightBracket);
		ZX_KEYCODE_DEF(graveAccent);
		ZX_KEYCODE_DEF(world1);
		ZX_KEYCODE_DEF(world2);
		ZX_KEYCODE_DEF(esc);
		ZX_KEYCODE_DEF(tab);
		ZX_KEYCODE_DEF(backspace);
		ZX_KEYCODE_DEF(insert);
		ZX_KEYCODE_DEF(del);
		ZX_KEYCODE_DEF(rightArrow);
		ZX_KEYCODE_DEF(leftArrow);
		ZX_KEYCODE_DEF(downArrow);
		ZX_KEYCODE_DEF(upArrow);
		ZX_KEYCODE_DEF(pageUp);
		ZX_KEYCODE_DEF(pageDown);
		ZX_KEYCODE_DEF(home);
		ZX_KEYCODE_DEF(end);
		ZX_KEYCODE_DEF(capsLock);
		ZX_KEYCODE_DEF(scrollLock);
		ZX_KEYCODE_DEF(numLock);
		ZX_KEYCODE_DEF(printScreen);
		ZX_KEYCODE_DEF(pause);
		ZX_KEYCODE_DEF(f1);
		ZX_KEYCODE_DEF(f2);
		ZX_KEYCODE_DEF(f3);
		ZX_KEYCODE_DEF(f4);
		ZX_KEYCODE_DEF(f5);
		ZX_KEYCODE_DEF(f6);
		ZX_KEYCODE_DEF(f7);
		ZX_KEYCODE_DEF(f8);
		ZX_KEYCODE_DEF(f9);
		ZX_KEYCODE_DEF(f10);
		ZX_KEYCODE_DEF(f11);
		ZX_KEYCODE_DEF(f12);
		ZX_KEYCODE_DEF(f13);
		ZX_KEYCODE_DEF(f14);
		ZX_KEYCODE_DEF(f15);
		ZX_KEYCODE_DEF(f16);
		ZX_KEYCODE_DEF(f17);
		ZX_KEYCODE_DEF(f18);
		ZX_KEYCODE_DEF(f19);
		ZX_KEYCODE_DEF(f20);
		ZX_KEYCODE_DEF(f21);
		ZX_KEYCODE_DEF(f22);
		ZX_KEYCODE_DEF(f23);
		ZX_KEYCODE_DEF(f24);
		ZX_KEYCODE_DEF(f25);
		ZX_KEYCODE_DEF(kp0);
		ZX_KEYCODE_DEF(kp1);
		ZX_KEYCODE_DEF(kp2);
		ZX_KEYCODE_DEF(kp3);
		ZX_KEYCODE_DEF(kp4);
		ZX_KEYCODE_DEF(kp5);
		ZX_KEYCODE_DEF(kp6);
		ZX_KEYCODE_DEF(kp7);
		ZX_KEYCODE_DEF(kp8);
		ZX_KEYCODE_DEF(kp9);
		ZX_KEYCODE_DEF(kpDecimal);
		ZX_KEYCODE_DEF(kpDivide);
		ZX_KEYCODE_DEF(kpMultiply);
		ZX_KEYCODE_DEF(kpSubtract);
		ZX_KEYCODE_DEF(kpAdd);
		ZX_KEYCODE_DEF(kpEnter);
		ZX_KEYCODE_DEF(kpEqual);
		ZX_KEYCODE_DEF(leftShift);
		ZX_KEYCODE_DEF(leftControl);
		ZX_KEYCODE_DEF(leftAlt);
		ZX_KEYCODE_DEF(leftSuper);
		ZX_KEYCODE_DEF(rightShift);
		ZX_KEYCODE_DEF(rightControl);
		ZX_KEYCODE_DEF(rightAlt);
		ZX_KEYCODE_DEF(rightSuper);
		ZX_KEYCODE_DEF(menu);

	
	};


#define ZX_MOUSEBUTTON_DETAIL(NAME, VALUE, STRINGVALUE)\
	struct inputcode_type_##NAME : public inputcode_mouse_button {\
	inputcode_type_##NAME()\
		: inputcode_mouse_button(VALUE) {}\
	constexpr const std::string_view toString() const override { return STRINGVALUE; }\
	};\
	inline const inputcode_type_##NAME NAME##Value = inputcode_type_##NAME()\

	namespace mousebuttoncode::detail
	{
		ZX_MOUSEBUTTON_DETAIL(none, 0, "left mouse button");
		ZX_MOUSEBUTTON_DETAIL(left, 1, "left mouse button");
		ZX_MOUSEBUTTON_DETAIL(right, 2, "right mouse button");
		ZX_MOUSEBUTTON_DETAIL(middle, 3, "middle mouse button");
		ZX_MOUSEBUTTON_DETAIL(b4, 4, "mouse button 4");
		ZX_MOUSEBUTTON_DETAIL(b5, 5, "mouse button 5");
		ZX_MOUSEBUTTON_DETAIL(b6, 6, "mouse button 6");
		ZX_MOUSEBUTTON_DETAIL(b7, 7, "mouse button 7");
		ZX_MOUSEBUTTON_DETAIL(b8, 8, "mouse button 8");
	}

#define ZX_MOUSEBUTTON_DEF(NAME) inline static const inputcode_mouse_button& NAME = mousebuttoncode::detail::NAME##Value;
	
	struct mousebutton
	{
		mousebutton() : code(&none) {}
		mousebutton(const inputcode_mouse_button& code) : code(&code)
		{

		}
		const std::string_view toString() const { return code->toString(); }
		const inputcode_mouse_button* code;
		[[nodiscard]] inline bool operator==(const mousebutton& other) const noexcept { return code->value == other.code->value; }
		[[nodiscard]] inline bool operator!=(const mousebutton& other) const noexcept { return code->value == other.code->value; }

		inline static const mousebutton& Get(size_t value) { return *inputcode_mouse_button::ps_FromValueMap[value]; }
		ZX_MOUSEBUTTON_DEF(none);
		ZX_MOUSEBUTTON_DEF(left);
		ZX_MOUSEBUTTON_DEF(right);
		ZX_MOUSEBUTTON_DEF(middle);
		ZX_MOUSEBUTTON_DEF(b4);
		ZX_MOUSEBUTTON_DEF(b5);
		ZX_MOUSEBUTTON_DEF(b6);
		ZX_MOUSEBUTTON_DEF(b7);
		ZX_MOUSEBUTTON_DEF(b8);
	};


}