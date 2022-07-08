package com.example.garden_app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.lifecycle.ViewModelProvider;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Set;

public class MainActivity extends AppCompatActivity {
    Button led1;
    Button led2;
    Button led3plus;
    Button led3sot;
    Button led4plus;
    Button led4sot;
    Button req_man_contr;
    Button irrigation_change;
    Button irrPlus;
    Button irrSot;
    TextView valueLed3;
    TextView valueLed4;
    MainViewModel viewModel;
    private BluetoothConnection connection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent intent = getIntent();
        if(intent.hasExtra("device")){
            BluetoothDevice device = intent.getExtras().getParcelable("device");
            try {
                connection = new BluetoothConnection(device.getAddress(), 3000);
                connection.open();
            } catch (Exception e) {

            }
        }

        viewModel = new ViewModelProvider(this).get(MainViewModel.class);

        led1 = findViewById(R.id.led1_on_off);
        led2 = findViewById(R.id.led2_on_off);
        led3plus = findViewById(R.id.led3_plus);
        led3sot = findViewById(R.id.led3_sot);
        led4plus = findViewById(R.id.led4_plus);
        led4sot = findViewById(R.id.led4_sot);
        valueLed3 = findViewById(R.id.value_led3);
        valueLed4 = findViewById(R.id.value_led4);
        irrigation_change = findViewById(R.id.irr_open_close);
        irrPlus = findViewById(R.id.irr_add);
        irrSot = findViewById(R.id.irr_sot);
        req_man_contr = findViewById(R.id.req_man_contr);

        viewModel.init(Integer.parseInt(valueLed3.getText().toString()), Integer.parseInt(valueLed4.getText().toString()), 0);

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

        irrigation_change.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                irrigation(view);
            }
        });

        irrPlus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                irrigation(view);
            }
        });

        irrSot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                irrigation(view);
            }
        });

        req_man_contr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent1 = new Intent(getApplicationContext(), ConnectionActivity.class);
                startActivity(intent1);
                finish();
            }
        });
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
                valueLed3.setText(String.valueOf(viewModel.incLed3()));
                op = "inc";
                break;
            case R.id.led3_sot:
                valueLed3.setText(String.valueOf(viewModel.decLed3()));
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
                valueLed4.setText(String.valueOf(viewModel.incLed4()));
                op = "inc";
                break;
            case R.id.led4_sot:
                valueLed4.setText(String.valueOf(viewModel.decLed4()));
                op = "dec";
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        String json = "{\"led4\":\""+op+"\"}";
        System.out.println(json);
        send(json);
    }

    public void irrigation(View v){
        String op;
        switch (v.getId()){
            case R.id.irr_open_close:
                op = "change";
                break;
            case R.id.irr_add:
                op = "inc";
                break;
            case R.id.irr_sot:
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