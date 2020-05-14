class Caller {
	public static void main() {
		System.out.println(new Callee().method());
	}
}

class Callee {
	public void method() {
		return 1;
	}
}

