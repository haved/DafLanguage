package me.haved.game.core;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;

import me.haved.engine.core.FPSCounter;
import me.haved.engine.core.GameWindow;

public class SmithGameWindow extends GameWindow {

	public SmithGameWindow(String title, int width, int height, int samples, boolean vsync) {
		super(title, width, height, samples, vsync);
	}

	@Override
	protected void OnInit() {
		System.out.println("Init!");
		glClearColor(0.1f, 0.5f, 0.8f, 0.0f);
	}

	private FPSCounter counter = new FPSCounter();
	@Override
	protected void OnRenderFrame() {
		counter.nextFrame();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SwapBuffers();
	}

	@Override
	protected void OnResize(int width, int height) {
		System.out.println(new StringBuilder("Resized to ").append(width).append(",").append(height).toString());
	}

	@Override
	protected void OnKeyEvent(int key, int scancode, int action, int mods) {
		if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
            SetWindowClose();
	}
	
	public static SmithGameWindow instance;
	public static void main(String[] args) {
		instance = new SmithGameWindow("Smith Game", 1600, 900, 8, false);
		instance.Run(60);
	}
}
