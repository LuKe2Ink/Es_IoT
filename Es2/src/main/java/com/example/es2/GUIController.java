package com.example.es2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import org.json.JSONObject;


public class GUIController {

    private static final String N_MAX_PRODUCT = "50";

    private static final String PORT = "COM7";
    private static final int RATE = 9600;

    public CommChannel commChannel;

    @FXML
    public Label state;

    @FXML
    public Label coffeeQuantity;

    @FXML
    public Label teaQuantity;

    @FXML
    public Label chocolateQuantity;

    @FXML
    public Label numberSelfTest;

    int coffee = 0, tea = 0, chocolate = 0, check = 0;
    String stato = null;

    public GUIController() throws Exception {
        this.commChannel = new SerialCommChannel(PORT, RATE);
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        //this.updateClicked();
//        JSONObject json = null;
//        boolean keepReading = true;
//        while (keepReading) {
//            String msg = this.commChannel.receiveMsg();
//            msg.replace("/.*{/", "");
//            if(msg.contains("{")){
//                json = new JSONObject(msg);
//                keepReading = false;
//            }
//            //msg.replaceAll("/.*{/", "");
//            //System.out.println(msg);
//        }
//        System.out.println(json);


//
//        System.out.println(json.getInt("coffee"));
//        int coffee = json.getInt("coffee");
//        coffeeQuantity.setText(String.valueOf(coffee));
//        int chocolate = json.getInt("chocolate");
//        chocolateQuantity.setText(String.valueOf(chocolate));
//        int tea = json.getInt("tea");
//        teaQuantity.setText(String.valueOf(tea));
    }


    @FXML
    protected void refillClicked() throws InterruptedException {
        boolean msgReceived = false;

//        System.out.println("coffeeQuantity = " + coffeeQuantity);
//        System.out.println("teaQuantity = " + teaQuantity);
//        System.out.println("chocolateQuantity = " + chocolateQuantity);

//
//        coffeeQuantity.setText(N_MAX_PRODUCT);
//        chocolateQuantity.setText(N_MAX_PRODUCT);
//        teaQuantity.setText(N_MAX_PRODUCT);

        System.out.println("Sending refill");
        commChannel.sendMsg("refill");
    }

    @FXML
    protected void recoverClicked() {
        state.setText("Dropping");
        commChannel.sendMsg("recover");
    }

    @FXML
    public void updateClicked() throws InterruptedException {
        while(true){
            message();
        }
    }

    public void message() throws InterruptedException {
        JSONObject json = null;
        //boolean keepReading = true;
        //while (keepReading) {
        String msg = this.commChannel.receiveMsg();
        System.out.println(msg);
        //String msg1 = msg.substring(msg.indexOf("{") + 1);
        //msg1.trim();
        msg.replace("/.*{/", "");
        if(msg.contains("{")){
            System.out.println("Found a JSON");
            json = new JSONObject(msg);
            //keepReading = false;
            System.out.println(json);

        coffee = json.getInt("coffee");
//            coffeeQuantity.setText(String.valueOf(json.getInt("coffee")));
        chocolate = json.getInt("chocolate");
//            chocolateQuantity.setText(String.valueOf(json.getInt("chocolate")));
        tea = json.getInt("tea");
//            teaQuantity.setText(String.valueOf(json.getInt("tea")));
        check = json.getInt("check");

        stato = json.getString("stato");
            // Avoids running on the different thread of the GUI, so he can update it async
            Platform.runLater(() -> {
                updateGui(coffee, tea, chocolate, check,stato);

            });

        }

    }

    public void updateGui(int coffee, int tea, int chocolate, int check, String stato){
        teaQuantity.setText(String.valueOf(tea));
        chocolateQuantity.setText(String.valueOf(chocolate));
        coffeeQuantity.setText(String.valueOf(coffee));
        numberSelfTest.setText(String.valueOf(check));
        state.setText(stato);
    }

}
