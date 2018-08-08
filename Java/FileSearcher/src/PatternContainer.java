package ru.karabutov.file_seacher.pattern;

import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class PatternContainer {

	private PatternContainer() {
		
	}
	
	public boolean match(String str, String pattern) {
		List<PatternProcessor> processors = splitPattern(pattern);
		return match(str, processors);
	}
	
	public boolean match(String str, List<PatternProcessor> processors) {
		State state = new State(processors);
		for (PatternProcessor processor : processors) {
			state.removeFirstElem();
			if (!processor.process(str, state)) {
				return false;
			}
		}
		if (!state.isAsteriksFaced() && state.getPosition() < str.length()) {
			return false;
		}
		return true;
	}

	private List<PatternProcessor> splitPattern(String pattern) {
		List<PatternProcessor> processors = new LinkedList<>();
		int pos = 0;
		Set<String> keys = ProcessorFactory.getProcessorKeys();
		while (pos < pattern.length()) {
			int firstKeyPos = Integer.MAX_VALUE;
			String procKey = null;
			for (String key : keys) {
				int kp = pattern.indexOf(key, pos);
				if (kp >= 0 && kp < firstKeyPos) {
					firstKeyPos = kp;
					procKey = key;
				}
			}
			if (null != procKey) {
				if (firstKeyPos > pos) {
					processors.add(new JustString(pattern.substring(pos, firstKeyPos)));
				}
				processors.add(ProcessorFactory.getProcessor(procKey));
				pos = firstKeyPos + procKey.length();
			} else {
				processors.add(new JustString(pattern.substring(pos)));
				break;
			}
		}
		return processors;
	}

	final static private PatternContainer INSTANCE = new PatternContainer();

	final static public PatternContainer getInstance() {
		return INSTANCE;
	}
}
