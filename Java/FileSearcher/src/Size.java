package ru.karabutov.file_seacher.pattern;

public class Size extends TypeOfInfo {

	Size(String info){
		super(info, 25);
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
		System.out.print("Size");
		for(int i = 0; i <  getSizeOfField() + 4; i++) {
			System.out.print(" ");
		}
	}
}
