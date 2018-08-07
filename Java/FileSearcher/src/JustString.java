package ru.karabutov.file_seacher.pattern;

public class JustString extends PatternProcessor {

	public JustString(String code) {
		super(code);
	}

	@Override
	public boolean process(String str, State state) {
		int pos = str.indexOf(getCode(), state.getPosition());

		if (pos < 0) {
			return false;
		}
		
		if(!state.isAsteriksFaced() && pos != state.getPosition()) {
			return false;
		} 
		state.setAsteriksFaced(false);
		state.setPosition(pos + getCode().length());
		return true;
	}

}
