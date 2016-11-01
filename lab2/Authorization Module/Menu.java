import java.util.Scanner;


public class Menu {
	public static void main(String[] args)
	{
		Authorization auth = new Authorization();
		Scanner reader = new Scanner(System.in);  // Reading from System.in
		//select a user, select a file, tell the user to select an action (rwx)
		//output if they have access or not
	
		while(true){	
			char menu; 			
			int user, file;
			String permissions, role, perm_choice;;
			System.out.println("A	-ACL/RBAC program");
			System.out.println("B	-Assign a user a role");
			System.out.println("C	-Change a user's file permission");
			System.out.println("D	-Show user's role and permission for a file");
			System.out.println("E	-Exit");
			System.out.println("Enter a selection: ");
			menu = reader.next().charAt(0); 		
			switch (menu)
			{
			case 'A':
				System.out.println("Enter the User number (1-5)");
				user = reader.nextInt();
				System.out.println("Enter the File number (0-5)");
				file = reader.nextInt();
				System.out.println("Do you want to Read (r) Write (w) or Execute (x)?");
				perm_choice = reader.next();
				if(!(perm_choice.equals("r")) && !(perm_choice.equals("w")) && !(perm_choice.equals("x")))
				{
					System.out.println("Invalid input, returning...");
					break;
				}	
				if(auth.checkPerm(auth.getUser(user), file, perm_choice))				
					System.out.println("Your '" + perm_choice + "' access request to the file '" + file + "' is granted");				
				else				
					System.out.println("You only have '" + auth.getUser(user).getPermission(file) + "' access to the file '" + file + "'");								
				break;
			case 'B':
				System.out.println("Enter the User number (1-5)");
				user = reader.nextInt();
				System.out.println("Enter a Role: Manager, Technical Staff, Sales");
				role = reader.next();				
				auth.assignRole(auth.getUser(user), role);				
				break;
			case 'C':
				System.out.println("Enter the User number (1-5)");
				user = reader.nextInt();
				System.out.println("Enter the File number (0-5)");
				file = reader.nextInt();
				System.out.println("Pick new permissions");
				permissions = reader.next();							
				auth.getUser(user).setPermission(file, permissions);				
				break;
			case 'D':
				System.out.println("Enter the User number (1-5)");
				user = reader.nextInt();
				System.out.println("Enter the File number (0-5)");
				file = reader.nextInt();
				System.out.println("Role: "+ auth.getUser(user).getRole());
				System.out.println("Permission: "+ auth.getUser(user).getPermission(file));
				break;
			case 'E':
				System.out.println("Buh-Bye");
				System.exit(0);
			default:	
				System.out.println("Can't you read?");
				break;
			}			
		}
	}	
}
