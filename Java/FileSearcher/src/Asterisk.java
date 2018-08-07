package ru.karabutov.file_seacher.pattern;

public class Asterisk extends PatternProcessor {

	public Asterisk() {
		super("*");
	}

	@Override
	public boolean process(String str, State state) {
		state.setAsteriksFaced(true);
		return true;
	}

}
