package com.example.garden_app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.lifecycle.ViewModelProvider;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URI;
import java.net.URL;
import java.net.URLConnection;
import java.util.Set;
import java.util.Timer;
import java.util.TimerTask;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Headers;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

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
    TextView irrValue;
    ImageView alarm;
    MainViewModel viewModel;
    private BluetoothConnection connection;
    private boolean manualMode = false;

    private JSONObject json;

    private String prevState;
    private int prevIrrValue;

//    private final OkHttpClient client = new OkHttpClient();

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
                System.out.println("Open");
                manualControl();
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
        irrValue = findViewById(R.id.irr_value);
        alarm = findViewById(R.id.alarm);
        req_man_contr = findViewById(R.id.req_man_contr);


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

        alarm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String state = "";
                try {
                    state = json.getString("state");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                if(state.contains("alarma")){
                    removeAlarm();
                }
            }
        });

//        System.setProperty("javax.net.ssl.debug", "all");
//            AsyncTask.execute(()->{
//                URL url;
//                try {
//                    url = new URL("https://192.168.43.101:3000/garden/app/getData");
//                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
//                    connection.setRequestMethod("GET");
//                    connection.setRequestProperty("Content-Type", "application/json");
//                    //System.out.println(connection.getResponseCode());
//                    System.out.println(connection.g);
//                } catch (MalformedURLException e) {
//                    e.printStackTrace();
//                } catch (ProtocolException e) {
//                    e.printStackTrace();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            });


//            Request request = new Request.Builder()
//                    .url("https://192.168.43.101:3000/garden/app/getData")
//                    .build();
//
//            client.newCall(request).enqueue(new Callback() {
//                @Override public void onFailure(Call call, IOException e) {
//                    e.printStackTrace();
//                }
//
//                @Override public void onResponse(Call call, Response response) throws IOException {
//                    try (ResponseBody responseBody = response.body()) {
//                        if (!response.isSuccessful()) throw new IOException("Unexpected code " + response);
//
//                        Headers responseHeaders = response.headers();
//                        for (int i = 0, size = responseHeaders.size(); i < size; i++) {
//                            System.out.println(responseHeaders.name(i) + ": " + responseHeaders.value(i));
//                        }
//
//                        System.out.println(responseBody.string());
//                    }
//                }
//            });


        AsyncTask.execute(()->{
            String stringa = executeRequest("http://localhost:3000/garden/app/getData", "");
//            String stringa = executePost("http://localhost:3000/garden/app/getData", "");
//            String stringa = executePost("https://182c-5-171-24-18.eu.ngrok.io/garden/app/getData", "");
            //System.out.println(stringa);
            try {
                json = new JSONObject(stringa);
                viewModel.init(json.getInt("led3"), json.getInt("led4"), json.getInt("water"));
                valueLed3.setText(String.valueOf(json.getInt("led3")));
                valueLed4.setText(String.valueOf(json.getInt("led4")));
                irrValue.setText(String.valueOf(json.getInt("water")));
            } catch (JSONException e) {
                e.printStackTrace();
            }
        });

        setEnabled();
        getUpdate();
    }
    public static String executeRequest(String targetURL, String urlParameters) {
        HttpURLConnection connection = null;

        try {
            //Create connection
            URL url = new URL(targetURL);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("Content-Type",
                    "application/json");

//            //Send request
//            DataOutputStream wr = new DataOutputStream (
//                    connection.getOutputStream());
//            wr.writeBytes(urlParameters);
//            wr.close();

            //Get Response
            InputStream is = connection.getInputStream();
            BufferedReader rd = new BufferedReader(new InputStreamReader(is));
            StringBuilder response = new StringBuilder(); // or StringBuffer if Java version 5+
            String line;
            while ((line = rd.readLine()) != null) {
                response.append(line);
                response.append('\r');
            }
            rd.close();
            return response.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        } finally {
            if (connection != null) {
                connection.disconnect();
            }
        }
    }

    public void getUpdate(){
        new Timer().scheduleAtFixedRate(new TimerTask(){
            @Override
            public void run(){
                AsyncTask.execute(()->{
                    String stringa = executeRequest("http://localhost:3000/garden/app/getData", "");
                    try {
                        JSONObject  j = new JSONObject(stringa);
                        String state = j.getString("state");
                        if(state.contains("alarm")){
                            prevIrrValue = json.getInt("water");
                            prevState = json.getString("state");
                            manualMode = false;
                            setEnabled();
                        }
                        json = j;
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                });
            }
        },0,300);
    }

    public void removeAlarm(){
        try {
            json.put("state", prevState);
            json.put("water", prevIrrValue);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        if(prevState.contains("manual")){
            manualMode = true;
        } else {
            manualMode = false;
        }
        prevState = "";
        prevIrrValue = 0;
        setEnabled();
    }

    public void manualControl(){
        try {
            json.put("state", "manual");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        manualMode = true;
        setEnabled();
        send(json.toString());
    }

    public void led1(View v) {
        try {
            boolean led = (boolean) json.get("led1");
            json.put("led1", !led);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        System.out.println(json);
        send(json.toString());
    }

    public void led2(View v) {
        try {
            boolean led = (boolean) json.get("led2");
            json.put("led2", !led);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        System.out.println(json);
        send(json.toString());
    }

    public void led3(View v){
        switch (v.getId()){
            case R.id.led3_plus:
                valueLed3.setText(String.valueOf(viewModel.incLed3()));
                break;
            case R.id.led3_sot:
                valueLed3.setText(String.valueOf(viewModel.decLed3()));
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        try {
            json.put("led3", viewModel.getLed3value());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        System.out.println(json);
        send(json.toString());
    }

    public void led4(View v) {
        switch (v.getId()){
            case R.id.led4_plus:
                valueLed4.setText(String.valueOf(viewModel.incLed4()));
                break;
            case R.id.led4_sot:
                valueLed4.setText(String.valueOf(viewModel.decLed4()));
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        try {
            json.put("led4", viewModel.getLed4value());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        System.out.println(json);
        send(json.toString());
    }

    public void irrigation(View v){
        String op;
        switch (v.getId()){
            case R.id.irr_open_close:
                op = "change";
                break;
            case R.id.irr_add:
                viewModel.incIrr();
                op = String.valueOf(viewModel.getIrrigationValue());
                irrValue.setText(op);
                break;
            case R.id.irr_sot:
                viewModel.decIrr();
                op = String.valueOf(viewModel.getIrrigationValue());
                irrValue.setText(op);
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + v.getId());
        }
        op = String.valueOf(viewModel.getIrrigationValue());
        irrValue.setText(op);

        try {
            json.put("water", viewModel.getIrrigationValue());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        System.out.println(json);
        send(json.toString());
    }

    private void send(String command) {
        try{
            connection.send(command.getBytes());
        } catch (Exception e) {

        }
    }

    private void setEnabled(){
        led1.setEnabled(manualMode);
        led2.setEnabled(manualMode);

        led3plus.setEnabled(manualMode);
        led3sot.setEnabled(manualMode);
        led4plus.setEnabled(manualMode);
        led4sot.setEnabled(manualMode);

    }
}