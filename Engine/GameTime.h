#pragma once
#include <cstdint>
namespace nu {
	class Time {

	public:
		Time();

		void Reset();
		void Tick();

		float GetTime() const { return TicksToSeconds(m_currentTicks - m_startTicks); }
		float GetDeltaTime() const { return TicksToSeconds(m_deltaTicks); }

		float TicksToSeconds(uint64_t ticks) const { return (float)ticks / 1'000'000'000; }


	private:
		uint64_t m_startTicks = 0;
		uint64_t m_currentTicks = 0;
		uint64_t m_frameTicks = 0;
		uint64_t m_deltaTicks = 0;
	};


}