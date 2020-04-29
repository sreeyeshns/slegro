package com.example.sreeyesh.slegro;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;

import java.util.Set;

public final class BluetoothConnectionManager {
    public enum BTConnectionStatus{
        BT_INIT_SUCCESS,
        BT_INIT_FAILED
    }
    public static final int REQUEST_ENABLE_BT = 1;
    //TODO Remove the hard coded value and provide user option to fill
    // the target address
    public static final String BT_TARGET_ADDR = "B0:35:9F:9E:3A:2B";

    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothDevice mTargetDevice;
    private boolean mIsTargetDiscovered = false;

    public BTConnectionStatus initBluetoothManager() {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (null == mBluetoothAdapter ) {
            return BTConnectionStatus.BT_INIT_FAILED;
        }
        return BTConnectionStatus.BT_INIT_SUCCESS;
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
        mIsTargetDiscovered = true;
    }

    public boolean isTargetDiscovered() {
        return mIsTargetDiscovered;
    }

    public boolean isAdaptorEnabled() {
        return mBluetoothAdapter.isEnabled();
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
}
