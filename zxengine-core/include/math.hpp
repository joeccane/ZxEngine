#pragma once
#include <concepts>
#include <cmath>


#include "core.hpp"


#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "vendor/glm/common.hpp"
#include "vendor/glm/gtc/quaternion.hpp"
#include "vendor/glm/gtx/quaternion.hpp"


namespace zx
{
#define ZX__GLMWRAPPER(name)\
template<std::floating_point T>\
[[nodiscard]] constexpr inline static T name(T value) noexcept {\
	return glm::name(value);\
}

#define ZX__MATH_CONSTANT(name, value)\
template<std::floating_point T = float>\
inline static const T name = static_cast<T>(value)
	struct math
	{
		struct constant
		{
			ZX__MATH_CONSTANT(pi, 3.1415926535897932384626433);
			ZX__MATH_CONSTANT(pi2, pi<T> / 2);
			ZX__MATH_CONSTANT(pi4, pi<T> / 4);
			ZX__MATH_CONSTANT(e, 2.71828182845904523536028747);
			ZX__MATH_CONSTANT(sqrt2, 1.41421356237309504880168872);
			ZX__MATH_CONSTANT(g, 9.8);
			ZX__MATH_CONSTANT(G, 0.000000000066743015);
			ZX__MATH_CONSTANT(log2, 0.69314718055994530941723212);
			ZX__MATH_CONSTANT(radians_to_degrees, 180.0 / pi<T>);
			ZX__MATH_CONSTANT(degrees_to_radians, pi<T> / 180.0);
		};
		ZX__GLMWRAPPER(abs);
		ZX__GLMWRAPPER(floor);
		ZX__GLMWRAPPER(ceil);
		ZX__GLMWRAPPER(log);
		ZX__GLMWRAPPER(sqrt);

		ZX__GLMWRAPPER(sin);
		ZX__GLMWRAPPER(cos);
		ZX__GLMWRAPPER(tan);
		
		ZX__GLMWRAPPER(asin);
		ZX__GLMWRAPPER(acos);
		ZX__GLMWRAPPER(atan);

		ZX__GLMWRAPPER(sinh);
		ZX__GLMWRAPPER(cosh);
		ZX__GLMWRAPPER(tanh);

		ZX__GLMWRAPPER(asinh);
		ZX__GLMWRAPPER(acosh);
		ZX__GLMWRAPPER(atanh);

		template<std::floating_point T>
		[[nodiscard]] inline static T atan2(T y, T x) {
			return std::atan2(y, x);
		}
		template<std::floating_point T>
		[[nodiscard]] inline static T pow(T value, T power) noexcept { 
			return glm::pow(value, power); 
		}
		template<std::floating_point T>
		[[nodiscard]] inline static T pow(T value, int power) noexcept {
			return std::pow(value, power);
		}

		template<typename T>
		requires std::floating_point<T> || std::integral<T>
		[[nodiscard]] inline static T min(T a, T b) {
			if (a < b) 
				return a;
			return b;
		}
		template<typename T>
		requires std::floating_point<T> || std::integral<T>
		[[nodiscard]] inline static T max(T a, T b) {
			if (a > b) 
				return a;
			return b;
		}

		template<std::integral T>
		[[nodiscard]] inline static constexpr T min() {
			if constexpr (std::unsigned_integral<T>)
				return 0;
			else if constexpr (std::same_as<T, char>)
				return CHAR_MIN;
			else if constexpr (std::same_as<T, short int>)
				return SHRT_MIN;
			else if constexpr (std::same_as<T, int>)
				return INT_MIN;
			else if constexpr (std::same_as<T, long int>)
				return LONG_MIN;
			else if constexpr (std::same_as<T, long long int>)
				return LLONG_MIN;

			assert(false);
		}
		template<std::integral T>
		[[nodiscard]] inline static constexpr T max() {
			if constexpr (std::same_as<T, char>)
				return CHAR_MAX;
			else if constexpr (std::same_as<T, unsigned char>)
				return UCHAR_MAX;
			else if constexpr (std::same_as<T, short int>)
				return SHRT_MAX;
			else if constexpr (std::same_as<T, unsigned short int>)
				return USHRT_MAX;
			else if constexpr (std::same_as<T, int>)
				return INT_MAX;
			else if constexpr (std::same_as<T, unsigned int>)
				return UINT_MAX;
			else if constexpr (std::same_as<T, long int>)
				return LONG_MAX;
			else if constexpr (std::same_as<T, unsigned long int>)
				return ULONG_MAX;
			else if constexpr (std::same_as<T, long long int>)
				return LLONG_MAX;
			else if constexpr (std::same_as<T, unsigned long long int>)
				return ULLONG_MAX;

			assert(false);
		}
		template<typename T>
		requires std::floating_point<T> || std::integral<T>
		[[nodiscard]] inline static constexpr T clamp(T value, T a, T b) noexcept { return std::clamp(value, a, b); }

