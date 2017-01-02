/*
	Standalone version of the Time and Clock classes from SFML
	http://http://www.sfml-dev.org
*/

#include "mtime.hpp"

#define WINDOWS
//#define LINUX
//#define MAC

/// general functions
#if defined(WINDOWS)
#include <windows.h>
LARGE_INTEGER _getF_() // used for initialization only
{
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return f;
}

MTime getNow()
{
    HANDLE cThread = GetCurrentThread();
    DWORD_PTR pMask = SetThreadAffinityMask(cThread, 1);

    static LARGE_INTEGER f = _getF_(); // constant

    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    SetThreadAffinityMask(cThread, pMask);
    return MTime::us2time(1000000 * t.QuadPart / f.QuadPart);
}
#elif defined(LINUX)
#include <time.h>
MTime getNow() // need testing
{
    // POSIX implementation
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return MTime::us2time(static_cast<int64_t>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);
}
#elif defined(MAC)
#include <mach/mach_time.h>
MTime getNow() // need testing
{
    // Mac OS X implementation
    static mach_timebase_info_data_t frequency = {0, 0};
    if(frequency.denom == 0) mach_timebase_info(&frequency);
    int64_t nanoseconds = mach_absolute_time() * frequency.numer / frequency.denom;
    return MTime::us2time(nanoseconds / 1000);
}
#endif


/// time functions
const MTime MTime::Zero;

MTime::MTime(): m_us(0){}

float MTime::to_s() const
{
    return m_us / 1000000.f;
}

int32_t MTime::to_ms() const
{
    return static_cast<int32_t>(m_us / 1000);
}

int64_t MTime::to_us() const
{
    return m_us;
}

MTime::MTime(int64_t us): m_us(us){}

MTime MTime::s2time(float amount)
{
    return MTime(static_cast<int64_t>(amount * 1000000));
}

MTime MTime::ms2time(int32_t amount)
{
    return MTime(static_cast<int64_t>(amount) * 1000);
}

MTime MTime::us2time(int64_t amount)
{
    return MTime(amount);
}

bool operator ==(MTime left, MTime right)
{
    return left.to_us() == right.to_us();
}

bool operator !=(MTime left, MTime right)
{
    return left.to_us() != right.to_us();
}

bool operator <(MTime left, MTime right)
{
    return left.to_us() < right.to_us();
}

bool operator >(MTime left, MTime right)
{
    return left.to_us() > right.to_us();
}

bool operator <=(MTime left, MTime right)
{
    return left.to_us() <= right.to_us();
}

bool operator >=(MTime left, MTime right)
{
    return left.to_us() >= right.to_us();
}

MTime operator -(MTime right)
{
    return MTime::us2time(-right.to_us());
}

MTime operator +(MTime left, MTime right)
{
    return MTime::us2time(left.to_us() + right.to_us());
}

MTime& operator +=(MTime& left, MTime right)
{
    return left = left + right;
}

MTime operator -(MTime left, MTime right)
{
    return MTime::us2time(left.to_us() - right.to_us());
}

MTime& operator -=(MTime& left, MTime right)
{
    return left = left - right;
}

MTime operator *(MTime left, float right)
{
    return MTime::s2time(left.to_s() * right);
}

MTime operator *(MTime left, int64_t right)
{
    return MTime::us2time(left.to_us() * right);
}

MTime operator *(float left, MTime right)
{
    return right * left;
}

MTime operator *(int64_t left, MTime right)
{
    return right * left;
}

MTime& operator *=(MTime& left, float right)
{
    return left = left * right;
}

MTime& operator *=(MTime& left, int64_t right)
{
    return left = left * right;
}

MTime operator /(MTime left, float right)
{
    return MTime::s2time(left.to_s() / right);
}

MTime operator /(MTime left, int64_t right)
{
    return MTime::us2time(left.to_us() / right);
}

MTime& operator /=(MTime& left, float right)
{
    return left = left / right;
}

MTime& operator /=(MTime& left, int64_t right)
{
    return left = left / right;
}

float operator /(MTime left, MTime right)
{
    return left.to_s() / right.to_s();
}

MTime operator %(MTime left, MTime right)
{
    return MTime::us2time(left.to_us() % right.to_us());
}

MTime& operator %=(MTime& left, MTime right)
{
    return left = left % right;
}

/// clock functions
MClock::MClock(): t(getNow()) {}

MTime MClock::get() const
{
    return getNow() - t;
}

MTime MClock::reset()
{
    MTime now = getNow();
    MTime elapsed = now - t;
    t = now;
    return elapsed;
}
