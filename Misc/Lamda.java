import java.util.function.Predicate;
import java.util.*;

interface Converter {
	int doit(int x);
}


public class Lamda {
	public static void main(String[] args) {
		Converter conv = (int x) -> {return x + 2;};
		// System.out.println(conv.doit(2));
		int u = 55,l = 13;
		List <Integer> nums = Arrays.asList(10,11,12,13,14,56,78);
		// nums.forEach(n->System.out.println(n + " "));
		Predicate<Integer> upper = (n)->n<u;		//gives a stream with underlyinh data structure as List which can be filtered 
		Predicate<Integer> lower = (n)->n>l;
		nums.stream().filter(upper.negate()).forEach(n->System.out.println(n + " "));	//negation of the stream obtained is done here
		nums.stream().filter(lower.and(upper)).forEach(n->System.out.println(n + " "));	//and means union of the two streams is taken here
		
		// List<Integer> costBeforeTAx = Arrays.asList(100,200,300,400,500);
		// double total = 0;
		// costBeforeTAx.stream().map((cost)->cost+0.12*cost).forEach(System.out::println);
		// Double avg = costBeforeTAx.stream().mapToDouble((cost)->cost + 0.12*cost).average().getAsDouble();
		// System.out.println(avg);
		// total = costBeforeTAx.stream().map((cost)->cost+0.12*cost).reduce((s,c)->s+c).get();
		// System.out.println(total);
	}
}