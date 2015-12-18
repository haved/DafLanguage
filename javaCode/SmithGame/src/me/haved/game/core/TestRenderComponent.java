package me.haved.game.core;

import me.haved.engine.core.Time;
import me.haved.engine.math.Matrix4;
import me.haved.engine.scene.GameComponent;

import static org.lwjgl.opengl.GL11.*;

public class TestRenderComponent extends GameComponent {
	@Override
	public void Update() {
		
	}

	@Override
	public void Render(Matrix4 modelspace, Matrix4 MVP) {
		glColor3f(Time.AllMillis()/1000f%1, Time.AllMillis()/2000f%1, Time.AllMillis()/3000f%1);
		glBegin(GL_QUADS);
		{
			glVertex2f(-.5f, -.5f);
			glVertex2f( .5f, -.5f);
			glVertex2f( .5f,  .5f);
			glVertex2f(-.5f,  .5f);
		}
		glEnd();
	}
}
