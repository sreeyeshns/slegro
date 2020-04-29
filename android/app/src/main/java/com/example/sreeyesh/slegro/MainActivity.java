package com.example.sreeyesh.slegro;

import android.Manifest;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import static com.example.sreeyesh.slegro.BluetoothConnectionManager.BTConnectionStatus.BT_INIT_SUCCESS;
import static com.example.sreeyesh.slegro.BluetoothConnectionManager.BT_TARGET_ADDR;
import static com.example.sreeyesh.slegro.BluetoothConnectionManager.REQUEST_ENABLE_BT;

public class MainActivity extends AppCompatActivity {

    BluetoothConnectionManager mBTConnectionManager;
    final BroadcastReceiver mBroadcastRreceiver;

    public MainActivity() {
        mBTConnectionManager = new BluetoothConnectionManager();
        mBroadcastRreceiver = new BroadcastReceiver()
        {
            @Override
            public void onReceive(Context context, Intent intent)
            {
                ProgressBar scanProgressBar = (ProgressBar)findViewById(R.id.progressBar);
                TextView scanningTextView = (TextView)findViewById(R.id.scanStatusTextViews);

                switch(intent.getAction()) {
                    // When discovery finds a device
                    case BluetoothDevice.ACTION_FOUND:
                        // Get the bluetoothDevice object from the Intent
                        BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                        if (BT_TARGET_ADDR.equals(device.getAddress())) {
                            mBTConnectionManager.stopDiscovery();
                            device.createBond();
                            scanProgressBar.setVisibility(View.INVISIBLE);
                            scanningTextView.setVisibility(View.INVISIBLE);
                            alertMessageShow("Success", "Target detected!");
                            mBTConnectionManager.setTargetDevice(device);
                        }
                        break;
                    case BluetoothAdapter.ACTION_DISCOVERY_FINISHED:
                        if (!mBTConnectionManager.isTargetDiscovered()) {
                            scanningTextView.setText("Scanning stopped");
                            alertMessageShow("Error", "Target not found!");
                            scanProgressBar.setVisibility(View.INVISIBLE);
                            scanningTextView.setVisibility(View.INVISIBLE);
                        }
                        Button connectButton = (Button) findViewById(R.id.connectButton);
                        connectButton.setEnabled(true);
                        break;
                }
            }
        };
    }


    private void alertMessageShow(String title, String message){
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(MainActivity.this);
        alertDialogBuilder.setTitle(title);
        alertDialogBuilder.setMessage(message);

        alertDialogBuilder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                Toast.makeText(getApplicationContext(), "You clicked on OK", Toast.LENGTH_SHORT).show();
            }
        });

        alertDialogBuilder.setNegativeButton(R.string.exit, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                Toast.makeText(getApplicationContext(), "You clicked on EXIT", Toast.LENGTH_SHORT).show();
                finish();
            }
        });

        AlertDialog alertDialog = alertDialogBuilder.create();
        alertDialog.show();
    }

    private void initSlegro() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, 1);
        }
        if (BT_INIT_SUCCESS != mBTConnectionManager.initBluetoothManager()) {
            alertMessageShow("Error", "Device doesn't support Bluetooth");
            finish();
        }

        // Register the BroadcastReceiver
        IntentFilter filter = new IntentFilter();
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        this.registerReceiver(mBroadcastRreceiver, filter);
    }

    private void findTarget() {
        ProgressBar scanProgressBar = (ProgressBar)findViewById(R.id.progressBar);
        TextView scanningTextView = (TextView)findViewById(R.id.scanStatusTextViews);

        scanningTextView.setText("Checking for paired target");

        BluetoothDevice device = mBTConnectionManager.searchPairedDeviceList(BT_TARGET_ADDR);
        if(null == device) {
            scanningTextView.setText("Scanning for target");
            // Discover new devices
            mBTConnectionManager.startDiscovery();
        } else {
            mBTConnectionManager.setTargetDevice(device);
            alertMessageShow("Found", "Target detected!");
            scanProgressBar.setVisibility(View.INVISIBLE);
            scanningTextView.setVisibility(View.INVISIBLE);
            Button connectButton = (Button)findViewById(R.id.connectButton);
            connectButton.setEnabled(true);
        }
    }

    public void onclickScan(View view) {
        Button connectButton = (Button)findViewById(R.id.connectButton);
        connectButton.setEnabled(false);
        ProgressBar scanProgressBar = (ProgressBar)findViewById(R.id.progressBar);
        scanProgressBar.setVisibility(View.VISIBLE);
        TextView scanningTextView = (TextView)findViewById(R.id.scanStatusTextViews);
        scanningTextView.setVisibility(View.VISIBLE);
        scanningTextView.setText("Checking bluetooth adaptor");
        if(mBTConnectionManager.isAdaptorEnabled()) {
            findTarget();
        }
        else {
            scanningTextView.setText("Turning on bluetooth...");
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == REQUEST_ENABLE_BT && resultCode == RESULT_OK) {
            findTarget();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme);
        super.onCreate(savedInstanceState);
        // Hide the action bar and run in full screen
        getSupportActionBar().hide();
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        // Wait 3 sec for the splash screen
        try{
            Thread.sleep(2000);
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        setContentView(R.layout.activity_main);
        initSlegro();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mBroadcastRreceiver);
    }

}
