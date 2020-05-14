class Caller {
	public static void main() {
		System.out.println(new Square().calc(100));
	}
}

class Callee {
	public void print_numbers(int n) {
		if (!n) {
			return 1;
		}

		System.out.println(n);
		this.print_numbers(n - 1);
	}
}

class Square {
	public int calc(int n) {
		return n * n;
	}
}