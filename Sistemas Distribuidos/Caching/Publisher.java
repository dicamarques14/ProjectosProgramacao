import java.rmi.Naming;

public class Publisher {

	public Publisher() {
		// TODO Auto-generated constructor stub
	}
	public static void main(String[] args) {
	    // TODO Auto-generated method stub
		try {
			/*
			//39.9596985;-75.1989943   40.591358;-7.768836
			String obsvLATLNG = "39.9597;-75.1968";
			String cacheLATLNG = "40.591358;-7.768836";
			util.getDistanceCacheToObsv(obsvLATLNG, cacheLATLNG);*/
			
			Subject subSV = (Subject)Naming.lookup(util.rmiSubjAddr);
			Observer cli = (Observer)Naming.lookup(util.rmiObseAddr);
			Observer cache = (Observer)Naming.lookup(util.rmiCacheSubjAddr);
			//subSV.attach(cli);
			//subSV.attach(cache);
			System.out.println("[PUB]Connected to RMI-server");
			subSV.setState("Ola Pessoas");
			
			
		}
		catch (Exception e) {
			System.out.println("exception: "+ e.getMessage());
			e.printStackTrace();
		}
	}

}
