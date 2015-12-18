package me.haved.engine.scene;

import java.util.ArrayList;

import me.haved.engine.math.Matrix4;
import me.haved.engine.math.Vector3;

public class GameObject {
	private GameObject 					parent;
	private ArrayList<GameObject>    	children;
	private ArrayList<GameComponent> 	components;
	private Scene scene;
	
	private boolean visible=true;
	private boolean updates=true;
	
	private boolean dead;
	
	private Vector3 pos;
	private Vector3 rot;
	private Vector3 scale;
	private Matrix4 localTransform;
	private Matrix4 globalTransform;
	
	private boolean localTransformChanged;
	private boolean globalTransformChanged;
	
	private int globalTransformVersion;
	private int parentTransformVersion;
	
	public GameObject() {
		children   = new ArrayList<>();
		components = new ArrayList<>();
		localTransform 	= new Matrix4().MakeIdentity();
		globalTransform = new Matrix4().MakeIdentity();
		pos 	= new Vector3();
		rot 	= new Vector3();
		scale 	= new Vector3();
	}
	
	public void SetParent(GameObject parent) {
		this.parent = parent;
		parentTransformVersion = parent.globalTransformVersion;
		globalTransformChanged = true;
	}
	
	public void SetScene(Scene s) {
		this.scene = s;
		if(s!=null)
			for(GameComponent comp:components) {
				comp.OnAddedToScene(s);
			}
		else {
			for(GameComponent comp:components) {
				comp.BeforeRemovedFromScene(s);
			}
		}
		for(GameObject child:children) {
			child.SetScene(s);
		}
	}
	
	public void AddComponent(GameComponent comp) {
		components.add(comp);
		comp.setParent(this);
		if(scene!=null)
			comp.OnAddedToScene(scene);
	}
	
	public void AddChild(GameObject child) {
		children.add(child);
		child.SetParent(this);
		child.SetScene(scene);
	}
	
	public void Update() {
		if(updates) {
			for(int i = 0; i < components.size(); i++) {
				components.get(i).Update();
			}
			for(int i = 0; i < children.size(); i++) {
				children.get(i).Update();
				if(children.get(i).dead)
					children.remove(i);
			}
		}
	}
	
	public void Render(Matrix4 VP) {
		if(visible) {
			Matrix4 MVP = VP;
			for(int i = 0; i < components.size(); i++) {
				components.get(i).Render(MVP, VP);
			}
			for(int i = 0; i < children.size(); i++) {
				children.get(i).Render(VP);
			}
		}
	}
	
	public boolean isDead() {
		return dead;
	}
	
	public void SetPosition(Vector3 pos) {
		this.pos = pos;
		localTransformChanged = true;
		globalTransformChanged = true;
	}
	
	public void SetRotation(Vector3 rot) {
		this.rot = rot;
		localTransformChanged = true;
		globalTransformChanged = true;
	}
	
	public void SetScale(Vector3 scale) {
		this.scale = scale;
		localTransformChanged = true;
		globalTransformChanged = true;
	}
	
	public Matrix4 GetLocalTransform() {
		if(localTransformChanged) {
			localTransform.MakeIdentity();
			//Do stuff!
			localTransformChanged = false;
		}
		
		return localTransform;
	}
	
	public Matrix4 GetGlobalTransform() {
		if(globalTransformChanged & parent==null) {
			globalTransform = GetLocalTransform();
		}
		else if(globalTransformChanged | parentTransformVersion != parent.globalTransformVersion) {
			globalTransform.CopyFrom(parent.GetGlobalTransform());
			//The multiply it with the GetLocalTransform();
			parentTransformVersion = parent.globalTransformVersion;
		}
		else {
			return globalTransform;
		}
		globalTransformChanged = false;
		globalTransformVersion++;
		return globalTransform;
	}
}
