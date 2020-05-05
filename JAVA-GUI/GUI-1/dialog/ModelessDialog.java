package dialog;

import java.awt.Dialog;
import java.awt.Frame;

public class ModelessDialog extends Frame {
	public ModelessDialog() {
		super("다이얼로그 테스트");
		Dialog dialog = new Dialog(this, "modeless dialog");
		setBounds(0,0,400,400);
		setVisible(true);
		dialog.setSize(200,200);
		dialog.setVisible(true);
	}
}
