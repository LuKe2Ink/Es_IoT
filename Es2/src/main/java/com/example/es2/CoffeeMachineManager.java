package com.example.es2;

public class CoffeeMachineManager {

    private static final String PORT = "COM3";
    private static final int RATE = 9600;

    private CommChannel commChannel;

    public CoffeeMachineManager() throws Exception {
        startCommunication();
    }

    private void startCommunication() throws Exception {
        commChannel = new SerialCommChannel(PORT, RATE);
    }
}
