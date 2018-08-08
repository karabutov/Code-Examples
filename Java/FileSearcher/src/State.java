package ru.karabutov.file_seacher.pattern;


import java.util.LinkedList;
import java.util.List;

public class State {

	private int position;

	private boolean asteriksFaced;

	private List<PatternProcessor> pattern;
	
	public State(List<PatternProcessor> pattern) {
		this.pattern = new LinkedList<>(pattern);
	}
	
	public  List<PatternProcessor> getPattern(){
		return pattern;
	}
	
	public void removeFirstElem() {
		pattern.remove(0);
	}
	
	public int getPosition() {
		return position;
	}

	public void addPosition(int shift) {
		this.position += shift;
	}

	public void setPosition(int position) {
		this.position = position;
	}

	public boolean isAsteriksFaced() {
		return asteriksFaced;
	}

	public void setAsteriksFaced(boolean asteriksFaced) {
		this.asteriksFaced = asteriksFaced;
	}

}