		template<typename TValues, typename TDelta>
		requires (std::floating_point<TValues> || std::integral<TValues>) && std::floating_point<TDelta>
		[[nodiscard]] inline static TValues lerp(TValues min, TValues max, TDelta t) {
			if (t < 0) return min;
			if (t > 1) return max;
			return static_cast<TValues>((max - min) * t + min);
		}
		template<typename TValues, typename TDelta>
		requires (std::floating_point<TValues> || std::integral<TValues>) && std::floating_point<TDelta>
		[[nodiscard]] inline static TValues smoothstep(TValues min, TValues max, TDelta t) {
			t = math::clamp<TValues>((t - min) / (max - min), 0, 1);
			return static_cast<TValues>(t * t * (3 - 2 * t));
		}
	};

	template<std::floating_point T>
	struct radians_basic;

	template<std::floating_point T>
	struct degrees_basic
	{
		float value;
		[[nodiscard]] inline constexpr explicit degrees_basic(float degs) noexcept : value(degs) {}
		template<std::same_as<radians_basic<T>> RadBasic>
		[[nodiscard]] inline constexpr degrees_basic(RadBasic rads) noexcept
			: value(rads.value * math::constant::radians_to_degrees<T>) {}


	};
	template<std::floating_point T>
	struct radians_basic
	{
		float value;
		[[nodiscard]] inline constexpr explicit radians_basic(float rads) 
			: value(rads) {}
		[[nodiscard]] inline constexpr radians_basic(degrees_basic<T> degs) noexcept
			: value(degs.value* math::constant::degrees_to_radians<T>) {}
	};
	template<std::floating_point T>
	struct angle_basic
	{
		[[nodiscard]] inline constexpr angle_basic() noexcept : pm_Radians(0) {}
		[[nodiscard]] inline constexpr angle_basic(degrees_basic<T> degs) noexcept 
			: pm_Radians(degs.value* math::constant::degrees_to_radians<T>) {}
		[[nodiscard]] inline constexpr angle_basic(radians_basic<T> rads) noexcept
			: pm_Radians(rads.value) {}
		[[nodiscard]] inline static constexpr angle_basic radians(T value) {
			return angle_basic(value); 
		}
		[[nodiscard]] inline static constexpr angle_basic degrees(T value) {
			return angle_basic(value * math::constant::degrees_to_radians<T>); 
		}

		inline constexpr void wrap()
		{
			pm_Radians = std::fmod(pm_Radians + math::constant::pi<T>, 2 * math::constant::pi<T>);
			if (pm_Radians < 0)
				pm_Radians += math::constant::pi<T> * 2;
			pm_Radians -= math::constant::pi<T>;
		}

		[[nodiscard]] inline static constexpr angle_basic zero() noexcept { return degrees(0); }
		[[nodiscard]] inline static constexpr angle_basic _45() noexcept { return degrees(45); }
		[[nodiscard]] inline static constexpr angle_basic _90() noexcept { return degrees(90); }
		[[nodiscard]] inline static constexpr angle_basic _180() noexcept { return degrees(180); }

		[[nodiscard]] inline constexpr angle_basic operator+(angle_basic other) const noexcept {
			return angle_basic(pm_Radians + other.pm_Radians); 
		}
		[[nodiscard]] inline constexpr angle_basic operator-(angle_basic other) const noexcept {
			return angle_basic(pm_Radians - other.pm_Radians);
		}
		[[nodiscard]] inline constexpr angle_basic operator*(T other) const noexcept {
			return angle_basic(pm_Radians * other);
		}
		[[nodiscard]] inline constexpr angle_basic operator/(T other) const noexcept {
			return angle_basic(pm_Radians / other);
		}
		[[nodiscard]] inline constexpr angle_basic operator-() const { 
			return angle_basic(-pm_Radians); 
		}
		[[nodiscard]] inline constexpr angle_basic operator+() const {
			return angle_basic(pm_Radians);
		}

