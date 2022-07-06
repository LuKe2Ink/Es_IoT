package com.example.garden_app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

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
import android.widget.Toast;

import java.util.Set;

public class MainActivity extends AppCompatActivity {
    private BluetoothAdapter bluetoothAdapter;
    ListView bluetoothDeviceList;
    Button reloadDevicesButton;
    Button bluetoothSwitchButton;
    private final static int REQUEST_ENABLE_BT = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        bluetoothDeviceList = findViewById(R.id.device_list);
        reloadDevicesButton = findViewById(R.id.reload_device_list);
        bluetoothSwitchButton = findViewById(R.id.bluetooth_switch);

        bluetoothDeviceList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapter, final View view, int position, long id) {
                final BluetoothDevice device = (BluetoothDevice) adapter.getItemAtPosition(position);
                Intent intent = new Intent(getApplicationContext(), ControlActivity.class);
                intent.putExtra("device", device);
                startActivity(intent);
            }
        });

        updateUI();
        loadPairedDevices();
    }

    public void switchBluetooth(View v) {
        if (bluetoothAdapter.isEnabled()) {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            bluetoothAdapter.disable();
            bluetoothDeviceList.setAdapter(null);
            reloadDevicesButton.setEnabled(false);
            bluetoothSwitchButton.setText(R.string.bluetooth_switch_on);
        } else {
            bluetoothSwitchButton.setEnabled(false);
            Intent turnBluetoothOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnBluetoothOn, REQUEST_ENABLE_BT);
        }
    }

    public void showPairedDevices(View v) {
        loadPairedDevices();
    }

    protected void loadPairedDevices() {
        Toast.makeText(this, "Load", Toast.LENGTH_SHORT).show();
        Set<BluetoothDevice> devices = bluetoothAdapter.getBondedDevices();

        BluetoothDevice[] deviceArray = devices.toArray(new BluetoothDevice[devices.size()]);
        BluetoothDeviceAdapter adapter = new BluetoothDeviceAdapter(this, R.id.device_list, deviceArray);
        bluetoothDeviceList.setAdapter(adapter);
    }

    protected void updateUI() {
        bluetoothSwitchButton.setEnabled(true);
        if (bluetoothAdapter.isEnabled()) {
            reloadDevicesButton.setEnabled(true);
            bluetoothSwitchButton.setText(R.string.bluetooth_switch_off);
        } else {
            reloadDevicesButton.setEnabled(false);
            bluetoothSwitchButton.setText(R.string.bluetooth_switch_on);
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