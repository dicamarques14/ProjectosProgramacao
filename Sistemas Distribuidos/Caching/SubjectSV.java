import java.io.Serializable;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.ServerNotActiveException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class SubjectSV extends UnicastRemoteObject implements Subject,Serializable  {
/*
 * 
 * http://ip-api.com/docs/api:json
 * http://ip-api.com/json/208.80.152.201
 * https://www.randomlists.com/ip-addresses
 */

	ArrayList<Observer> listObserver;
	
	HashMap<Integer,Observer> listCacheObsv;// idCache | <Observer>
	HashMap<Integer,Subject> listCacheSubj; // idCache | <Subject>
	
	HashMap<Integer,String> listStates; // idState | <state>
	HashMap<String,Float> listDistancesCacheToObsv; // Oy;Cx | <Dist>
	HashMap<String,String> listLocationsCache; // Cx | <Lat>;<Lng>
	HashMap<String,String> listLocationsObsv; // Oy | <Lat>;<Lng>
	
	static Subject s;
	
	public SubjectSV() throws RemoteException  {
		listObserver = new ArrayList<Observer>();
		
		listCacheObsv = new HashMap<Integer,Observer>();
		listCacheSubj = new HashMap<Integer,Subject>();
		
		listStates = new HashMap<Integer,String>();
		listDistancesCacheToObsv = new HashMap<String,Float>();
		listLocationsCache = new HashMap<String,String>();
		listLocationsObsv = new HashMap<String,String>();
	}
	
	public static void main(String[] args) {
		System.out.println("[SUBJECT] Subject Server...");
				
		Registry r=null;
		try{
			r = LocateRegistry.createRegistry(util.rmiSubjPort);
		}catch(RemoteException a){
			a.printStackTrace();
		}
		
		try{
			s = new SubjectSV();
			Naming.rebind(util.rmiSubjAddr, s );
			System.out.println("[SUBJECT] Server ready");
		}catch(Exception e) {
			System.out.println("Exception " + e.getMessage());
		}

		 
	}
	
	@Override
	//Client uses this to get a state from the event list
	public String getState(Integer state) throws RemoteException {

		return listStates.get(state);
	}

	@Override
	//Client uses this to add a new event to the event list, afterwards the Subject requests all the clients to update
	public void setState(String state) throws RemoteException {
		Integer msgID = new Integer(System.identityHashCode(state));
		listStates.put(msgID, state);
		System.out.println("[SUBJECT]New event:" + state);
		updateCache(msgID);
		updateObservers(msgID);
	}

	//Requests all the caches to get the latest msg
	public void updateCache(Integer msgID) throws RemoteException{

		
		Iterator<Integer> keySetIterator = listCacheObsv.keySet().iterator();

		while(keySetIterator.hasNext()){
		  Integer key = keySetIterator.next();
		  try {
			listCacheObsv.get(key).update(msgID, s, null);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
		  
		}
		
		System.out.println("[SUBJECT] Caches Updated");
	}
	
	//Tells all the clients theres a new msg and which cache to use
	public void updateObservers(Integer msgID) throws RemoteException {
		for (Observer observer : listObserver) {
			
			
			observer.update(msgID, s, selectCache("O"+observer.getObsvID()));
		}
		System.out.println("[SUBJECT] Observers Updated");
	}
	
	//Compares cache location with client location and returns the nearest one
	Subject selectCache(String obsvID) {

		
		Iterator<String> keySetIterator = listDistancesCacheToObsv.keySet().iterator();


		String cache_melhor = new String("null");
		Float distancia_melhor = new Float(-1);
		
		//for each element in the hash find the ones with the distances between the observer we want to update and a cache
		while(keySetIterator.hasNext()){
		  String key = keySetIterator.next();
		  //System.out.println("key:"+ key);
		  String[] splitted = key.split(";");
		  //System.out.println("1:"+ splitted[0]+" 2:"+splitted[1]);
		  if(splitted[0].equals(obsvID)) {
			  	Float distancia = listDistancesCacheToObsv.get(key);
				if(distancia_melhor == -1 || (distancia < distancia_melhor) ){
					cache_melhor = splitted[1];
					distancia_melhor = distancia;
				}
		  }
	
		}
		
		//if a good cache was found return it.
		if(distancia_melhor != -1) {
			cache_melhor = cache_melhor.replace("C", "");
			return listCacheSubj.get(Integer.parseInt(cache_melhor));
		}
		System.out.println("[SUBJECT] No good cache for "+obsvID);
		return null;
	}
	
	@Override
	public void attach(Observer o) throws RemoteException {
		int hashID = o.getObsvID();
		listObserver.add(o);
		listLocationsObsv.put("O"+hashID, o.getLocation());
		updateDistancesToObsv(hashID);
		
		
		try {
			System.out.println("[SUBJECT] Attached new Observer IP:"+getClientHost());
		} catch (ServerNotActiveException e) {
			e.printStackTrace();
		}
	}

	//Updates the hash table with the best cache to the observer
	private void updateDistancesToObsv(int obsvID) {
		String obsvLATLNG = listLocationsObsv.get("O"+obsvID);
		Iterator<String> keySetIterator = listLocationsCache.keySet().iterator();

	
		
		while(keySetIterator.hasNext()){
			String cacheID = keySetIterator.next(); //
			String cacheLATLNG = listLocationsCache.get(cacheID);
			float distancia = util.getDistanceCacheToObsv(obsvLATLNG, cacheLATLNG);
			listDistancesCacheToObsv.put("O"+obsvID+";"+cacheID, distancia);
		}
					
				
	}

	//Splits a cache between lists, places its location to another list and updates the observers distance
	@Override
	public void attachCache(Observer o,Subject s) throws RemoteException {
		int hashID = o.getObsvID();
		listCacheObsv.put(hashID, o);
		listCacheSubj.put(hashID, s);
		listLocationsCache.put("C"+hashID, o.getLocation());
		updateDistancesAll();
		try {
			System.out.println("[SUBJECT] Attached new Cache IP:"+getClientHost() );
		} catch (ServerNotActiveException e) {

			e.printStackTrace();
		}
		
	}

	//for each observer update all the distances
	private void updateDistancesAll() throws RemoteException {
		
		for (Observer observer : listObserver) {
			updateDistancesToObsv(observer.getObsvID());
		}
	}

}
