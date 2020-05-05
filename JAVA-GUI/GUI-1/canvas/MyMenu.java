package canvas;

import java.awt.Frame;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;

public class MyMenu extends Frame {
	public MyMenu(String str) {
		super(str);
		
		MenuBar menuBar = new MenuBar();
		
		Menu file = new Menu("파일");
		MenuItem file_new = new MenuItem("새로 만들기");
		MenuItem file_open = new MenuItem("열기");
		MenuItem file_save = new MenuItem("저장");
		MenuItem file_saveas = new MenuItem("다른 이름으로 저장");		
		file.add(file_new);
		file.add(file_open);
		file.add(file_save);
		file.add(file_saveas);
		
		Menu edit = new Menu("편집");
		MenuItem edit_undo = new MenuItem("실행 취소");
		MenuItem edit_cut = new MenuItem("잘라내기");
		MenuItem edit_copy = new MenuItem("복사");
		MenuItem edit_paste = new MenuItem("붙여넣기");		
		edit.add(edit_undo);
		edit.add(edit_cut);
		edit.add(edit_copy);
		edit.add(edit_paste);
		
		menuBar.add(file);
		menuBar.add(edit);
		
		setMenuBar(menuBar);
		setSize(200, 200);
		setVisible(true);
	}
}
