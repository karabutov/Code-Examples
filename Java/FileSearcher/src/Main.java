package ru.karabutov.file_seacher.pattern;

import java.io.File;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class Main {
	
	private static boolean size = false;
	private static boolean rights = false;
	private static boolean help = false;
	private static int ind = 0;
	private static String template = "";
	
	private static ArrayList<TypeOfInfo> makeTypeOfInfo(File f){
		ArrayList<TypeOfInfo> fileInfo= new ArrayList<>();
		
		fileInfo.add(new Path(f.getParent()));
		
		fileInfo.add(new Name(f.getName()));
		
		if(f.isDirectory()) {				
			fileInfo.add(new IsDir("Dir"));
		} else {
			fileInfo.add(new IsDir("File"));
		}
		
		if(size) {
			Long sizeOfFile =f.length();
			fileInfo.add(new Size(sizeOfFile.toString()));
		}
		
		if(rights) {
			String rights = "";
			if(f.canRead()) {
				rights += "Yes ";
			} else {
				rights += "No ";
			}
			
			if(f.canWrite()) {
				rights += "Yes ";
			} else {
				rights += "No ";
			}
			
			if(f.canExecute()) {
				rights += "Yes ";
			} else {
				rights += "No ";
			}
			fileInfo.add(new Rights(rights));
		}
		return fileInfo;
	}
	
	private static void argsParse(String[] args) {
		for(String arg : args) {
			if(arg.charAt(0) == '-') {
				for(int i = 1; i < arg.length(); i++) {
					char curSymb = arg.charAt(i);
					switch(curSymb){
					case 'h': 
						help = true;
						break;
					case 's':
						size = true;
						break;
					case 'r':
						rights = true;
						break;
					}
				}
			} else {
				template = arg;
				ind++;
			}
		}
	}
	
	public static void main(String[] args) {
		
		if(args.length > 0) {
			argsParse(args);
		} else {
			help = true;
		}
		String curDir = System.getProperty("user.dir");
		if(help){
			System.out.println("HELP");
			System.out.println("Program arguments:");
			System.out.println("	File name(required)(wildcards ? and * supported)");
			System.out.println("	The following additional keys:");
			System.out.println("		-h - displays this help");
			System.out.println("		-s - show size of found files");
			System.out.println("		-r - show rights of found files");
		}
		
		if(!help && ind == 0) {
			System.out.println("Template wasn't founded");
		} else if(ind > 1) {
			System.out.println("More then one templates were founded");
		} else if(ind == 1){
			
			Searcher fileSearcher = new Searcher(template, curDir);
			Collection<File> files = fileSearcher.find();
			
			ArrayList<ArrayList<TypeOfInfo>> info = new ArrayList<>();
			
			for(Iterator<File> i = files.iterator(); i.hasNext();) {
				File f = i.next();
				info.add(makeTypeOfInfo(f));
			}
			PrettyPrint.processing(info);
		}
		
	}
}

