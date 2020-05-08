class Program {
	public static void main () {
		int modified;
		modified = 0;

		{
		  int modified;
			modified = 1;
		}

		System.out.println(modified);
	}
}