package button;

import java.awt.Button;
import java.awt.Frame;
import java.awt.Panel;

public class MyButton extends Frame {
	Button btn1, btn2, btn3;
	
	public MyButton(String str) {
		super(str);
		
		Panel panel = new Panel();
		
		btn1 = new Button(" 가위 ");
		btn2 = new Button(" 바위 ");
		btn3 = new Button(" 보 ");
		
		panel.add(btn1);
		panel.add(btn2);
		panel.add(btn3);
		add(panel);
		
		//btn1.setEnabled(true);
		//btn2.setEnabled(false);
		//btn3.setEnabled(true);
		
		setSize(200,200);
		setVisible(true);
	}
}
