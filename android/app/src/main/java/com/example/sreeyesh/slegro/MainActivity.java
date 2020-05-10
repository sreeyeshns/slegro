package com.example.sreeyesh.slegro;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
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

import static com.example.sreeyesh.slegro.BluetoothConnectionManager.*;

public class MainActivity extends AppCompatActivity {
    private BluetoothConnectionManager mBluetoothConnectionManager;

    final BroadcastReceiver mBroadcastRreceiver;

    public MainActivity() {
        mBluetoothConnectionManager = new BluetoothConnectionManager();

        /* Save the object reference globally so that it can be accessed
         by other activities */
        if(null != mBluetoothConnectionManager)
        {
            sBluetoothConnectionManager = mBluetoothConnectionManager;
        }

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
                        if (BluetoothConnectionManager.BT_TARGET_ADDR.equals(device.getAddress())) {
                            mBluetoothConnectionManager.stopDiscovery();
                            mBluetoothConnectionManager.setTargetDevice(device);
                            scanningTextView.setText("Connecting to target");
                            if(BluetoothConnectionStatus.BT_OK == mBluetoothConnectionManager.connectToTarget()) {
                                scanningTextView.setText("Verifying target");
                                Intent controlActivityIntent = new Intent(context, ControlActivity.class);
                                startActivity(controlActivityIntent);
                            }
                            else {
                                alertMessageShow("Error", "Failed to connect to target!");
                            }
                            scanProgressBar.setVisibility(View.INVISIBLE);
                            scanningTextView.setVisibility(View.INVISIBLE);
                        }
                        break;
                    case BluetoothAdapter.ACTION_DISCOVERY_FINISHED:
                        if (!mBluetoothConnectionManager.isTargetDiscovered()) {
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
            }
        });

        alertDialogBuilder.setNegativeButton(R.string.exit, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
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
        if (BluetoothConnectionStatus.BT_OK != mBluetoothConnectionManager.initBluetoothManager()) {
            alertMessageShow("Error", "Device doesn't support Bluetooth");
            finish();
        }

        // Register the BroadcastReceiver
        IntentFilter filter = new IntentFilter();
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        registerReceiver(mBroadcastRreceiver, filter);
    }

    private void setupBluetoothCommunication() {
        ProgressBar scanProgressBar = (ProgressBar)findViewById(R.id.progressBar);
        TextView scanningTextView = (TextView)findViewById(R.id.scanStatusTextViews);

        scanningTextView.setText("Checking for paired target");

        BluetoothDevice device = mBluetoothConnectionManager.searchPairedDeviceList(BT_TARGET_ADDR);
        if(null == device) {
            scanningTextView.setText("Scanning for target");
            // Discover new devices
            mBluetoothConnectionManager.startDiscovery();
        } else {
            mBluetoothConnectionManager.setTargetDevice(device);

            scanningTextView.setText("Connecting to target");
            if(BluetoothConnectionStatus.BT_OK == mBluetoothConnectionManager.connectToTarget()) {
                scanningTextView.setText("Verifying target");
                Intent controlActivityIntent = new Intent(this, ControlActivity.class);
                startActivity(controlActivityIntent);
            }
            else {
                alertMessageShow("Error", "Failed to connect to target!");
            }
            scanProgressBar.setVisibility(View.INVISIBLE);
            scanningTextView.setVisibility(View.INVISIBLE);
            Button connectButton = (Button)findViewById(R.id.connectButton);
            connectButton.setEnabled(true);
        }
    }

    public void onclickConnect(View view) {
        Button connectButton = (Button)findViewById(R.id.connectButton);
        connectButton.setEnabled(false);
        ProgressBar scanProgressBar = (ProgressBar)findViewById(R.id.progressBar);
        scanProgressBar.setVisibility(View.VISIBLE);
        TextView scanningTextView = (TextView)findViewById(R.id.scanStatusTextViews);
        scanningTextView.setVisibility(View.VISIBLE);
        scanningTextView.setText("Checking bluetooth adaptor");
        if(mBluetoothConnectionManager.isAdaptorEnabled()) {
            setupBluetoothCommunication();
        }
        else {
            scanningTextView.setText("Turning on bluetooth");
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == REQUEST_ENABLE_BT && resultCode == RESULT_OK) {
            setupBluetoothCommunication();
        }
    }

    @SuppressLint("SourceLockedOrientationActivity")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme);
        super.onCreate(savedInstanceState);
        setRequestedOrientation (ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
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

    /* call this function only from onBackPressed */
    private void navigateBack() {
        super.onBackPressed();
    }

    @Override
    public void onBackPressed() {
        if (mBluetoothConnectionManager.isTargetConnected()) {
            AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(MainActivity.this);
            alertDialogBuilder.setTitle("Exit");
            alertDialogBuilder.setMessage("Do you want to exit?");

            alertDialogBuilder.setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    mBluetoothConnectionManager.disconnectTarget();
                    navigateBack();
                }
            });

            alertDialogBuilder.setNegativeButton(R.string.no, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                }
            });

            AlertDialog alertDialog = alertDialogBuilder.create();
            alertDialog.show();
        }
        else {
            super.onBackPressed();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mBroadcastRreceiver);
        mBluetoothConnectionManager.disconnectTarget();
    }
}
