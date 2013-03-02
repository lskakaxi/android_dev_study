package com.example.bttest;

import com.example.bttest.R;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.bluetooth.*;
import android.content.Intent;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Button btn = (Button) findViewById(R.id.button1);
		Button ndk_btn = (Button) findViewById(R.id.button2);
		btn.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Log.i("lskakaxi", "hello");
				BluetoothAdapter bt_adapter = BluetoothAdapter.getDefaultAdapter();
				if (bt_adapter == null)
					Log.e("lskakaxi", "no BT");
				else
					Log.i("lskakaxi", "BT" + bt_adapter);
				if (!bt_adapter.isEnabled()) {
					Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
					startActivityForResult(enableBtIntent, 0x1);
				}
			}
		});
		ndk_btn.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				test();
			}
		});
		
		TextView tv = (TextView) findViewById(R.id.textView1);
		tv.setText(stringFromJNI());
	}

	public native String stringFromJNI();
	public native void test();
	
	static {
		System.loadLibrary("testjni");
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
