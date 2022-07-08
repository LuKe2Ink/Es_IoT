package com.example.garden_app;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import java.util.Set;

public class ConnectionActivity extends AppCompatActivity {

    private BluetoothAdapter bluetoothAdapter;
    ListView bluetoothDeviceList;
    Button reloadDevicesButton;
    private final static int REQUEST_ENABLE_BT = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connection);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        bluetoothDeviceList = findViewById(R.id.device_list);
        reloadDevicesButton = findViewById(R.id.reload_device_list);

        bluetoothDeviceList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapter, final View view, int position, long id) {
                final BluetoothDevice device = (BluetoothDevice) adapter.getItemAtPosition(position);
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                intent.putExtra("device", device);
                startActivity(intent);
            }
        });

        updateUI();
        loadPairedDevices();
    }

    public void switchBluetooth(View v) {
        if (bluetoothAdapter.isEnabled()) {
            bluetoothAdapter.disable();
            bluetoothDeviceList.setAdapter(null);
            reloadDevicesButton.setEnabled(false);
        } else {
            Intent turnBluetoothOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnBluetoothOn, REQUEST_ENABLE_BT);
        }
    }

    public void showPairedDevices(View v) {
        loadPairedDevices();
    }

    protected void loadPairedDevices() {
        Set<BluetoothDevice> devices = bluetoothAdapter.getBondedDevices();

        BluetoothDevice[] deviceArray = devices.toArray(new BluetoothDevice[devices.size()]);
        BluetoothDeviceAdapter adapter = new BluetoothDeviceAdapter(this, R.id.device_list, deviceArray);
        bluetoothDeviceList.setAdapter(adapter);
    }

    protected void updateUI() {
        if (bluetoothAdapter.isEnabled()) {
            reloadDevicesButton.setEnabled(true);
        } else {
            reloadDevicesButton.setEnabled(false);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode == RESULT_OK) {
                loadPairedDevices();
                updateUI();
            }
        }
    }
}