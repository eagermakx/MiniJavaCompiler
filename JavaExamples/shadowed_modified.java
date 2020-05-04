class Program {
	public static void main () {
		int shadowed;
		shadowed = 1;
		int modified;
		modified = 0;

		if (true) {
			int shadowed;
			shadowed = 0;

			modified = 1;
		}

		System.out.println(shadowed);
		System.out.println(modified);
	}
}