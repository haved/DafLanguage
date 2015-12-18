package me.haved.engine.math;

public class Matrix4 {
	private static final int ROWS = 4;
	private static final int COLS = 4;
	private static final int IDENTITY_SIZE=4; //The smallest value of width and height
	
	public float[] array;
	
	public Matrix4() {
		array = new float[ROWS*COLS];
	}
	
	public Matrix4 MakeIdentity() {
		for(int i = 0; i < IDENTITY_SIZE; i++) {
			array[COLS*i+i]=1;
		}
		return this;
	}
	
	public String toString() {
		StringBuilder b = new StringBuilder("Matrix4 \n");
		
		for(int j=0;j<ROWS;j++) {
			b.append("| ");
			for(int i=0;i<COLS;i++) {
				b.append(array[i+j*COLS]).append(" ");
			}
			b.append("|\n");
		}
		
		return b.toString();
	}
	
	public Matrix4 Copy() {
		Matrix4 cp = new Matrix4();
		System.arraycopy(array, 0, cp.array, 0, ROWS*COLS);
		return cp;
	}
	
	public void CopyFrom(Matrix4 b) {
		System.arraycopy(b.array, 0, array, 0, ROWS*COLS);
	}
}
