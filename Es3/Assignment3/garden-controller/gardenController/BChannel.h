#ifndef __BCHANNEL__
#define __BCHANNEL__

#include <SoftwareSerial.h>


class BChannel{
    public:
        BChannel(int RX, int TX);
        void isAvailable();
        String readString();
};

#endif
