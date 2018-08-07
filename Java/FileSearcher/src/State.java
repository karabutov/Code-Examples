package ru.karabutov.file_seacher.pattern;

public class State {

	private int position;

	private boolean asteriksFaced;

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
