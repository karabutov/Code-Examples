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
		
		state.setPosition(pos + getCode().length());
		
		if(state.isAsteriksFaced()) {
			boolean ind = false;
			while(!(ind = PatternContainer.getInstance().match(str.substring(state.getPosition(), str.length()), state.getPattern())) 
																																																&&
																																					state.getPosition()<str.length()) {
				pos = str.indexOf(getCode(), state.getPosition());
				if (pos < 0) {
					return false;
				}
				state.setPosition(pos + getCode().length());
			}		
			state.setAsteriksFaced(false);
			return ind;
		}
		
		
		state.setAsteriksFaced(false);
		return true;
	}

}
