/*
	Standalone version of the Time and Clock classes from SFML
	http://http://www.sfml-dev.org
*/

#ifndef MTIME_HPP
#define MTIME_HPP

#include <stdint.h>

/// time class and operator
class MTime
{
    public:
        MTime();
        static const MTime Zero;

        /// conversion
        float to_s() const;
        int32_t to_ms() const;
        int64_t to_us() const;

        static MTime s2time(float s);
        static MTime ms2time(int32_t ms);
        static MTime us2time(int64_t us);
    private:
        explicit MTime(int64_t us);
        int64_t m_us;
};

bool operator ==(MTime left, MTime right);
bool operator !=(MTime left, MTime right);
bool operator <(MTime left, MTime right);
bool operator >(MTime left, MTime right);
bool operator <=(MTime left, MTime right);
bool operator >=(MTime left, MTime right);
MTime operator -(MTime right);
MTime operator +(MTime left, MTime right);
MTime& operator +=(MTime& left, MTime right);
MTime operator -(MTime left, MTime right);
MTime& operator -=(MTime& left, MTime right);
MTime operator *(MTime left, float right);
MTime operator *(MTime left, int64_t right);
MTime operator *(float left, MTime right);
MTime operator *(int64_t left, MTime right);
MTime& operator *=(MTime& left, float right);
MTime& operator *=(MTime& left, int64_t right);
MTime operator /(MTime left, float right);
MTime operator /(MTime left, int64_t right);
MTime& operator /=(MTime& left, float right);
MTime& operator /=(MTime& left, int64_t right);
float operator /(MTime left, MTime right);
MTime operator %(MTime left, MTime right);
MTime& operator %=(MTime& left, MTime right);

/// clock class
class MClock
{
    public:
        MClock();
        MTime get() const;
        MTime reset();
    private:
        MTime t;
};

#endif // MMTime_HPP
