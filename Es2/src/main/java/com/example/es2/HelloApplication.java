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
        stage.show();

        System.out.println("Welcome");
        new Timer().scheduleAtFixedRate(new TimerTask(){

            @Override
            public void run(){
                System.out.println("A Kiss every 5 seconds");
            }
        },0,1000);

        GUIController guiController = (GUIController) fxmlLoader.getController();
        guiController.message();

    }



    public static void main(String[] args) throws Exception {
        launch();
    }
}