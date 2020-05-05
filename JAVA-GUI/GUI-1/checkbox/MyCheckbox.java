package checkbox;

import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.Frame;
import java.awt.Panel;

public class MyCheckbox extends Frame {
	
	public MyCheckbox(String str) {
		super(str);
		
		Panel panel = new Panel();
		
		Checkbox cbx1 = new Checkbox("치킨", true);
		Checkbox cbx2 = new Checkbox("피자");
		Checkbox cbx3 = new Checkbox("햄버거");
		panel.add(cbx1);
		panel.add(cbx2);
		panel.add(cbx3);
		
		CheckboxGroup group = new CheckboxGroup();
		Checkbox cbx4 = new Checkbox("그룹 내 버튼1", group, true);
		Checkbox cbx5 = new Checkbox("그룹 내 버튼2", group, false);
		Checkbox cbx6 = new Checkbox("그룹 내 버튼3", group, false);
		panel.add(cbx4);
		panel.add(cbx5);
		panel.add(cbx6);
		
		add(panel);
		setSize(180, 300);
		setVisible(true);
		
	}
}
