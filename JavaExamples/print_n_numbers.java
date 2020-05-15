class Caller {
	public static void main() {
		new Printer().print_numbers(10);
	}
}

class Printer {
	public void print_numbers(int n) {
		if (n > 0) {
			System.out.println(n);
			this.print_numbers(n - 1);
		}
	}
}