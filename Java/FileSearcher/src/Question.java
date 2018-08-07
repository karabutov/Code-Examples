package ru.karabutov.file_seacher.pattern;

public class Question extends PatternProcessor {

	public Question() {
		super("?");
	}

	@Override
	public boolean process(String str, State state) {
		if (state.getPosition() >= str.length()) {
			return false;
		}
		state.addPosition(getCode().length());
		return true;
	}

}
