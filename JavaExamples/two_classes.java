class Program {
	public static void main() {
		int a;
		a = 1;
		System.out.println(a);
		{
			System.out.println(a);
			int a;
			a = 2;
			System.out.println(a);
		}
		System.out.println(a);
	}
}

class MyObject {
	public int foo(int a) {
		int b;
		b = 10;
		System.out.println(b);
	}

	int b;
	int c;
}

class Useless {
	public void bar(int a, boolean b, int c) {
		int unused;
		unused = 10;
	}
}