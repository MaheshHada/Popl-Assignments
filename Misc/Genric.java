oimport java.util.*;

// class EventPool<T> {
// 	private ArrayList<T> pool;
// 	public T makeEvent() {
// 		T event = createEvent();
// 		pool.add(event);
// 		return event;
// 	}
// }

class GenricNumber<T> {
	private ArrayList<T> list;
	GenricNumber() {
		list = new ArrayList<T>();
	}
	public void addtoList(T e) {
		list.add(e);
	}
	public void print() {
		for(T p : list)
			System.out.println(p);
	}
	public T search(int ind) {
		return list.get(ind);
	}
}

public class Genric {
	public static void addGenric(List<? super Integer> list,Number e) {
		list.add(e);
	}
	public static void getGenric(List<? extends Number> list) {
		for(int i=0;i<list.size();i++) {
			System.out.println(list.get(i));
		}
	}
	public static void main(String[] args) {
		// Number one = new Integer(1);
		// Float two = new Float(1.0);
		// // Integer one = new Integer(1);
		// GenricNumber<Number> gn = new GenricNumber<Number>();
		// gn.addtoList(one);
		// gn.addtoList(two);
		// gn.print();
		// Integer In = gn.search(1);  //incompatible types: Number cannot be converted to Integer 
		// ArrayList<Integer> in = new ArrayList<Integer>();
		// // in.add(one);	//cant do this
		// in.add(new Integer(5));
		// in.add(new Integer(2));
		// in.add(new Integer(6));
		// // ArrayList<Number> nn = in;	//incompatible types
		
		// List<Double> ld = new ArrayList<>();
		// ld.add(new Double(2.0));
		// ld.add(new Double(3.0));
		// getGenric(ld);
		// getGenric(in);
		List<Integer> inn = new ArrayList<>();
		Number nn1 = new Integer(89);
		addGenric(inn,new Integer(67));
		// addGenric(inn,nn1);
		getGenric(inn);
	}
}
