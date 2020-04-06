package graphics1;

import javax.media.opengl.*;
import javax.media.opengl.awt.GLCanvas;
import javax.swing.JFrame;


// https://www.javatpoint.com/jogl-primitives-shapes


public class Main implements GLEventListener{
	@Override
	public void init(GLAutoDrawable arg0) {
		
	}
	
	@Override
	public void display(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glBegin(GL2.GL_POLYGON);
		gl.glVertex3f(-0.50f, -0.50f, 0);
		gl.glVertex3f(0.50f, -0.50f, 0);
		gl.glVertex3f(0.50f, 0.50f, 0);
		gl.glVertex3f(-0.50f, 0.50f, 0);
		gl.glEnd();
		
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
		Main sq = new Main();
		gc.addGLEventListener(sq);
		gc.setSize(400,400);
		
		// creating frame
		final JFrame frame = new JFrame("JOGL Drawing Example");
		
		// adding canvas to frame
		frame.getContentPane().add(gc);
		
		frame.setSize(frame.getContentPane().getPreferredSize());
		frame.setVisible(true);
	}
}
