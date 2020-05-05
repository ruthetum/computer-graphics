package textarea;

import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.TextField;

public class MyTextArea extends Frame {
	public MyTextArea(String str) {
		super(str);
		
		Panel panel = new Panel();
		TextArea textArea = new TextArea(10, 30);
		TextField textField = new TextField("Hello JAVA", 20);
		
		textArea.setText(" Java World ");
		textArea.setBackground(Color.yellow);
		textArea.setFont(new Font("궁서체", Font.BOLD, 10));
		textArea.setForeground(Color.blue);
		
		textField.setEchoChar('@');
		textField.setForeground(Color.red);
		
		panel.add(textArea);
		panel.add(textField);
		add(panel);
		
		setSize(200, 200);
		setVisible(true);
	}
}
