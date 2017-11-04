import java.lang.*;
import java.util.Random;

public class Download implements Runnable {
  protected int id;
  protected Tab tab;
  protected int parts;
  protected int size;
  private static final Random rNo = new Random();
  protected Listener downloadListener;
  
  public Download(Tab tab, int id) {
    this.tab = tab;
    this.id = id;
    downloadListener = new Listener();
    size = rNo.nextInt(990) + 10;
    this.parts = size / 100;
  }
  
  @Override
  public synchronized void run() {
    downloadListener.onDownload(new LoadDownloadEvent(this));
  }
}
