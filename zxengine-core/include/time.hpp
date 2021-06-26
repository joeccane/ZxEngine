#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <concepts>
namespace zx
{
	using timepoint = std::chrono::time_point<std::chrono::system_clock>;

	template<typename T>
	struct duration
	{
		using ChronoType = T;
		[[nodiscard]] inline constexpr duration() noexcept 
			: pm_Data(0) {}
		[[nodiscard]] explicit constexpr duration(float count) noexcept 
			: pm_Data(count) {}
		[[nodiscard]] explicit constexpr duration(int count) noexcept 
			: pm_Data(count) {}

		[[nodiscard]] inline constexpr duration(const T& copy) 
			: pm_Data(copy) {}

		[[nodiscard]] inline constexpr float count() const { return pm_Data.count(); }


		[[nodiscard]] inline constexpr duration operator+(const duration& other) const noexcept {
			return duration(pm_Data.count() + other.pm_Data.count());
		}
		[[nodiscard]] inline constexpr duration operator-(const duration& other) const noexcept {
			return duration(pm_Data.count() - other.pm_Data.count());
		}
		[[nodiscard]] inline constexpr duration operator*(float other) const noexcept {
			return duration(pm_Data.count() * other);
		}
		[[nodiscard]] inline constexpr duration operator/(float other) const noexcept {
			return duration(pm_Data.count() / other);
		}

		inline constexpr duration& operator+=(const duration& other) noexcept {
			pm_Data = T(pm_Data.count() + other.count());
			return *this;
		}
		inline constexpr duration& operator-=(const duration& other) noexcept {
			pm_Data = T(pm_Data.count() - other.count());
			return *this;
		}
		inline constexpr duration& operator*=(float other) noexcept {
			pm_Data = T(pm_Data.count() * other);
			return *this;
		}
		inline constexpr duration& operator/=(float other) noexcept {
			pm_Data = T(pm_Data.count() / other);
			return *this;
		}
		[[nodiscard]] inline constexpr bool operator>(const duration& other) const noexcept { return pm_Data > other.pm_Data; }
		[[nodiscard]] inline constexpr bool operator>=(const duration& other) const noexcept { return pm_Data >= other.pm_Data; }
		[[nodiscard]] inline constexpr bool operator<(const duration& other) const noexcept { return pm_Data < other.pm_Data; }
		[[nodiscard]] inline constexpr bool operator<=(const duration& other) const noexcept { return pm_Data <= other.pm_Data; }
		[[nodiscard]] inline constexpr bool operator==(const duration& other) const noexcept { return pm_Data == other.pm_Data; }
		[[nodiscard]] inline constexpr bool operator!=(const duration& other) const noexcept { return pm_Data != other.pm_Data; }

		template<typename DurationType>
		inline constexpr duration& operator=(const DurationType& other) { pm_Data = T(other); return *this; }

		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float, std::ratio<60 * 60, 1>>>() const noexcept
		{
			return duration<std::chrono::duration<float, std::ratio<60 * 60, 1>>>(pm_Data);
		}
		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float, std::ratio<60, 1>>>() const noexcept
		{
			return duration<std::chrono::duration<float, std::ratio<60, 1>>>(pm_Data);
		}
		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float>>() const noexcept
		{
			return duration<std::chrono::duration<float>>(pm_Data);
		}
		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float, std::ratio<1, 1000>>>() const noexcept
		{
			return duration<std::chrono::duration<float, std::ratio<1, 1000>>>(pm_Data);
		}
		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float, std::ratio<1, 1000 * 1000>>>() const noexcept
		{
			return duration<std::chrono::duration<float, std::ratio<1, 1000 * 1000>>>(pm_Data);
		}
		[[nodiscard]] inline constexpr operator duration<std::chrono::duration<float, std::ratio<1, 1000 * 1000 * 1000>>>() const noexcept
		{
			return duration<std::chrono::duration<float, std::ratio<1, 1000 * 1000 * 1000>>>(pm_Data);
		}
		[[nodiscard]] inline constexpr static duration zero() noexcept { return duration(0); }

		
	private:
		T pm_Data;
	};


	using hours = duration<std::chrono::duration<float, std::ratio<60 * 60, 1>>>;
	using minutes = duration<std::chrono::duration<float, std::ratio<60, 1>>>;
	using seconds = duration<std::chrono::duration<float>>;
	using milliseconds = duration<std::chrono::duration<float, std::milli>>;
	using microseconds = duration<std::chrono::duration<float, std::micro>>;
	using nanoseconds = duration<std::chrono::duration<float, std::nano>>;
	

	namespace detail
	{
		template<typename DurationType>
		class zx__impl_DurationAbbrv;

		template<>
		class zx__impl_DurationAbbrv<hours>
		{
		public:
			inline static const std::string value = "h";
		};
		template<>
		class zx__impl_DurationAbbrv<minutes>
		{
		public:
			inline static const std::string value = "m";
		};
		template<>
		class zx__impl_DurationAbbrv<seconds>
		{
		public:
			inline static const std::string value = "s";
		};
		template<>
		class zx__impl_DurationAbbrv<milliseconds>
		{
		public:
			inline static const std::string value = "ms";
		};
		template<>
		class zx__impl_DurationAbbrv<microseconds>
		{
		public:
			inline static const std::string value = "us";
		};
		template<>
		class zx__impl_DurationAbbrv<nanoseconds>
		{
		public:
			inline static const std::string value = "ns";
		};
	}

