package ru.karabutov.file_seacher.pattern;

public abstract class TypeOfInfo {

	private String info;
	private int pointer = 0;
	private int sizeOfField;
	private boolean isPrinted = false;
	
	TypeOfInfo(String info, int size){
		this.info = info;
		sizeOfField = size;
	}
	
	public String getInfo() {
		return info;
	}
	public void setIfo(String info) {
		this.info = info;
	}
	public int getPointer() {
		return pointer;
	}
	public void setPointer(int pointer) {
		this.pointer = pointer;
	}
	public int getSizeOfField() {
		return sizeOfField;
	}
	public void setSizeOfField(int sizeOfField) {
		this.sizeOfField = sizeOfField;
	}
	public boolean isPrinted() {
		return isPrinted;
	}
	public void setPrinted(boolean isPrinted) {
		this.isPrinted = isPrinted;
	}
	
	public abstract boolean printLine();
	public abstract void printColoumn();
	
}
