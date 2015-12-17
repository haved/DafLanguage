package me.haved.engine.core;

public abstract class Game {
	public abstract void Init(GameWindow window);
	public abstract void Resize(int width, int height);
	public abstract void Update();
	public abstract void Render();
	public abstract void OnKeyEvent(int key, int scancode, int action, int mods);
}
