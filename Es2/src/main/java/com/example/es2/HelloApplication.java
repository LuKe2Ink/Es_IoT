package com.example.es2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import jssc.*;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("GUI_Assign_2.fxml"));
        Scene scene = new Scene(fxmlLoader.load(),  1200, 800);
        stage.setTitle("Assignment 2!");

        System.out.println(SerialPortList.getPortNames() + " Michi no sa nemmeno pulirsi il culetto");

        for(String port : SerialPortList.getPortNames()) {
            System.out.println(port);
        }

        stage.setScene(scene);
        stage.show();



    }

    public static void main(String[] args) {
        launch();

    }
}