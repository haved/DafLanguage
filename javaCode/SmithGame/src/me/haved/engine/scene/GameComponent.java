package me.haved.engine.scene;

import me.haved.engine.math.Matrix4;

public abstract class GameComponent {
	protected GameObject parent;
	
	public void setParent(GameObject parent) {
		this.parent = parent;
	}
	
	public void OnAddedToScene(Scene scene) {
		
	}
	
	public void BeforeRemovedFromScene(Scene scene) {
		
	}
	
	public abstract void Update();
	
	public abstract void Render(Matrix4 modelspace, Matrix4 MVP);
}
