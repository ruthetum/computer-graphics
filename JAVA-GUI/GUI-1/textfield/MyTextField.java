package textfield;

import java.awt.Frame;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;

public class MyTextField extends Frame {
	public MyTextField(String str) {
		super(str);
		
		Panel panel = new Panel();
		
		Label label1 = new Label(" 아 이 디 ");
		Label label2 = new Label(" 비밀번호 ");
		
		TextField textField1 = new TextField("ID", 20);
		TextField textField2 = new TextField(20);
		textField2.setEchoChar('*');
		
		panel.add(label1);
		panel.add(textField1);
		panel.add(label2);
		panel.add(textField2);
		add(panel);
		setSize(200, 200);
		setVisible(true);
	}
}
