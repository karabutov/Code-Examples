package ru.karabutov.file_seacher.pattern;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class ProcessorFactory {

	static private Map<String, PatternProcessor> processorStorage = new HashMap<>();

	static public PatternProcessor getProcessor(String key) {
		return processorStorage.get(key);
	}

	static public Set<String> getProcessorKeys() {
		return processorStorage.keySet();
	}

	static {
		processorStorage.put("*", new Asterisk());
		processorStorage.put("?", new Question());
	}

}
