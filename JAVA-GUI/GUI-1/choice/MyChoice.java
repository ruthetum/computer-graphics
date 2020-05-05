package choice;

import java.awt.Choice;
import java.awt.Frame;

public class MyChoice extends Frame {
	Choice choice;
	
	public MyChoice(String str) {
		super(str);
		
		choice = new Choice();
		
		choice.addItem("치킨");
		choice.addItem("피자");
		choice.addItem("햄버거");
		
		add(choice);
		setSize(300, 100);
		setVisible(true);
	}
}
