class Caller {
	public static void main() {
		Callee c;
		c = new Callee();

		System.out.println(new Callee().return10() + c.return20());
	}
}

class Callee {
	public int return10() {
		return 10;
	}

	public int return20() {
		return this.return10() + this.return10();
	}
}

