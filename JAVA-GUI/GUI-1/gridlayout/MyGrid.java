package gridlayout;

import java.awt.Button;
import java.awt.Frame;
import java.awt.GridLayout;

import java.awt.Button;
import java.awt.Frame;
import java.awt.GridLayout;

public class MyGrid extends Frame {

	Button[] button = new Button[6];
	
	public MyGrid(String str) {
		super(str);
		
		setLayout(new GridLayout(3,2));
		
		for (int i=0; i<6;i++) {
			button[i] = new Button(i+1 +"번 버튼");
			add(button[i]);
		}
		
		setSize(200,200);
		setVisible(true);
	}
}
