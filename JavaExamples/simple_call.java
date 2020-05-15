class Caller {
	public static void main() {
		Callee callee;
		callee = new Callee();
		callee.method_to_call();
	}
}

class Callee {
	public void method_to_call() {
		System.out.println(1);
	}
}