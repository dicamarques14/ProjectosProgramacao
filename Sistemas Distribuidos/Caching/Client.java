import java.io.Serializable;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;

public class Client extends UnicastRemoteObject implements Observer,Serializable   {
	private HashMap<Integer,String> states;
	
	String Location;//<lat>;<Lng>
	static String IP;
	int ID;
	
	public Client(String _IP) throws RemoteException {
		states = new HashMap<Integer,String>();
		IP = _IP;
		Location = util.getIPLocation(IP);

		ID = System.identityHashCode(this);
	}
	
	public static void main(String[] args) throws RemoteException {
		System.out.println("[OBSERVER] Observer Client...");
		Registry r;
		Observer o;
		try{
			r = LocateRegistry.createRegistry(util.rmiObsePort);
		}catch(RemoteException a){}
		try{
			o = new Client(util.getRandomIP());
			Naming.rebind(util.rmiObseAddr, o );
			System.out.println("[OBSERVER] Client ready");
			
			
			
			Subject subj = (Subject)Naming.lookup(util.rmiSubjAddr);
			subj.attach(o);//attach to subject
			System.out.println("[OBSERVER] Attached to subject");
			
		}catch(Exception e) {
			System.out.println("Exception " + e.getMessage());
			e.printStackTrace();
		}
	}
	
	@Override
	//gets update from Cache sv
	public void update(int idEvent, Subject s, Subject o) throws RemoteException {	
		System.out.println("[OBSERVER] Update idEvent:"+idEvent);
		if(o != null) {
			//go to the cache
			states.put(idEvent,o.getState(idEvent));
			System.out.println("[OBSERVER] Accessed Cache");
		}else {
			//go to the subject
			states.put(idEvent,s.getState(idEvent));
			System.out.println("[OBSERVER] Accessed Subject");
		}
		System.out.println("[OBSERVER] State:"+states.get(idEvent));
	}
	
	@Override
	public HashMap<Integer,String> getEvents() throws RemoteException{
		return states;
	}

	@Override
	public String getLocation() throws RemoteException {
		return Location;
	}

	@Override
	public int getObsvID() throws RemoteException {
		return ID;
	}

}
