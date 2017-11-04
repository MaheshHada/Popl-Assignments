class Triangle {
	public void draw() { 
		System.out.println("Base::draw\n"); 
	}
	public void computeCentroid(Triangle t) 
	{
		System.out.println("Base::centroid\n");
	}
}

class RightAngledTr extends Triangle {
	public void draw() { 
		System.out.println("RightAngle::draw\n"); 
	}
	public void computeCentroid(RightAngledTr t) {
		System.out.println("RtAngle::centroid\n");
	}
	public void foo() {

	}
}

public class Poly {
	static void manageFigures() {
		Triangle tr = new RightAngledTr();
		RightAngledTr rtr = new RightAngledTr ();
		tr.draw();		//RightAngle::draw
		rtr.draw();		//RightAngle::draw
		rtr.computeCentroid(tr);	//Base::centroid    	//here at compile time only it decides which method to call
		rtr.computeCentroid(rtr);	//RtAngle::centroid
		tr.computeCentroid(tr);		//Base::centroid
		tr.computeCentroid(rtr);	//Base::centroid
		// tr.foo();	

	}
	public static void main(String[] args) {
		manageFigures();
	}
}