import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.HashMap;

public interface Observer extends Remote {
	public void update(int idState, Subject s, Subject o) throws RemoteException; //subject executes this everytime theres a new state 
	public HashMap<Integer,String> getEvents() throws RemoteException; //get events stored on the client
	public String getLocation() throws RemoteException; //get location of client, for selecting best cache server
	public int getObsvID() throws RemoteException; //get ID of the observer 
	
}
