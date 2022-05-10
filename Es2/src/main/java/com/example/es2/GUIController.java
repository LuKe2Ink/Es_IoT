package com.example.es2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import org.json.JSONObject;


public class GUIController {

    private static final String N_MAX_PRODUCT = "50";

    private static final String PORT = "COM6";
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

        System.out.println("coffeeQuantity = " + coffeeQuantity);
        System.out.println("teaQuantity = " + teaQuantity);
        System.out.println("chocolateQuantity = " + chocolateQuantity);


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
        msg.replace("/.*{/", "");
        if(msg.contains("{")){
            json = new JSONObject(msg);
            //keepReading = false;
        }
        //msg.replaceAll("/.*{/", "");
        //System.out.println(msg);
        //}
        System.out.println(json);

        coffeeQuantity.setText(String.valueOf(json.getInt("coffee")));
//        int chocolate = json.getInt("chocolate");
        chocolateQuantity.setText(String.valueOf(json.getInt("chocolate")));
//        int tea = json.getInt("tea");
        teaQuantity.setText(String.valueOf(json.getInt("tea")));
    }
}
