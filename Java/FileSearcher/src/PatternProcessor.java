package ru.karabutov.file_seacher.pattern;

public abstract class PatternProcessor {

	private String code;

	public PatternProcessor(String code) {
		this.code = code;
	}

	abstract public boolean process(String str, State state);

	public String getCode() {
		return code;
	}

}