	template<typename DurationType>
	std::string durationAbbrv = detail::zx__impl_DurationAbbrv<DurationType>::value;

	struct timestep
	{
		[[nodiscard]] inline constexpr timestep(seconds time = zx::seconds(0)) noexcept 
			: pm_Step(time) {}
		template<typename DurationType>
		[[nodiscard]] inline constexpr timestep(const DurationType& copy) 
			: pm_Step(copy) {}

		[[nodiscard]] constexpr float seconds() const noexcept { return pm_Step.count(); }
		[[nodiscard]] constexpr float miliseconds() const noexcept { return zx::milliseconds(pm_Step).count(); }
		[[nodiscard]] constexpr float fps() const noexcept { return 1.0f / pm_Step.count(); }

		[[nodiscard]] constexpr zx::seconds operator+(zx::seconds other) const noexcept { return pm_Step + other; }
		[[nodiscard]] constexpr zx::seconds operator-(zx::seconds other) const noexcept { return pm_Step - other; }
		[[nodiscard]] constexpr zx::seconds operator*(float other) const noexcept { return pm_Step * other; }
		[[nodiscard]] constexpr zx::seconds operator/(float other) const noexcept { return pm_Step / other; }

		template<typename DurationType>
		[[nodiscard]] constexpr inline operator DurationType() const noexcept { return pm_Step; }

		[[nodiscard]] constexpr inline operator hours() const noexcept { return pm_Step; }
		[[nodiscard]] constexpr inline operator minutes() const noexcept { return pm_Step; }
		[[nodiscard]] constexpr inline operator zx::seconds() const noexcept { return pm_Step; }
		[[nodiscard]] constexpr inline operator zx::milliseconds() const noexcept { return pm_Step; }
		[[nodiscard]] constexpr inline operator zx::nanoseconds() const noexcept { return pm_Step; }
		[[nodiscard]] constexpr inline operator float() const noexcept { return pm_Step.count(); }
		
	private:
		zx::seconds pm_Step;


		friend class time;
	};

	class time
	{
	public:
		[[nodiscard]] inline static timepoint now() noexcept
		{
			return std::chrono::system_clock::now();
		}
		[[nodiscard]] inline static const timestep& delta() noexcept { return ps_DeltaTime; }
		[[nodiscard]] inline static const timestep& fixed() noexcept { return ps_FixedDelta; }
	private:
		friend class application;

		inline static timepoint ps_LastTime;
		inline static seconds ps_FrameTime;
		inline static timestep ps_DeltaTime;
		inline static timestep ps_FixedDelta = timestep(seconds(1.0f / 60.0f));

		inline static void update() noexcept
		{
			timepoint n = now();

			ps_FrameTime = n - ps_LastTime;
			ps_LastTime = n;
			ps_DeltaTime = ps_FrameTime;
		}


		class timer
		{
		public:
			[[nodiscard]] inline timer() noexcept
				: pm_Elasped(), pm_Length(),
				pm_Running(false), pm_Paused(true), pm_Loop(false), pm_Tick(false)
			{}
			[[nodiscard]] inline timer(seconds length, bool loop) noexcept
				: pm_Elasped(0), pm_Length(length),
				pm_Running(false), pm_Paused(true), pm_Loop(loop), pm_Tick(false)
			{}

			[[nodiscard]] inline bool is_running() noexcept { return pm_Running; }
			[[nodiscard]] inline bool is_paused() noexcept { return pm_Paused; }

			[[nodiscard]] inline bool loop_timer() const noexcept { return pm_Loop; }
			inline bool& loop_timer() noexcept { return pm_Loop; }


			[[nodiscard]] inline bool tick() const noexcept { return pm_Tick; }

			void start() noexcept
			{
				if (!pm_Running)
				{
					pm_Running = true;
					pm_Elasped = seconds(0);
				}
				pm_Paused = false;
			}
			void pause() noexcept
			{
				pm_Paused = true;
			}
			void stop() noexcept
			{
				pm_Running = false;
				pm_Paused = true;
			}
			void update() noexcept
			{
				if (pm_Tick)
					pm_Tick = false;

				if (pm_Running && !pm_Paused)
				{
					pm_Elasped += time::delta();
					if (pm_Elasped >= pm_Length)
					{
						pm_Tick = true;
						if (!pm_Loop)
							pm_Running = false;
						else
							pm_Elasped -= pm_Length;
					}
				}
			}
		private:
			seconds pm_Elasped;
			seconds pm_Length;

			bool pm_Running;
			bool pm_Paused;
			bool pm_Loop;
			bool pm_Tick;
		};

		struct stopwatch
		{
			const timepoint start;
			[[nodiscard]] inline stopwatch() noexcept : start(time::now()) {}

			[[nodiscard]] inline seconds get() const noexcept
			{
				return seconds(time::now() - start);
			}
		};

		
	};
}