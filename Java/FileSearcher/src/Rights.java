package ru.karabutov.file_seacher.pattern;

public class Rights extends TypeOfInfo {

	Rights(String info){
		super(info, 11);
	}
	
	@Override
	public boolean printLine() {
		if(!isPrinted()) {
			System.out.print(getInfo());
			setPrinted(true);
			return true;
		} else {
			for(int i = 0; i < getSizeOfField(); i++) {
				System.out.print(" ");
			}
			return true;
		}
	}

	@Override
	public void printColoumn() {
		System.out.print("Rights(read, write,  execute)");
		for(int i = 0; i <  getSizeOfField() + 4; i++) {
			System.out.print(" ");
		}

	}

}
