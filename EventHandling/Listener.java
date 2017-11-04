import java.lang.*;

public class Listener {
  public synchronized void onDownload(LoadDownloadEvent de) {
    System.out.println(de.name + " loaded " + (int)(100 * de.completion) + "%. " + de.status()); 
  }
}
