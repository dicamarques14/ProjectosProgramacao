import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Subject extends Remote{
	public String getState(Integer state) throws RemoteException; 
	public void setState(String state) throws RemoteException;
	public void attach(Observer o) throws RemoteException;
	public void attachCache(Observer o,Subject s) throws RemoteException;
}
