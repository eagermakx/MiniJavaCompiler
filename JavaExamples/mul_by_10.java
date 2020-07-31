class Caller {
	public static void main() {
		Callee c;
		c = new Callee();

		System.out.println(new Callee().mul_by_10(new Callee().mul_by_10(10)));
	}
}

class Callee {
	public int mul_by_10(int a) {
		return 10 * a;
	}
}

