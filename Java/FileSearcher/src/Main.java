package ru.karabutov.file_seacher.pattern;

import java.io.File;
import java.util.Collection;
import java.util.Iterator;


public class Main {
	
	public static void main(String[] args) {
		
		String template = args[0];
		String curDir = args[1];
	
		Searcher fileSearcher = new Searcher(template, curDir, true);
		Collection<File> files = fileSearcher.find();
		for(Iterator<File> i = files.iterator(); i.hasNext();) {
			File f = i.next();
			System.out.println(f.getName());
		}	
	}
}

