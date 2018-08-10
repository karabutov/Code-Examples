package ru.karabutov.file_seacher.pattern;

public class IsDir extends TypeOfInfo {

	IsDir(String info){
		super(info, 4);
	}
	
	@Override
	public boolean printLine() {
		if(!isPrinted()) {
			System.out.print(getInfo());
			for(int i = 0; i < 4; i++) {
				System.out.print(" ");
			}
			setPrinted(true);
			return true;
		} else {
			for(int i = 0; i < getSizeOfField() + 4; i++) {
				System.out.print(" ");
			}
			return true;
		}
	}
	
	@Override
	public void printColoumn() {
		System.out.print("Type");
		for(int i = 0; i < getSizeOfField() + 4; i++) {
			System.out.print(" ");
		}
	}
}
