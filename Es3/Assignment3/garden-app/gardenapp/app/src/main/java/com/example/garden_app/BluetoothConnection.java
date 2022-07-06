package com.example.garden_app;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.UUID;

public class BluetoothConnection {
    private final String address;
    private final BluetoothAdapter adapter;
    private BluetoothSocket socket;
    private InputStream inputStream;
    private OutputStream outputStream;
    private final UUID serialPortUUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    private final int bufferSize = 4096;
    byte[] rxBuffer;

    public BluetoothConnection(String address, int timeout) throws RuntimeException {
        this.address = address;
        adapter = BluetoothAdapter.getDefaultAdapter();

        if (adapter == null)
            throw new RuntimeException("Bluetooth not supported");

        adapter.cancelDiscovery();
        rxBuffer = new byte[bufferSize];
    }

    public boolean isOpen() {
        return socket != null;
    }

    public boolean open() throws Exception {
        Log.d("BluetoothConnection", "opening connection...");
        BluetoothDevice device = adapter.getRemoteDevice(address.toUpperCase());
        socket = device.createRfcommSocketToServiceRecord(serialPortUUID);
        try {
            socket.connect();
        } catch (Exception e) {
            socket = null;
            throw e;
        }
        inputStream = socket.getInputStream();
        outputStream = socket.getOutputStream();
        Log.d("BluetoothConnection", "connection opened");
        return true;
    }

    public boolean close() throws Exception {
        Log.d("BluetoothConnection", "closing connection...");
        inputStream = null;
        outputStream = null;
        socket.close();
        socket = null;
        Log.d("BluetoothConnection", "connection closed");
        return true;
    }

    public int send(byte[] buffer) throws IOException {
        Log.d("BluetoothConnection", String.format("sending %d bytes...", buffer.length));
        outputStream.write(buffer);
        Log.d("BluetoothConnection", "data sent");
        return buffer.length;
    }

    public byte[] receive(int bytesToRead) throws IOException {
        Log.d("BluetoothConnection", String.format("receiving %d bytes...", bytesToRead));
        int readBytes = inputStream.read(rxBuffer, 0, Math.min(bytesToRead, bufferSize));
        Log.d("BluetoothConnection", String.format("received %d bytes", bytesToRead));
        return Arrays.copyOfRange(rxBuffer, 0, readBytes);
    }
}
