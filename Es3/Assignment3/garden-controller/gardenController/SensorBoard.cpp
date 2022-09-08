#include "SensorBoard.h"

SensorBoard::SensorBoard()
{
    this->photoresistor = new Photoresistor();
    this->temp = new Temp();
}
