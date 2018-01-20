import java.io.Serializable;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.ServerNotActiveException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;

public class ObserverCache extends UnicastRemoteObject implements Observer, Subject,Serializable   {

	HashMap<Integer,String> listStates;
	String Location;//<lat>;<Lng>
	String IP;
	int ID;
	
	public ObserverCache(String _IP) throws RemoteException {
		
		listStates = new HashMap<Integer,String>();
		IP = _IP;
		Location = util.getIPLocation(IP);
		ID = System.identityHashCode(this);
	}

	public static void main(String[] args) throws RemoteException  {
		System.out.println("[CACHE] Observer Cache...");
		Registry r;
		ObserverCache c = new ObserverCache(util.getRandomIP());
		Subject s = c;
		Observer o = c;
		
		try{
			r = LocateRegistry.createRegistry(2023);
		}catch(RemoteException a){
			a.printStackTrace();
			System.out.println("Registry not found!");
		}
		try{
			
			Naming.rebind(util.rmiCacheSubjAddr, s );
			Naming.rebind(util.rmiCacheObseAddr, o );
			System.out.println("[CACHE] Cache ready");
			
			Subject subj = (Subject)Naming.lookup(util.rmiSubjAddr);
			subj.attachCache(o,s);
			System.out.println("[CACHE] Attached to subject");
			
			
		}catch(Exception e) {
			System.out.println("Exception " + e.getMessage());
		}
		
	}
	
	@Override
	//Gets update from subject sv
	public void update(int idEvent, Subject s,Subject o) throws RemoteException {
		System.out.println("[CACHE] update req. idEvent="+idEvent);
		listStates.put(idEvent, s.getState(idEvent));
	}
	
	@Override
	public HashMap<Integer,String> getEvents() throws RemoteException{
		return listStates;
	}

	//returns the content of a state.
	@Override
	public String getState(Integer state) throws RemoteException {
		try {
			System.out.println("[CACHE] getState req. from Host"+getClientHost());
		} catch (ServerNotActiveException e) {

			e.printStackTrace();
		}
		return listStates.get(state);
	}
	
	//returns the location of the cache
	@Override
	public String getLocation() throws RemoteException {
		return Location;
	}

	//returns the ID of the cache
	@Override
	public int getObsvID() throws RemoteException {
		return ID;
	}
	
	@Override
	public void setState(String state) throws RemoteException {
		System.out.println("[CACHE] Hmmm i'm a cache not a subject, wrong number");
	}

	@Override
	public void attach(Observer o) throws RemoteException {
		System.out.println("[CACHE] Hmmm i'm a cache not a subject, wrong number");
	}

	@Override
	public void attachCache(Observer o, Subject s) throws RemoteException {
		System.out.println("[CACHE] Hmmm i'm a cache not a subject, wrong number");		
	}

}
