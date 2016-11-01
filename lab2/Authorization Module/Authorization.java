
public class Authorization {

	private Users[] user = new Users[5];
		
	public Authorization(){	
		String[] alcPerm = {"--x","--x","--x","--x","--x","--x"};				
		for(int i = 0; i < 5; i++)
		{	
			int index = i + 1;
			user[i] = new Users("user" + index + "", alcPerm, "No Role Assigned");
		}
	}
	
	public boolean checkPerm(Users u, int filenum, String permInput)
	{//check to see if you can access a file
		if(u.getPermission(filenum).indexOf(permInput) >= 0)//permInput is in the string if not -1
		{
			return true;
		}
		return false;
	}
	
	public void assignPerm(Users u, int filenum, String perm)
	{
		//filenum must be 0-5 (array index)
		u.setPermission(filenum, perm);
	}
	
	public void assignRole(Users u, String r)
	{
		if (!(r.equals("Manager")) && !(r.equals("Technical Staff")) && !(r.equals("Sales")))
		{
			System.out.println("Invalid Role, exiting program");
			System.exit(1);
		}		
		if(r.equals("Manager") && checkRoleConstraint())//check if a manager exists							
			System.out.println("A user is already manager");			
		else
			u.setRole(r);
	}
	
	public boolean checkRoleConstraint()
	{
		for(int i = 0; i< user.length; i++)
		{
			if(user[i].getRole().equals("Manager"))
				return true;
		}
		return false;
	}
	
	public Users getUser(int index)
	{
		if(index > 5 || index < 1)
		{
			System.out.println("Error, invalid user, Exiting...");
			System.exit(1);
		}	
		return user[index];
	}
}
