package com.example.es2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class GUIController {

    private static final String N_MAX_PRODUCT = "50";

    private static final String PORT = "COM3";
    private static final int RATE = 9600;

    private CommChannel commChannel;

    @FXML
    private Label state;

    @FXML
    private Label coffeeQuantity;

    @FXML
    private Label teaQuantity;

    @FXML
    private Label chocolateQuantity;

    @FXML
    private Label numberSelfTest;

    public GUIController() throws Exception {
        this.commChannel = new SerialCommChannel(PORT, RATE);
    }


    @FXML
    protected void refillClicked() throws InterruptedException {
        boolean msgReceived = false;

        coffeeQuantity.setText(N_MAX_PRODUCT);
        chocolateQuantity.setText(N_MAX_PRODUCT);
        teaQuantity.setText(N_MAX_PRODUCT);

        System.out.println("Sending refill");
        commChannel.sendMsg("refill");
    }

    @FXML
    protected void recoverClicked() {
        state.setText("Dropping");
    }

}
