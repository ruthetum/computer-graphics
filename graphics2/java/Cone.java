package graphics2;

import javax.media.opengl.*;
import javax.media.opengl.awt.GLCanvas;
import javax.swing.JFrame;

import com.jogamp.opengl.util.gl2.GLUT;

public class Cone implements GLEventListener{
	@Override
	public void init(GLAutoDrawable arg0) {
		
	}
	
	@Override
	public void display(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		GLUT glut = new GLUT();
		gl.glClear(GL.GL_COLOR_BUFFER_BIT);
		
		glut.glutWireCone(0.5, 5.0, 5, 12);
		
		gl.glFlush();
	}
	
	@Override
	public void reshape(GLAutoDrawable arg0, int arg1, int arg2, int arg3, int arg4) {
		
	}
	
	@Override
	public void dispose(GLAutoDrawable arg0){
		
	}
	
	public static void main(String []args) {
		// getting the capabilities object of GL2 profile
		final GLProfile gp = GLProfile.get(GLProfile.GL2);
		GLCapabilities cap = new GLCapabilities(gp);
		
		// The canvas
		final GLCanvas gc = new GLCanvas(cap);
		Cone sq = new Cone();
		gc.addGLEventListener(sq);
		gc.setSize(400,400);
		
		// creating frame
		final JFrame frame = new JFrame("Drawing cone with JOGL");
		
		// adding canvas to frame
		frame.getContentPane().add(gc);
		
		frame.setSize(frame.getContentPane().getPreferredSize());
		frame.setVisible(true);
	}
}
