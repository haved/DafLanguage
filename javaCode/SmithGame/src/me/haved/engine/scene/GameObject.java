package me.haved.engine.scene;

import java.util.ArrayList;

import me.haved.engine.math.Matrix4;

public class GameObject {
	private ArrayList<GameComponent> components;
	private Scene scene;
	
	public GameObject() {
		components = new ArrayList<>();
	}
	
	public void SetScene(Scene s) {
		this.scene = s;
	}
	
	public void Update() {
		
	}
	
	public void Render(Matrix4 VP) {
		
	}
}
