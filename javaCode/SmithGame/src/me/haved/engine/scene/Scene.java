package me.haved.engine.scene;

import java.util.ArrayList;

public class Scene {
	private ArrayList<GameObject> gameObjects;
	
	public Scene() {
		gameObjects = new ArrayList<>();
	}
	
	public void Update() {
		for(int i = 0; i < gameObjects.size(); i++) {
			gameObjects.get(i).Update();
		}
	}
}
