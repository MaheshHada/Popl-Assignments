import java.lang.*;
import java.util.List;
import java.util.ArrayList;

public class Tab implements Runnable {
  private static int count = 0;
  protected int id = count++;
  protected String name;
  protected int components;
  protected int totalSize;
  protected List<Thread> threads;
  protected double[] completion;
  
  public Tab(String name, int components) {
    this.name = name;
    this.components = components;
    completion = new double[components];
    totalSize = 0;
    threads = new ArrayList<Thread>();
    new Thread(this).start();
  }
  
  @Override
  public synchronized void run() {
    for (int i=0; i<components; i++) {
      Download d = new Download(this, i);
      totalSize += d.size;
      completion[i] = (double)d.size;
      if (i != 0)
        completion[i] += completion[i - 1];
      threads.add(new Thread(d));
    }
    
    for (int i=0; i<components; i++)
      completion[i] /= totalSize;
      
    System.out.println("Total size of tasks for " + name + ": " + totalSize);
    
    for (Thread t: threads) {
      try {
        t.start();
        t.join();
      }
      catch(InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
