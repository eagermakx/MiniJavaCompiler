class Program {
	public static void main () {
		int var;
		var = 1;
		System.out.println(var);

		{
			{
				System.out.println(var);
				
				int var;
				var = 3;
				System.out.println(var);
			}

			System.out.println(var);

			int var;
			var = 2;
			System.out.println(var);
		}

		System.out.println(var);
	}
}