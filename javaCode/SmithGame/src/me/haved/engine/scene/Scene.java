package me.haved.engine.scene;

import me.haved.engine.math.Matrix4;

public class Scene {
	private GameObject rootObject;
	
	public Scene() {
		rootObject = new GameObject();
		rootObject.SetScene(this);
	}
	
	public void Update() {
		rootObject.Update();
	}
	
	public void Render(Matrix4 VP) {
		rootObject.Render(VP);
	}
	
	public void AddGameObject(GameObject object) {
		rootObject.AddChild(object);
	}
}
