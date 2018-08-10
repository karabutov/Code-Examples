package ru.karabutov.file_seacher.pattern;


import java.util.ArrayList;
public class PrettyPrint {

	private PrettyPrint() {}
	
	private static boolean needToContinue(ArrayList<TypeOfInfo> info) {
		for(int i = 0; i < info.size(); i++) {
			if(!info.get(i).isPrinted()) {
				return true;
			}
		}
		return false;
	}
	
	private static void print(ArrayList<TypeOfInfo> info) {
		while(needToContinue(info)) {
			for(int i = 0; i < info.size(); i++) {
				info.get(i).printLine();
			}
			System.out.println("");
		}
		System.out.println("");
	}
	
	public static void processing(ArrayList<ArrayList<TypeOfInfo>> info) {
		
		for(int i = 0; i < info.get(0).size(); i++) {
			info.get(0).get(i).printColoumn();
		}
		System.out.println("");
		System.out.println("");
		for(int i = 0; i < info.size(); i++) {
			print(info.get(i));
		}
	}
	
}
