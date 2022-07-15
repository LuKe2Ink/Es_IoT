#include "BChannel.h"


BChannel::BChannel(int RX, int TX){
    SoftwareSerial btChannel(RX, TX);
}
bool BChannel::isAvailable(){
    
}
String BChannel::readString(){}
