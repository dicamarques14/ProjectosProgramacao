import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ThreadLocalRandom;

import org.json.JSONArray;
import org.json.JSONObject;

//Class with common variables and functions 

public class util {

	public static final String ipList[] = {
			"210.222.66.157",
		    "206.115.146.196",
		    "133.5.175.106",
		    "47.145.0.75",
		    "40.203.146.205",
		    "129.38.141.128",
		    "165.123.54.236",
		    "185.71.140.2",
		    "30.11.153.172",
		    "59.4.28.181",
		    "156.190.251.21",
		    "68.232.220.225"
		    };
	
	public static final int rmiSubjPort = 2020;
	public static final String rmiSubjAddr = "//localhost:"+rmiSubjPort+"/subject";
	
	public static final int rmiCachePort = 2023;
	public static final String rmiCacheSubjAddr = "//localhost:"+rmiCachePort+"/cacheSubject";
	public static final String rmiCacheObseAddr = "//localhost:"+rmiCachePort+"/cacheObserver";
	
	public static final int rmiObsePort = 2021;
	public static final String rmiObseAddr = "//localhost:"+rmiObsePort+"/client";
	
	public static final String gAPIKey = "GET YOUR OWN KEY"; //https://developers.google.com/maps/documentation/javascript/get-api-key
	public static final String gAPIUrl = "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins=";
	public static final String gAPIUrl2 = "&destinations=";
	public static final String gAPIUrl3 = "&key="+gAPIKey;
	
	public static final String ipAPIUrl = "http://ip-api.com/json/";
	
	
	//returns a random IP from the list of IP's
	public static final String getRandomIP() {
		
		int randomNum = ThreadLocalRandom.current().nextInt(0, ipList.length);
		//System.out.println(randomNum);
		return ipList[randomNum];
		
	}
	
	//returns a string with the lat and lng of the IP <lat>;<lng>
	public static final String getIPLocation(String IP) {
		String response = "null";
		try {
			JSONObject jsonResponse = new JSONObject(sendGet(ipAPIUrl+IP));
			response = jsonResponse.getFloat("lat") +";"+ jsonResponse.getFloat("lon");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//do json stuff and return lat;lng

		System.out.println("[UTIL]"+response);
		return response;
		
	}
	
	//request the distance between two geographical locations and in case its not found it returns -1
	public static final float getDistanceCacheToObsv(String obsvLATLNG,String cacheLATLNG ){
		
		String split[] = obsvLATLNG.split(";");
		
		String split2[] = cacheLATLNG.split(";");
		String response;
		float value = 0;
		try {
			response = sendGet(gAPIUrl+split[0]+","+split[1]+gAPIUrl2+split2[0]+","+split2[1]+gAPIUrl3);
			JSONObject json = new JSONObject(response);
			JSONArray  rows = json.getJSONArray("rows");
			JSONObject jobj = rows.getJSONObject(0);
			JSONArray jarray2 = jobj.getJSONArray("elements");
			JSONObject element = jarray2.getJSONObject(0);
			String status = element.getString("status");
			
			//check if the distance was calculated
			if(status.equals("OK")) {
				value = element.getJSONObject("distance").getFloat("value");
				System.out.println("[UTIL]Distance: "+value); 
			}else {
				value = -1;
				System.out.println("[UTIL]Distance Not Found"); 
			}
			 
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return value;
	}
	// HTTP GET request
	private static String sendGet(String url) throws Exception {
		URL obj = new URL(url);
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();

		// optional default is GET
		con.setRequestMethod("GET");

		//add request header
		con.setRequestProperty("User-Agent", "Mozilla/5.0");

		int responseCode = con.getResponseCode();
		System.out.println("[UTIL]Sending 'GET' request to URL : " + url);
		//System.out.println("Response Code : " + responseCode);

		BufferedReader in = new BufferedReader(
		        new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer response = new StringBuffer();

		while ((inputLine = in.readLine()) != null) {
			response.append(inputLine);
		}
		in.close();
		
		//System.out.println(response.toString());
		return response.toString();

	}
}