		inline constexpr angle_basic& operator=(angle_basic other) {
			pm_Radians = other.pm_Radians;
			return *this;
		}
		inline constexpr angle_basic& operator+=(angle_basic other) {
			pm_Radians += other.pm_Radians;
			return *this;
		}
		inline constexpr angle_basic& operator-=(angle_basic other) {
			pm_Radians -= other.pm_Radians;
			return *this;
		}
		inline constexpr angle_basic& operator*=(T other) {
			pm_Radians *= other;
			return *this;
		}
		inline constexpr angle_basic& operator/=(T other) {
			pm_Radians /= other;
			return *this;
		}


		[[nodiscard]] inline constexpr explicit operator radians_basic<T>() {
			return radians_basic(pm_Radians);
		}
		[[nodiscard]] inline constexpr explicit operator degrees_basic<T>() {
			return degrees_basic(pm_Radians * math::constant::radians_to_degrees<T>);
		}

		[[nodiscard]] inline operator T* () {
			return &pm_Radians;
		}
	private:
		[[nodiscard]] inline constexpr angle_basic(T radians) : pm_Radians(radians) {}

		T pm_Radians;
	};

	using angle = angle_basic<float>;
	using degrees = degrees_basic<float>;
	using radians = radians_basic<float>;

	struct vector2
	{
		union {
			glm::vec2 glmVector;
			struct {
				float x, y;
			};
		};

		[[nodiscard]] inline constexpr vector2() noexcept : x(0), y(0) {}
		[[nodiscard]] inline constexpr vector2(const vector2& copy) noexcept : x(copy.x), y(copy.y) {}
		[[nodiscard]] inline constexpr vector2(vector2&& move) noexcept : x(move.x), y(move.y) {}

		[[nodiscard]] inline constexpr vector2(float value) noexcept : x(value), y(value) {}
		[[nodiscard]] inline constexpr vector2(float x, float y) noexcept : x(x), y(y) {}

		[[nodiscard]] inline constexpr vector2(glm::vec2 glmVector) noexcept : glmVector(glmVector) {}
		inline void Normalize() noexcept
		{
			glmVector = glm::normalize(glmVector);
		}
		[[nodiscard]] inline vector2 normalized()
		{
			return glm::normalize(glmVector);
		}

		[[nodiscard]] inline float magnitude() const noexcept {
			return glm::length(glmVector);
		}
		[[nodiscard]] inline constexpr float sqrMagnitude() const noexcept {
			return x * x + y * y;
		}

		[[nodiscard]] inline static float distance(const vector2& from, const vector2& to) {
			return glm::distance(from.glmVector, to.glmVector);
		}
		[[nodiscard]] inline static float distanceSqrd(const vector2& from, const vector2& to) {
			return math::pow(from.x - to.x, 2.0f) + math::pow(from.y - to.y, 2.0f);
		}

		[[nodiscard]] inline constexpr vector2 operator+(const vector2& other) const noexcept {
			return { x + other.x, y + other.y };
		}
		[[nodiscard]] inline constexpr vector2 operator-(const vector2& other) const noexcept {
			return { x - other.x,y - other.y };
		}
		[[nodiscard]] inline constexpr vector2 operator*(float other) const noexcept {
			return { x * other, y * other };
		}
		[[nodiscard]] inline constexpr vector2 operator/(float other) const noexcept {
			return { x / other, y / other };
		}
		[[nodiscard]] inline constexpr vector2 operator-() const noexcept {
			return { -x, -y };
		}
		[[nodiscard]] inline constexpr vector2 operator+() const noexcept {
			return { +x, +y };
		}

		inline vector2& operator=(const vector2& other) noexcept {
			glmVector = other.glmVector;
			return *this;
		}
		inline vector2& operator+=(const vector2& other) noexcept {
			x += other.x;
			y += other.y;
			return *this;
		}
		inline vector2& operator-=(const vector2& other) noexcept {
			x -= other.x;
			y -= other.y;
			return *this;
		}
		inline vector2& operator*=(float other) noexcept {
			x *= other;
			y *= other;
			return *this;
		}
		inline vector2& operator/=(float other) noexcept {
			x /= other;
			y /= other;
		}


