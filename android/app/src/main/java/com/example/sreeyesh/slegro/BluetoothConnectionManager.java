package com.example.sreeyesh.slegro;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public final class BluetoothConnectionManager {
    public enum BluetoothConnectionStatus {
        BT_OK,
        BT_INIT_FAILED,
        BT_TARGET_NOT_DETECTED,
        BT_TARGET_CONN_FAILED,
        BT_SEND_FAILED
    }
    private enum BluetoothConnectionState {
        BT_UNINITIALIZED,
        BT_ADAPTER_FOUND,
        BT_TARGET_FOUND,
        BT_TARGET_CONNECTED
    }
    public static BluetoothConnectionManager sBluetoothConnectionManager;
    public static final int REQUEST_ENABLE_BT = 1;
    //TODO Remove the hard coded value and provide user option to fill
    // the target address
    public static final String BT_TARGET_ADDR = "B0:35:9F:9E:3A:2B";
    public static final String TARGET_RFCOMM_UUID = "00001101-0000-1000-8000-00805F9B34FB";

    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothDevice mTargetDevice;
    private BluetoothSocket mSocket;
    private BluetoothConnectionState mState = BluetoothConnectionState.BT_UNINITIALIZED;

    public BluetoothConnectionStatus initBluetoothManager() {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (null == mBluetoothAdapter ) {
            return BluetoothConnectionStatus.BT_INIT_FAILED;
        }
        mState = BluetoothConnectionState.BT_ADAPTER_FOUND;
        return BluetoothConnectionStatus.BT_OK;
    }

    public BluetoothDevice searchPairedDeviceList(final String targetDeviceAddress) {
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        for (BluetoothDevice device : pairedDevices) {
            if(targetDeviceAddress.equals(device.getAddress()))
            {
                return device;
            }
        }
        return null;
    }

    public void setTargetDevice(BluetoothDevice device) {
        mTargetDevice = device;
        mState = BluetoothConnectionState.BT_TARGET_FOUND;
    }

    public boolean isTargetDiscovered() {
        switch(mState)
        {
            case BT_UNINITIALIZED:
            case BT_ADAPTER_FOUND:
            default:
                return false;
            case BT_TARGET_FOUND:
            case BT_TARGET_CONNECTED:
                return true;
        }
    }

    public boolean isAdaptorEnabled() {
        return mBluetoothAdapter.isEnabled();
    }

    public boolean isTargetConnected() {
        return (null != mSocket) ? true : false;
    }

    public void startDiscovery() {
        // If we're already discovering, stop it
        if (mBluetoothAdapter.isDiscovering()) {
            mBluetoothAdapter.cancelDiscovery();
        }
        mBluetoothAdapter.startDiscovery();
    }
    public void stopDiscovery() {
        mBluetoothAdapter.cancelDiscovery();
    }

    public BluetoothConnectionStatus connectToTarget() {
        if(!isTargetDiscovered()) {
            return BluetoothConnectionStatus.BT_TARGET_NOT_DETECTED;
        }

        try {
            mSocket = mTargetDevice.createRfcommSocketToServiceRecord(UUID.fromString(TARGET_RFCOMM_UUID));
        } catch (IOException e) {
            e.printStackTrace();
            return BluetoothConnectionStatus.BT_TARGET_CONN_FAILED;
        }

        try {
            mSocket.connect();
        } catch (IOException e) {
            e.printStackTrace();
            return BluetoothConnectionStatus.BT_TARGET_CONN_FAILED;
        }
        mState = BluetoothConnectionState.BT_TARGET_CONNECTED;
        return BluetoothConnectionStatus.BT_OK;
    }

    public BluetoothConnectionStatus send(byte[] data) {
        OutputStream outSteam = null;
        if(BluetoothConnectionState.BT_TARGET_CONNECTED == mState) {
            try {
                outSteam = mSocket.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
                return BluetoothConnectionStatus.BT_SEND_FAILED;
            }
            try {
                outSteam.write(data);
            } catch (IOException e) {
                e.printStackTrace();
                return BluetoothConnectionStatus.BT_SEND_FAILED;
            }
        }
        return BluetoothConnectionStatus.BT_OK;
    }
    public void disconnectTarget() {
        if(null != mSocket) {
            try {
                mSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        mTargetDevice = null;
        mState = BluetoothConnectionState.BT_ADAPTER_FOUND;
    }
}
