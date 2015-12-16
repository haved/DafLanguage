package me.haved.engine.core;

public class Time {
	
	private static long  deltaMillis;
	private static float deltaTime;
	
	private static long prevTimeMillis=System.currentTimeMillis();
	public static void updateDeltaTime() {
		long newDelta = System.currentTimeMillis()-prevTimeMillis;
		if(newDelta<10) {
			Time.deltaTime   = newDelta/1000f;
			Time.deltaMillis = newDelta;
		}
		prevTimeMillis = System.currentTimeMillis();
	}
	
	public static float DeltaTime() {
		return deltaTime;
	}
	
	public static long DeltaMillis() {
		return deltaMillis;
	}
	
	public static long TimeSinceDeltaUpdate() {
		return System.currentTimeMillis()-prevTimeMillis;
	}
}