		[[nodiscard]] inline constexpr bool operator==(const vector2& other) const {
			return x == other.x && y == other.y;
		}
		[[nodiscard]] inline constexpr bool operator!=(const vector2& other) const {
			return x != other.x || y != other.y;
		}

		[[nodiscard]] inline static constexpr vector2 zero() noexcept {
			return vector2();
		}
		[[nodiscard]] inline static constexpr vector2 one() noexcept {
			return vector2(1.0f);
		}
		[[nodiscard]] inline static constexpr vector2 right() noexcept {
			return vector2(1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector2 left() noexcept {
			return vector2(-1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector2 up() noexcept {
			return vector2(0.0f, 1.0f);
		}
		[[nodiscard]] inline static constexpr vector2 down() noexcept {
			return vector2(0.0f, -1.0f);
		}
		[[nodiscard]] inline static constexpr vector2 xAxis() noexcept {
			return right();
		}
		[[nodiscard]] inline static constexpr vector2 yAxis() noexcept {
			return up();
		}
		[[nodiscard]] inline static vector2 direction(float x, float y) noexcept {
			return vector2(x, y).normalized();
		}

		[[nodiscard]] inline static vector2 lerp(const vector2& min, const vector2& max, float t) {
			return vector2(math::lerp(min.x, max.x, t), math::lerp(min.y, max.y, t));
		}
		[[nodiscard]] inline static vector2 smoothstep(const vector2& min, const vector2& max, float t) {
			return vector2(math::smoothstep(min.x, max.x, t), math::smoothstep(min.y, max.y, t));
		}


		[[nodiscard]] inline operator float* () {
			return &x;
		}
	};

	struct vector3
	{
		union {
			glm::vec3 glmVector;
			struct {
				float x, y, z;
			};
			vector2 xy;
		};

		[[nodiscard]] inline constexpr vector3() noexcept : x(0), y(0), z(0) {}
		[[nodiscard]] inline constexpr vector3(const vector3& copy) noexcept : x(copy.x), y(copy.y), z(copy.z) {}
		[[nodiscard]] inline constexpr vector3(vector3&& move) noexcept : x(move.x), y(move.y), z(move.z) {}

		[[nodiscard]] inline constexpr vector3(float value) noexcept : x(value), y(value), z(value) {}
		[[nodiscard]] inline constexpr vector3(float x, float y) noexcept : x(x), y(y), z(0) {}
		[[nodiscard]] inline constexpr vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}
		[[nodiscard]] inline constexpr explicit vector3(const vector2& v) noexcept : x(v.x), y(v.y), z(0) {}
		[[nodiscard]] inline constexpr vector3(const vector2& v, float z) noexcept : x(v.x), y(v.y), z(z) {}
		[[nodiscard]] inline constexpr explicit vector3(const glm::vec3& glmVector) noexcept : glmVector(glmVector) {}

		inline void Normalize() noexcept
		{
			glmVector = glm::normalize(glmVector);
		}
		[[nodiscard]] inline vector3 normalized()
		{
			return vector3(glm::normalize(glmVector));
		}

		[[nodiscard]] inline float magnitude() const noexcept {
			return glm::length(glmVector);
		}
		[[nodiscard]] inline constexpr float sqrMagnitude() const noexcept {
			return x * x + y * y + z * z;
		}

		[[nodiscard]] inline static float distance(const vector3& from, const vector3& to) {
			return glm::distance(from.glmVector, to.glmVector);
		}
		[[nodiscard]] inline static float distanceSqrd(const vector3& from, const vector3& to) {
			return math::pow(from.x - to.x, 2.0f) + math::pow(from.y - to.y, 2.0f) + math::pow(from.z - to.z, 2.0f);
		}
		[[nodiscard]] inline static float dot(const vector3& a, const vector3& b) noexcept {
			return glm::dot(a.glmVector, b.glmVector);
		}
		[[nodiscard]] inline static vector3 cross(const vector3& a, const vector3& b) noexcept {
			return vector3(glm::cross(a.glmVector, b.glmVector));
		}
		[[nodiscard]] inline static vector3 reflect(const vector3& vector, const vector3& normal) {
			return vector3(glm::reflect(vector.glmVector, normal.glmVector));
		}
		[[nodiscard]] inline constexpr vector3 operator+(const vector3& other) const noexcept {
			return { x + other.x, y + other.y, z + other.z };
		}
		[[nodiscard]] inline constexpr vector3 operator-(const vector3& other) const noexcept {
			return { x - other.x,y - other.y, z - other.z };
		}
		[[nodiscard]] inline constexpr vector3 operator*(float other) const noexcept {
			return { x * other, y * other, z * other};
		}
		[[nodiscard]] inline constexpr vector3 operator/(float other) const noexcept {
			return { x / other, y / other, z / other };
		}
		[[nodiscard]] inline constexpr vector3 operator-() const noexcept {
			return { -x, -y, -z };
		}
		[[nodiscard]] inline constexpr vector3 operator+() const noexcept {
			return { +x, +y, +z };
		}

		inline vector3& operator=(const vector3& other) noexcept {
			glmVector = other.glmVector;
			return *this;
		}
		inline vector3& operator+=(const vector3& other) noexcept {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		inline vector3& operator-=(const vector3& other) noexcept {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		inline vector3& operator*=(float other) noexcept {
			x *= other;
			y *= other;
			z *= other;
			return *this;
		}
		inline vector3& operator/=(float other) noexcept {
			x /= other;
			y /= other;
			z /= other;
			return *this;
		}


		[[nodiscard]] inline constexpr bool operator==(const vector3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}
		[[nodiscard]] inline constexpr bool operator!=(const vector3& other) const {
			return x != other.x || y != other.y || z != other.z;
		}

		[[nodiscard]] inline static constexpr vector3 zero() noexcept {
			return vector3();
		}
		[[nodiscard]] inline static constexpr vector3 one() noexcept {
			return vector3(1.0f);
		}
		[[nodiscard]] inline static constexpr vector3 right() noexcept {
			return vector3(1.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector3 left() noexcept {
			return vector3(-1.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector3 up() noexcept {
			return vector3(0.0f, 1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector3 down() noexcept {
			return vector3(0.0f, -1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector3 forward() noexcept {
			return vector3(0.0f, 0.0f, 1.0f);
		}
		[[nodiscard]] inline static constexpr vector3 backward() noexcept {
			return vector3(0.0f, 0.0f, -1.0f);
		}

		[[nodiscard]] inline static constexpr vector3 xAxis() noexcept {
			return right();
		}
		[[nodiscard]] inline static constexpr vector3 yAxis() noexcept {
			return up();
		}
		[[nodiscard]] inline static constexpr vector3 zAxis() noexcept {
			return forward();
		}
		[[nodiscard]] inline static vector3 direction(float x, float y, float z) noexcept {
			return vector3(x, y, z).normalized();
		}

		[[nodiscard]] inline static vector3 lerp(const vector3& min, const vector3& max, float t) {
			return vector3(math::lerp(min.x, max.x, t), math::lerp(min.y, max.y, t), math::lerp(min.z, max.z, t));
		}
		[[nodiscard]] inline static vector3 smoothstep(const vector3& min, const vector3& max, float t) {
			return vector3(math::smoothstep(min.x, max.x, t), math::smoothstep(min.y, max.y, t), math::smoothstep(min.z, max.z, t));
		}


		[[nodiscard]] inline operator float* () noexcept{
			return &x;
		}
	};


	struct vector4
	{
		union {
			glm::vec4 glmVector;
			struct {
				float x, y, z, w;
			};
			vector2 xy;
			vector3 xyz;
		};

		[[nodiscard]] inline constexpr vector4() noexcept : x(0), y(0), z(0), w(0) {}
		[[nodiscard]] inline constexpr vector4(const vector4& copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}
		[[nodiscard]] inline constexpr vector4(vector4&& move) noexcept : x(move.x), y(move.y), z(move.z), w(move.w) {}

		[[nodiscard]] inline constexpr vector4(float value) noexcept : x(value), y(value), z(value), w(value) {}
		[[nodiscard]] inline constexpr vector4(float x, float y) noexcept : x(x), y(y), z(0), w(1) {}
		[[nodiscard]] inline constexpr vector4(float x, float y, float z) noexcept : x(x), y(y), z(z), w(1) {}
		[[nodiscard]] inline constexpr vector4(float x, float y, float z, float w) noexcept : x(), y(y), z(z), w(w) {}

		[[nodiscard]] inline constexpr explicit vector4(const vector2& v) noexcept : x(v.x), y(v.y), z(0), w(1) {}
		[[nodiscard]] inline constexpr vector4(const vector2& v, float z) noexcept : x(v.x), y(v.y), z(z), w(1) {}
		[[nodiscard]] inline constexpr explicit vector4(const vector3& v) noexcept : x(v.x), y(v.y), z(v.z), w(1) {}
		[[nodiscard]] inline constexpr vector4(const vector3& v, float w) noexcept : x(v.x), y(v.y), z(v.z), w(w) {}

		[[nodiscard]] inline constexpr explicit vector4(const glm::vec4& glmVector) noexcept : glmVector(glmVector) {}


		inline void Normalize() noexcept
		{
			glmVector = glm::normalize(glmVector);
		}
		[[nodiscard]] inline vector4 normalized()
		{
			return vector4(glm::normalize(glmVector));
		}

		[[nodiscard]] inline float magnitude() const noexcept {
			return glm::length(glmVector);
		}
		[[nodiscard]] inline constexpr float sqrMagnitude() const noexcept {
			return x * x + y * y + z * z + w * w;
		}

		[[nodiscard]] inline static float distance(const vector4& from, const vector4& to) {
			return glm::distance(from.glmVector, to.glmVector);
		}
		[[nodiscard]] inline static float distanceSqrd(const vector4& from, const vector4& to) {
			return math::pow(from.x - to.x, 2.0f) + math::pow(from.y - to.y, 2.0f) + math::pow(from.z - to.z, 2.0f) + math::pow(from.w - to.w, 2.0f);
		}
		[[nodiscard]] inline static float dot(const vector4& a, const vector4& b) noexcept {
			return glm::dot(a.glmVector, b.glmVector);
		}
		[[nodiscard]] inline static vector4 reflect(const vector4& vector, const vector4& normal) {
			return vector4(glm::reflect(vector.glmVector, normal.glmVector));
		}
		[[nodiscard]] inline constexpr vector4 operator+(const vector4& other) const noexcept {
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}
		[[nodiscard]] inline constexpr vector4 operator-(const vector4& other) const noexcept {
			return { x - other.x,y - other.y, z - other.z, w - other.w };
		}
		[[nodiscard]] inline constexpr vector4 operator*(float other) const noexcept {
			return { x * other, y * other, z * other, w * other };
		}
		[[nodiscard]] inline constexpr vector4 operator/(float other) const noexcept {
			return { x / other, y / other, z / other, w / other};
		}
		[[nodiscard]] inline constexpr vector4 operator-() const noexcept {
			return { -x, -y, -z, -w };
		}
		[[nodiscard]] inline constexpr vector4 operator+() const noexcept {
			return { +x, +y, +z, +w };
		}

		inline vector4& operator=(const vector4& other) noexcept {
			glmVector = other.glmVector;
			return *this;
		}
		inline vector4& operator+=(const vector4& other) noexcept {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		inline vector4& operator-=(const vector4& other) noexcept {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		inline vector4& operator*=(float other) noexcept {
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}
		inline vector4& operator/=(float other) noexcept {
			x /= other;
			y /= other;
			z /= other;
			z /= other;
			return *this;
		}


		[[nodiscard]] inline constexpr bool operator==(const vector4& other) const {
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}
		[[nodiscard]] inline constexpr bool operator!=(const vector4& other) const {
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}

		[[nodiscard]] inline static constexpr vector4 zero() noexcept {
			return vector4();
		}
		[[nodiscard]] inline static constexpr vector4 one() noexcept {
			return vector4(1.0f);
		}
		[[nodiscard]] inline static constexpr vector4 right() noexcept {
			return vector4(1.0f, 0.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 left() noexcept {
			return vector4(-1.0f, 0.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 up() noexcept {
			return vector4(0.0f, 1.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 down() noexcept {
			return vector4(0.0f, -1.0f, 0.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 forward() noexcept {
			return vector4(0.0f, 0.0f, 1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 backward() noexcept {
			return vector4(0.0f, 0.0f, -1.0f, 0.0f);
		}
		[[nodiscard]] inline static constexpr vector4 in() noexcept {
			return vector4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		[[nodiscard]] inline static constexpr vector4 out() noexcept {
			return vector4(0.0f, 0.0f, 0.0f, -1.0f);
		}

		[[nodiscard]] inline static constexpr vector4 xAxis() noexcept {
			return right();
		}
		[[nodiscard]] inline static constexpr vector4 yAxis() noexcept {
			return up();
		}
		[[nodiscard]] inline static constexpr vector4 zAxis() noexcept {
			return forward();
		}
		[[nodiscard]] inline static constexpr vector4 wAxis() noexcept {
			return in();
		}
		[[nodiscard]] inline static vector4 direction(float x, float y, float z) noexcept {
			return vector4(x, y, z).normalized();
		}

		[[nodiscard]] inline static vector4 lerp(const vector4& min, const vector4& max, float t) {
			return vector4(math::lerp(min.x, max.x, t), math::lerp(min.y, max.y, t), math::lerp(min.z, max.z, t));
		}
		[[nodiscard]] inline static vector4 smoothstep(const vector4& min, const vector4& max, float t) {
			return vector4(math::smoothstep(min.x, max.x, t), math::smoothstep(min.y, max.y, t), math::smoothstep(min.z, max.z, t));
		}

		[[nodiscard]] inline operator float* () noexcept {
			return &x;
		}
	};


	struct point2
	{
		union {
			struct { int width, height; };
			struct { int x, y; };
		};

		[[nodiscard]] inline constexpr point2() noexcept : x(0), y(0) {}
		[[nodiscard]] inline constexpr point2(const point2& copy) noexcept : x(copy.x), y(copy.y) {}
		[[nodiscard]] inline constexpr point2(point2&& move) noexcept : x(move.x), y(move.y) {}

		[[nodiscard]] inline constexpr point2(int value) noexcept : x(value), y(value) {}
		[[nodiscard]] inline constexpr point2(int x, int y) noexcept : x(x), y(y) {}

		[[nodiscard]] inline constexpr point2 operator+(const point2& other) const noexcept {
			return { x + other.x, y + other.y };
		}
		[[nodiscard]] inline constexpr point2 operator-(const point2& other) const noexcept {
			return { x - other.x, y - other.y };
		}
		[[nodiscard]] inline constexpr point2 operator*(int other) const noexcept {
			return { x * other, y * other };
		}
		[[nodiscard]] inline constexpr point2 operator/(int other) const noexcept {
			return { x / other, y / other };
		}


		[[nodiscard]] inline constexpr point2 zero() noexcept { return point2(); }
		[[nodiscard]] inline constexpr point2 one() noexcept { return point2(1); }
		[[nodiscard]] inline constexpr point2 right() noexcept { return point2(1, 0); }
		[[nodiscard]] inline constexpr point2 left() noexcept { return point2(-1, 0); }
		[[nodiscard]] inline constexpr point2 up() noexcept { return point2(0, 1); }
		[[nodiscard]] inline constexpr point2 down() noexcept { return point2(0, -1); }

		[[nodiscard]] inline operator int* () noexcept {
			return &x;
		}
	};
	using size2 = point2;

	struct point3
	{
		union {
			struct { int width, height, length; };
			struct { int x, y, z; };
		};

		[[nodiscard]] inline constexpr point3() noexcept : x(0), y(0), z(0) {}
		[[nodiscard]] inline constexpr point3(const point3& copy) noexcept : x(copy.x), y(copy.y), z(copy.z) {}
		[[nodiscard]] inline constexpr point3(point3&& move) noexcept : x(move.x), y(move.y), z(move.z) {}

		[[nodiscard]] inline constexpr point3(int value) noexcept : x(value), y(value), z(value) {}
		[[nodiscard]] inline constexpr point3(int x, int y) noexcept : x(x), y(y), z(0) {}
		[[nodiscard]] inline constexpr point3(int x, int y, int z) noexcept : x(x), y(y), z(z) {}

		[[nodiscard]] inline constexpr explicit point3(const point2& convert) : x(convert.x), y(convert.y), z(0) {}


		[[nodiscard]] inline constexpr point3 operator+(const point3& other) const noexcept {
			return { x + other.x, y + other.y };
		}
		[[nodiscard]] inline constexpr point3 operator-(const point3& other) const noexcept {
			return { x - other.x, y - other.y };
		}
		[[nodiscard]] inline constexpr point3 operator*(int other) const noexcept {
			return { x * other, y * other };
		}
		[[nodiscard]] inline constexpr point3 operator/(int other) const noexcept {
			return { x / other, y / other };
		}


		[[nodiscard]] inline constexpr point3 zero() noexcept { return point3(); }
		[[nodiscard]] inline constexpr point3 one() noexcept { return point3(1); }
		[[nodiscard]] inline constexpr point3 right() noexcept { return point3(1, 0, 0); }
		[[nodiscard]] inline constexpr point3 left() noexcept { return point3(-1, 0, 0); }
		[[nodiscard]] inline constexpr point3 up() noexcept { return point3(0, 1, 0); }
		[[nodiscard]] inline constexpr point3 down() noexcept { return point3(0, -1, 0); }
		[[nodiscard]] inline constexpr point3 forward() noexcept { return point3(0, 0, 1); }
		[[nodiscard]] inline constexpr point3 backward() noexcept { return point3(0, 0, -1); }

		[[nodiscard]] inline operator int* () noexcept {
			return &x;
		}
	};
	using size3 = point3;

	struct matrix
	{
		union {
			glm::mat4 glmMatrix;
			struct {
				float	_11, _12, _13, _14,
						_21, _22, _23, _24,
						_31, _32, _33, _34,
						_41, _42, _43, _44;
			};
			float data[16];
		};

		[[nodiscard]] inline matrix() noexcept : glmMatrix(glm::mat4(1.0f)) {}
		[[nodiscard]] inline matrix(const matrix& copy) noexcept : glmMatrix(copy.glmMatrix) {}
		[[nodiscard]] inline matrix(matrix&& move) noexcept : glmMatrix(move.glmMatrix) {}

		[[nodiscard]] inline explicit matrix(const glm::mat4& convert) noexcept : glmMatrix(convert) {}

		[[nodiscard]] inline static matrix identity() noexcept { return matrix(glm::mat4(1.0f)); }

		[[nodiscard]] inline static matrix translate(const vector3& translation) {
			return matrix(glm::translate(identity().glmMatrix, translation.glmVector));
		}
		[[nodiscard]] inline static matrix scale(float scalar) noexcept {
			return matrix(glm::scale(identity().glmMatrix, vector3(scalar).glmVector));
		}
		[[nodiscard]] inline static matrix scale(const vector3& scale) noexcept {
			return matrix(glm::scale(identity().glmMatrix, scale.glmVector));
		}
		[[nodiscard]] inline static matrix rotate(const vector3& axis, radians amount) {
			return matrix(glm::rotate(identity().glmMatrix, amount.value, axis.glmVector));
		}
		[[nodiscard]] inline static matrix rotate(vector3 euler) { 
			return matrix(glm::toMat4(glm::quat(euler.glmVector))); 
		}

		[[nodiscard]] inline matrix operator*(const matrix& other) const noexcept {
			return matrix(glmMatrix * other.glmMatrix);
		}
		inline matrix& operator=(const matrix& assign) noexcept {
			glmMatrix = assign.glmMatrix;
			return *this;
		}

		[[nodiscard]] inline matrix inverse() const noexcept {
			return matrix(glm::inverse(glmMatrix));
		}


		[[nodiscard]] inline operator float* () noexcept {
			return &_11;
		}

	};


	template<typename T>
	requires std::floating_point<T> || std::integral<T>
	struct range
	{
		T min;
		T max;
		[[nodiscard]] inline constexpr range() noexcept : min(0), max(1) {}
		[[nodiscard]] inline constexpr range(T max) noexcept : min(0), max(max) {}
		[[nodiscard]] inline constexpr range(T min, T max) noexcept : min(min), max(max) {}

		[[nodiscard]] inline constexpr bool within(T value) noexcept {
			return value >= min && value <= max;
		}
		[[nodiscard]] inline constexpr bool outside(T value) noexcept {
			return value < min || value > max;
		}

		template<std::floating_point TDelta>
		[[nodiscard]] inline constexpr T lerp(TDelta t) noexcept {
			return math::lerp(min, max, t);
		}
		template<std::floating_point TDelta>
		[[nodiscard]] inline constexpr T smoothstep(TDelta t) noexcept {
			return math::smoothstep(min, max, t);
		}
	};
}