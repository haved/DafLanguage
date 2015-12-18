package me.haved.engine.math;

public class Vector3 {
	float x, y, z;
	
	public Vector3(){}
	
	public Vector3(float x, float y, float z) {
		this.x=x;
		this.y=y;
		this.z=z;
	}
	
	public float getLength() {
		return (float)Math.sqrt(x*x+y*y+z*z);
	}
}
