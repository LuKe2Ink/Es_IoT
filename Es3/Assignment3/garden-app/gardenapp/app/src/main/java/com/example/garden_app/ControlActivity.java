package com.example.garden_app;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;

public class ControlActivity extends AppCompatActivity {

    Button led1;
    Button led2;
    Button led3plus;
    Button led3sot;
    Button led4plus;
    Button led4sot;
    private BluetoothConnection connection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        Intent intent = getIntent();
        BluetoothDevice device = intent.getExtras().getParcelable("device");

        led1 = findViewById(R.id.led1_on_off);
        led2 = findViewById(R.id.led2_on_off);
        led3plus = findViewById(R.id.led3_plus);
        led3sot = findViewById(R.id.led3_sot);
        led4plus = findViewById(R.id.led4_plus);
        led4sot = findViewById(R.id.led4_sot);

        led1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led1(view);
            }
        });

        led2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led2(view);
            }
        });

        led3plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led3(view);
            }
        });

        led3sot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led3(view);
            }
        });

        led4plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led4(view);
            }
        });

        led4sot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                led4(view);
            }
        });

        try {
            connection = new BluetoothConnection(device.getAddress(), 3000);
            connection.open();
        } catch (Exception e) {

        }
    }

    public void led1(View v) {
        String json = "{\"led1\":\"change\"}";
        System.out.println(json);
        send(json);
    }

    public void led2(View v) {
        String json = "{\"led2\":\"change\"}";
        System.out.println(json);
        send(json);
    }

    public void led3(View v) {
        String op;
        switch (v.getId()){
            case R.id.led3_plus:
                op = "inc";
                break;
            case R.id.led3_sot:
                op = "dec";
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        String json = "{\"led3\":\""+op+"\"}";
        System.out.println(json);
        send(json);
    }

    public void led4(View v) {
        String op;
        switch (v.getId()){
            case R.id.led4_plus:
                op = "inc";
                break;
            case R.id.led4_sot:
                op = "dec";
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        String json = "{\"led4\":\""+op+"\"}";
        System.out.println(json);
        send(json);
    }

    private void send(String command) {
        try{
            connection.send(command.getBytes());
        } catch (Exception e) {

        }
    }
}