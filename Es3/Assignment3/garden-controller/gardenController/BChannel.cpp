#include "BChannel.h"


BChannel::BChannel(int RX, int TX){
    SoftwareSerial btChannel(RX, TX);
}
void BChannel::isAvailable(){
    
}
String BChannel::readString(){}