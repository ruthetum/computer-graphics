package ListTest;

import java.awt.Frame;
import java.awt.List;
import java.awt.Panel;

public class ListTest extends Frame {
	Panel panel;
	List list;
	
	public ListTest(String str) {
		super(str);
		
		panel = new Panel();
		
		list = new List(2, true);
		
		list.add("치킨");
		list.add("피자");
		list.add("햄버거");
		list.add("족발");
		panel.add(list);
		
		add(panel);
		setSize(300,100);
		setVisible(true);
	}
}
