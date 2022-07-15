#ifndef __BCHANNEL__
#define __BCHANNEL__

#include <SoftwareSerial.h>


class BChannel{
    public:
        BChannel(int RX, int TX);
        bool isAvailable();
        String readString();
};

#endif
