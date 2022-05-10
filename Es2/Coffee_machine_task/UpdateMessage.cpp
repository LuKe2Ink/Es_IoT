#include "UpdateMessage.h"
#include "Arduino.h"

UpdateMessage::UpdateMessage(int coffee, int tea, int chocolate, int checks, String stato){

    this->coffeeMsg = coffee;
    this->teaMsg = tea;
    this->chocolateMsg = chocolate;
    this->checks = checks;
    this->statoMsg = stato;

}

void UpdateMessage::setMessage(int coffee, int tea, int chocolate, int checks, String stato){
    this->coffeeMsg = coffee;
    this->teaMsg = tea;
    this->chocolateMsg = chocolate;
    this->checks = checks;
    this->statoMsg = stato;
}

String UpdateMessage::toJson(){
    String json = "";
    json = json + "{'coffee':"+this->coffeeMsg+",'tea': "+this->teaMsg+",'chocolate': "+this->chocolateMsg+ ", 'check': " + this->checks +", 'stato': '"+this->statoMsg+"'}";
    return json;
}
