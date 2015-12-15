package me.haved.engine.core;

import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;
 
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.Version;

public abstract class GameWindow {
	private GLFWErrorCallback errorCallback;
	private GLFWKeyCallback keyCallback;
	
	private long windowHandle;
	
	private String title;
	private int width, height, samples;
	private boolean vsync;
	
	public GameWindow(String title, int width, int height, int samples, boolean vsync) {
		this.title 		= title;
		this.width 		= width;
		this.height 	= height;
		this.samples 	= samples;
		this.vsync 		= vsync;
	}
	
	protected abstract void OnInit();
	protected abstract void OnRenderFrame();
	protected abstract void OnResize(int width, int height);
	protected abstract void OnKeyEvent(int key, int scancode, int action, int mods);
	
	protected void Run(int frameRate) {
		System.out.println("LWJGL Version " + Version.getVersion());
		try {
			glfwSetErrorCallback(errorCallback = GLFWErrorCallback.createPrint(System.err));
			if(glfwInit()!=GLFW_TRUE)
				throw new IllegalStateException("Unable to initialize GLFW");
			
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
			glfwWindowHint(GLFW_SAMPLES, samples);
			glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
			
			windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
			if(windowHandle==NULL)
				throw new RuntimeException("Failed to create GLFW window");
			
			glfwSetKeyCallback(windowHandle, keyCallback = new GLFWKeyCallback() {
				@Override
				public void invoke(long window, int key, int scancode, int action, int mods) {
					OnKeyEvent(key, scancode, action, mods);
				}
			});
			
			GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			
			glfwSetWindowPos(windowHandle, (vidmode.width()-width)/2, (vidmode.height()-height)/2);
			
			glfwMakeContextCurrent(windowHandle);
			glfwSwapInterval(vsync?1:0);
			glfwShowWindow(windowHandle);
			
			GL.createCapabilities();
			
			OnInit();
			OnResize(width, height);
			
			while(glfwWindowShouldClose(windowHandle)==GLFW_FALSE) {
				Time.updateDeltaTime();
				glfwPollEvents();
				OnRenderFrame();
			}
			
			glfwDestroyWindow(windowHandle);
			keyCallback.release();
		} finally {
			glfwTerminate();
			errorCallback.release();
		}
	}
	
	public void MakeCurrentContext() {
		glfwMakeContextCurrent(windowHandle);
	}
	
	public void SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}
	
	public void SetWindowClose() {
		glfwSetWindowShouldClose(windowHandle, GLFW_TRUE);
	}
}
