package label;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Label;
import java.awt.Panel;

public class LabelTest extends Frame{
	Panel panel;
	Label label1, label2, label3;
	
	public LabelTest(String str) {
		super(str);
		
		panel = new Panel();
		
		label1 = new Label("치킨", Label.RIGHT);
		label2 = new Label("피자", Label.CENTER);
		label3 = new Label("햄버거", Label.LEFT);
		
		label1.setBackground(Color.red);
		label2.setBackground(Color.blue);
		label3.setBackground(Color.green);
		
		panel.add(label1);
		panel.add(label2);
		panel.add(label3);
		
		add(panel);
		setSize(300, 300);
		setVisible(true);
	}
}
