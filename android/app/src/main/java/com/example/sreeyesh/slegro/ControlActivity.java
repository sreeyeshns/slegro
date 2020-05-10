package com.example.sreeyesh.slegro;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;

public class ControlActivity extends AppCompatActivity {
    private BluetoothConnectionManager mBluetoothConnectionManager = BluetoothConnectionManager.sBluetoothConnectionManager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Hide the action bar and run in full screen
        getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_control);
    }

    public void onclickStop(View view) {
        mBluetoothConnectionManager.send("Stop\n\r".getBytes());
    }

    public void onclickForward(View view) {
        mBluetoothConnectionManager.send("Forward\n\r".getBytes());
    }

    public void onclickBackward(View view) {
        mBluetoothConnectionManager.send("Backward\n\r".getBytes());
    }

    public void onclickRight(View view) {
        mBluetoothConnectionManager.send("Right\n\r".getBytes());
    }

    public void onclickLeft(View view) {
        mBluetoothConnectionManager.send("Left\n\r".getBytes());
    }

    /* call this function only from onBackPressed */
    private void navigateBack() {
        super.onBackPressed();
    }

    @Override
    public void onBackPressed() {
        if (mBluetoothConnectionManager.isTargetConnected()) {
            AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(ControlActivity.this);
            alertDialogBuilder.setTitle("Disconnect");
            alertDialogBuilder.setMessage("Target is connected. Do you want to disconnect?");

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
}
