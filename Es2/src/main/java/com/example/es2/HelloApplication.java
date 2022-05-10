package com.example.es2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.Timer;
import java.util.TimerTask;

public class HelloApplication extends Application {

    private static final int WIDTH = 1200;
    private static final int HEIGHT = 800;


    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("GUI_Assign_2.fxml"));
        Scene scene = new Scene(fxmlLoader.load(),  WIDTH, HEIGHT);
        stage.setTitle("Coffee Machine");


        stage.setScene(scene);


        GUIController guiController = (GUIController) fxmlLoader.getController();

        try {
            guiController.message();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        new Timer().scheduleAtFixedRate(new TimerTask(){

            @Override
            public void run(){
                System.out.println("A Kiss every 1 seconds");
                try {
                    guiController.message();
                } catch (InterruptedException e) {

                    System.out.println("BAD LUCK");
                }
            }
        },0,300);

        stage.show();

//
//        Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), ev -> {
//
//            try {
//                    guiController.message();
//                } catch (InterruptedException e) {
//                    System.out.println("Not a lucky catch");
//                }
//
//        }));
//        timeline.setCycleCount(Animation.INDEFINITE);
//        timeline.play();

    }



    public static void main(String[] args) throws Exception {
        launch();
    }
}