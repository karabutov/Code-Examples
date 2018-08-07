package ru.karabutov.file_seacher.pattern;

import java.io.File;
import java.util.Collection;
import java.util.TreeSet;

public class Searcher {

	private String pattern;
	private String dir;
	private Collection<File> fileList;
	private boolean recursion;

	public Searcher() {
		fileList = new TreeSet<>();
	}

	public Searcher(String fileName, String dir, boolean recursion) {
		this.pattern = fileName;
		this.dir = dir;
		fileList = new TreeSet<>();
		this.recursion = recursion;
	}

	public void setCharacteristic(String fileName, String dir,boolean recursion) {
		this.pattern = fileName;
		this.dir = dir;
		fileList = new TreeSet<>();
		this.recursion = recursion;
	}

	private void searchFiles(String curDir) {
		File dir = new File(curDir);
		if (!dir.isDirectory()) {
			throw new IllegalArgumentException();
		}
		for (File item : dir.listFiles()) {
			if (PatternContainer.getInstance().match(item.getName(), pattern)) {
				fileList.add(item);
			}
			if (item.isDirectory() && recursion) {
				searchFiles(curDir + "/" + item.getName());
			}
		}
	}

	public Collection<File> find() {
		searchFiles(dir);
		return fileList;
	}
}
