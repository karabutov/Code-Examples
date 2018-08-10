package ru.karabutov.file_seacher.pattern;

public class Name extends TypeOfInfo {

	private static final int FIELD_SIZE = 20;
	Name(String info){
		super(info, FIELD_SIZE);
	}
	@Override
	public boolean printLine() {
		if(!isPrinted()) {
			if(getInfo().length() - getPointer() < getSizeOfField()) {
				System.out.print(getInfo().substring(getPointer(), getInfo().length()));
				setPrinted(true);
				for(int i = 0; i <  getSizeOfField()-getInfo().length() + getPointer() + 4 ; i++) {
					System.out.print(" ");
				}
				return true;
			}
			System.out.print(getInfo().substring(getPointer(), getPointer() + getSizeOfField()));
			setPointer(getPointer() + getSizeOfField());
			for(int i = 0; i <  4 ; i++) {
				System.out.print(" ");
			}
			return false;
		} else {
			for(int i = 0; i < getSizeOfField() + 4; i++) {
				System.out.print(" ");
			}
			return true;
		}
	}

	@Override
	public void printColoumn() {
		System.out.print("Name");
		for(int i = 0; i < getSizeOfField() + 4; i++) {
			System.out.print(" ");
		}
	}

}
