package com.example.helloworldndk;

import androidx.appcompat.app.AppCompatActivity;
import android.widget.TextView;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("helloworld-c");
    }

    // A native method that returns a Java String to be displayed on the
    // TextView
    public native String getMessage();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Create a TextView.
        TextView textView = new TextView(this);
        // Retrieve the text from native method getMessage()
        textView.setText(getMessage());
        setContentView(textView);
    }

//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//    }
}