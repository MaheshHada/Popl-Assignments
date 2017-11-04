import java.lang.*;
import java.util.List;
import java.util.ArrayList;

public class LoadDownloadEvent {
  protected Download d;
  protected int id;
  protected String name;
  protected double completion;
  protected int parts;
  protected List<Thread> threads;
  
  public LoadDownloadEvent(Download d) {
    this.d = d;
    this.completion = d.tab.completion[d.id];
    name = d.tab.name;
    id = d.id;
    parts = d.parts;
    threads = new ArrayList<Thread>();
    splitAndDownload();
  }
  
  public void splitAndDownload() {
    for (int i=0; i<parts; i++)
      threads.add(new Thread(new Task(this)));
      
    for (Thread t: threads) {
      try {
        t.start();
        t.join();
      }
      catch (InterruptedException e) {
        e.printStackTrace();
      }
    }  
  }  
  
  
  public String status() {
    if (completion == 1.0)
      return "Tab Idle.";
    else
      return "";
  }
}
