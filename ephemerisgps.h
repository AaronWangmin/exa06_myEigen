#ifndef EPHEMERISGPS_H
#define EPHEMERISGPS_H

// the two files(.h, .cpp) do not work now.
// implemented by the two class: Rinex2.11, RTCM32

#include "gpshead.h"


class EphemerisGPS
{
public:
    EphemerisGPS();
    void fromRTCM();        // get gps ephemeris from rtcm stream.
    void fromRinex();       // get gps ephemeris from rinex file.

private:
    eph_t ephGPS;
};

#endif // EPHEMERISGPS_H
