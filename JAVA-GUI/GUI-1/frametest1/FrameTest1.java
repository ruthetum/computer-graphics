package frametest1;

import java.awt.Frame;

public class FrameTest1 {

	public static void main(String[] args) {
		
		Frame f = new Frame();
		f.setTitle("프레임 예제1");
		f.setBounds(100,100,300,300); // 원점x,y , width, height
		f.setVisible(true);
	}

}
