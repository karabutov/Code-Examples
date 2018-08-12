package ru.karabutov.file_seacher.pattern;

public class Path extends TypeOfInfo {
	
	private static final int FIELD_SIZE = 30;
	
	Path(String info){
		super(info, FIELD_SIZE);
	}
	
	private int getPosOfNextSlash() {
		int pos = getInfo().indexOf('/', getPointer());
		if(pos < 0) {
			pos = getInfo().indexOf("\\", getPointer());
		}
		if(pos < 0) {
			return getInfo().length();
		}
		return pos+1;
	}
	
	@Override
	public boolean printLine() {
		
		if(!isPrinted()) {
			int surplus = getSizeOfField();
			String curFolder = getInfo().substring(getPointer(), getPosOfNextSlash());
			if(curFolder.length() < surplus) {
				while(curFolder.length() > 0 && curFolder.length() < surplus) {
					setPointer(getPosOfNextSlash());
					System.out.print(curFolder);
					surplus -=curFolder.length();
					curFolder = getInfo().substring(getPointer(), getPosOfNextSlash());
				}
			} else {
				System.out.print(getInfo().substring(getPointer(), getPointer() + getSizeOfField()));
				setPointer(getPointer() + getSizeOfField());
				surplus = 0;
			}
			for(int i = 0; i < surplus + 4; i++) {
				System.out.print(" ");
			}
			if(getPointer() == getInfo().length()) {
				setPrinted(true);
				return true;
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
		System.out.print("Path");
		for(int i = 0; i < getSizeOfField(); i++) {
			System.out.print(" ");
		}
	}
	
}
