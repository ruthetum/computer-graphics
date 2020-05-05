package borderlayout;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Frame;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Frame;

public class MyBorderLayout extends Frame {
	public MyBorderLayout(String str) {
		super(str);
		
		setLayout(new BorderLayout());
		
		add("North", new Button("북"));
		add("West", new Button("서"));
		add("East", new Button("동"));
		add("Center", new Button("중앙"));
		add("South", new Button("남"));
		
		setSize(200,200);
		setVisible(true);
	}
}
