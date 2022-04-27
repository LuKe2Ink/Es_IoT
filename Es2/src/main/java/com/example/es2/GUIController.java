package com.example.es2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class GUIController {

    private static final String N_MAX_PRODUCT = "50";

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


    @FXML
    protected void refillClicked() {
        coffeeQuantity.setText(N_MAX_PRODUCT);
        chocolateQuantity.setText(N_MAX_PRODUCT);
        teaQuantity.setText(N_MAX_PRODUCT);
    }

    @FXML
    protected void recoverClicked() {
        state.setText("Dropping");
    }

}
