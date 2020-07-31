class Main {
	public static void main() {
		boolean a;
		a = true;

		int b;
		b = 0;

		if (a) {
			if (true) {
				b = 1;
			}
		}

		System.out.println(b);
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

