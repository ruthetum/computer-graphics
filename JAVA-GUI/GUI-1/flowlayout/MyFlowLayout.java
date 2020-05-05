package flowlayout;

import java.awt.Button;
import java.awt.FlowLayout;
import java.awt.Frame;

public class MyFlowLayout extends Frame {
	FlowLayout flowLayout = new FlowLayout();
	Button[] button = new Button[10];
	
	public MyFlowLayout(String str) {
		super(str);
		
		setLayout(flowLayout);
		
		for (int i=0;i<10;i++) {
			button[i] = new Button((i+1)+"번 버튼");
			add(button[i]);
		}
		setBounds(100,100,200,200);
		setVisible(true);
	}
}
