package me.haved.engine.core;

public class FPSCounter {
	private int frameCount;
	private long startTimeMillis = System.currentTimeMillis(); 
	public void nextFrame() {
		frameCount++;
		long diff = System.currentTimeMillis() - startTimeMillis;
		if(diff>=1000) {
			System.out.println("FPS:"+(frameCount*1000f/diff));
			frameCount = 0;
			startTimeMillis = System.currentTimeMillis();
		}
	}
}
