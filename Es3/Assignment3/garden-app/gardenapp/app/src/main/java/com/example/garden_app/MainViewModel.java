package com.example.garden_app;

import androidx.lifecycle.ViewModel;

public class MainViewModel extends ViewModel {

    private final static int MAX_BRIGHTNESS = 4;
    private final static int MIN_BRIGHTNESS = 0;
    private final static int MAX_SPEED = 5;
    private final static int MIN_SPEED = 1;

    private int led3value;
    private int led4value;
    private int irrigationValue;

    public int getLed3value() {
        return led3value;
    }

    public int getLed4value() {
        return led4value;
    }

    public int getIrrigationValue() {
        return irrigationValue;
    }

    public void init(int led3value, int led4value, int irrigationValue) {
        this.led3value = led3value;
        this.led4value = led4value;
        this.irrigationValue = irrigationValue;
    }

    public int incLed3(){
        if(led3value<MAX_BRIGHTNESS){
            led3value++;
        }
        return led3value;
    }

    public int decLed3(){
        if(led3value>MIN_BRIGHTNESS){
            led3value--;
        }
        return led3value;
    }
    public int incLed4(){
        if(led4value<MAX_BRIGHTNESS){
            led4value++;
        }
        return led4value;

    }

    public int decLed4(){
        if(led4value>MIN_BRIGHTNESS){
            led4value--;
        }
        return led4value;
    }

    public int incIrr(){
        if(irrigationValue<MAX_SPEED) irrigationValue++;
        return irrigationValue;
    }

    public int decIrr(){
        if(irrigationValue>MIN_SPEED) irrigationValue--;
        return irrigationValue;
    }

}
