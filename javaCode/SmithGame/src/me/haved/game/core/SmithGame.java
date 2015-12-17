package me.haved.game.core;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;

import me.haved.engine.core.FPSCounter;
import me.haved.engine.core.Game;
import me.haved.engine.core.GameWindow;
import me.haved.engine.math.Matrix4;
import me.haved.engine.scene.Scene;

public class SmithGame extends Game {

	private GameWindow window;
	
	private Matrix4 perspectiveMatrix;
	private Scene currentScene;
	
	@Override
	public void Init(GameWindow window) {
		this.window = window;
		
		currentScene = new Scene();
		
		glClearColor(0.1f, 0.5f, 0.8f, 0.0f);
	}

	@Override
	public void Resize(int width, int height) {
		perspectiveMatrix = new Matrix4().MakeIdentity();
	}

	private FPSCounter counter = new FPSCounter();
	@Override
	public void Update() {
		counter.nextFrame();
		currentScene.Update();
	}

	@Override
	public void Render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//currentScene.Render();
		window.SwapBuffers();
	}

	@Override
	public void OnKeyEvent(int key, int scancode, int action, int mods) {
		if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
            window.SetWindowClose();
	}
	
	public static SmithGame  gameInstance;
	public static GameWindow windowInstance;
	public static void main(String[] args) {
		gameInstance = new SmithGame();
		windowInstance = new GameWindow(gameInstance, "Smith Game", 1600, 900, 8, false);
		windowInstance.Run(75);
	}
}
