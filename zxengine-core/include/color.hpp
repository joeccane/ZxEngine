#pragma once
#include "math.hpp"
namespace zx
{
	struct color3
	{
		union
		{
			struct { float r, g, b; };
			vector3 vector;
		};

		[[nodiscard]] inline constexpr color3(const vector3& vector) noexcept : vector(vector) {}
		[[nodiscard]] inline constexpr color3(float r, float g, float b) noexcept : r(r), g(g), b(b) {}

		inline color3 grayscale()
		{
			float result = r * 0.2125f + g * 0.7154f + b * 0.0721f;
			result /= 3;
			return color3(result, result, result);
		}

		[[nodiscard]] inline static constexpr color3 black() noexcept { return { 0.0f, 0.0f, 0.0f }; }
		[[nodiscard]] inline static constexpr color3 blue() noexcept { return { 0.0f, 0.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color3 cyan() noexcept { return { 0.0f, 1.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color3 gray() noexcept { return { 0.5f, 0.5f, 0.5f }; }
		[[nodiscard]] inline static constexpr color3 gray(float value) noexcept { return { value, value, value}; }
		[[nodiscard]] inline static constexpr color3 green() noexcept { return { 0.0f, 1.0f, 0.0f }; }
		[[nodiscard]] inline static constexpr color3 magenta() noexcept { return { 1.0f, 0.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color3 white() noexcept { return { 1.0f, 1.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color3 yellow() noexcept { return { 1.0f, 0.92f, 0.016f }; }

		inline constexpr color3& operator=(const color3& other) noexcept { vector = other.vector; }
		inline constexpr color3& operator=(const color3&& other) noexcept { vector = other.vector; }
		[[nodiscard]] inline constexpr bool operator==(const color3& other) noexcept { return vector == other.vector; }
		[[nodiscard]] inline constexpr bool operator!=(const color3& other) noexcept { return vector != other.vector; }
	};

	struct color4
	{
		union
		{
			struct { float r, g, b, a; };
			vector4 vector;
		};

		[[nodiscard]] inline constexpr color4(const vector4& vector) noexcept : vector(vector) {}
		[[nodiscard]] inline constexpr color4(const vector3& vector) noexcept : vector(vector, 1.0f) {}

		[[nodiscard]] inline constexpr color4(float r, float g, float b) noexcept : r(r), g(g), b(b), a(1.0f) {}
		[[nodiscard]] inline constexpr color4(float r, float g, float b, float a) noexcept : r(r), g(g), b(b), a(a) {}

		[[nodiscard]] inline constexpr color4(const color3& other) noexcept : vector(other.vector, 1.0f) {}

		inline color3 grayscale()
		{
			float result = r * 0.2125f + g * 0.7154f + b * 0.0721f;
			result /= 3;
			return color3(result, result, result);
		}

		[[nodiscard]] inline static constexpr color4 black() noexcept { return { 0.0f, 0.0f, 0.0f }; }
		[[nodiscard]] inline static constexpr color4 blue() noexcept { return { 0.0f, 0.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color4 cyan() noexcept { return { 0.0f, 1.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color4 gray() noexcept { return { 0.5f, 0.5f, 0.5f }; }
		[[nodiscard]] inline static constexpr color4 gray(float value) noexcept { return { value, value, value }; }
		[[nodiscard]] inline static constexpr color4 green() noexcept { return { 0.0f, 1.0f, 0.0f }; }
		[[nodiscard]] inline static constexpr color4 magenta() noexcept { return { 1.0f, 0.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color4 white() noexcept { return { 1.0f, 1.0f, 1.0f }; }
		[[nodiscard]] inline static constexpr color4 yellow() noexcept { return { 1.0f, 0.92f, 0.016f }; }

		[[nodiscard]] inline static constexpr color4 transparent() noexcept { return { 1.0f, 1.0f, 1.0f, 0.0f }; }


		inline constexpr color4& operator=(const color4& other) noexcept { vector = other.vector; }
		inline constexpr color4& operator=(const color4&& other) noexcept { vector = other.vector; }
		[[nodiscard]] inline constexpr bool operator==(const color4& other) noexcept { return vector == other.vector; }
		[[nodiscard]] inline constexpr bool operator!=(const color4& other) noexcept { return vector != other.vector; }
	};
}