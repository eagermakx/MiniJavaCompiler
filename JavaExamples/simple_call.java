class Caller {
	public static void main() {
		Callee callee;
		callee = new Callee();
		callee.method_to_call();
	}
}

class Callee {
	public void method_to_call() {
		SecondCallee second_callee;
		second_callee = new SecondCallee();
		second_callee.print();
	}
}

class SecondCallee {
	public void print() {
		System.out.println(1);
	}
}