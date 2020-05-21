class Caller {
	public static void main() {
		System.out.println(new Callee().method(10, 10, false));
	}
}

class Callee {
	public int method(int a, int b, boolean c) {
		if (c) {
			return a + b;
		}
		return a;
	}
}

