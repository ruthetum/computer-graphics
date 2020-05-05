package paneltest;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Panel;

public class PanelTest extends Frame{
	
	public PanelTest(String str) {
		super(str);
		Panel panel = new Panel();
		
		panel.setBackground(Color.RED);
		
		add(panel);
		
		setSize(300, 300);
		setVisible(true);
	}
}
