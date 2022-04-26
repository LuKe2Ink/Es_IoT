package com.example.es2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import jssc.*;

import java.io.IOException;

public class HelloApplication extends Application {

    private static final int WIDTH = 1200;
    private static final int HEIGHT = 800;

    private CoffeeMachineManager coffeeMachineManager;

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("GUI_Assign_2.fxml"));
        Scene scene = new Scene(fxmlLoader.load(),  WIDTH, HEIGHT);
        stage.setTitle("Coffee Machine");

        stage.setScene(scene);
        stage.show();

        System.out.println("Welcome");

        coffeeMachineManager = new CoffeeMachineManager();
    }



    public static void main(String[] args) {
        launch();

    }
}