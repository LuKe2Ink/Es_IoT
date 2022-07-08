package com.example.garden_app;

import androidx.lifecycle.ViewModel;

public class MainViewModel extends ViewModel {

    private final static int MAX_BRIGHTNESS = 4;
    private final static int MIN_BRIGHTNESS = 0;

    private int led3value;
    private int led4value;
    private int irrigationValue;

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

}
