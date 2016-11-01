
public class Users {
	
	private String username;
	private String[] filepermissions;
	private String role;
	
	
	public Users(String name, String[] filePerm, String r)
	{
		this.username = name;
		this.filepermissions = filePerm;
		this.role = r;
	}
	
	public String getRole()
	{
		return this.role;
	}

	public void setPermission(int filenum, String perm) 
	{
		filepermissions[filenum] = perm;		
	}
	
	public void setPermission(String r)
	{
		if(r.equals("Manager"))
		{
			filepermissions[0] = "rwx";
			filepermissions[1] = "rwx";
			filepermissions[2] = "rwx";
			filepermissions[3] = "rwx";
			filepermissions[4] = "rwx";
			filepermissions[5] = "rwx";
		}
		else if(r.equals("Technical Staff"))
		{
			filepermissions[0] = "rw";
			filepermissions[1] = "rw";
			filepermissions[2] = "rw";
			filepermissions[3] = "rw";
			filepermissions[4] = "rw";
			filepermissions[5] = "rw";
		}
		else if(r.equals("Sales"))
		{
			filepermissions[0] = "rx";
			filepermissions[1] = "rx";
			filepermissions[2] = "rx";
			filepermissions[3] = "rx";
			filepermissions[4] = "rx";
			filepermissions[5] = "rx";
		}				
	}
	
	public String getPermission(int filenum)
	{
		return this.filepermissions[filenum];
	}
	
	public void setRole(String r)
	{
		this.role = r;
		setPermission(r);
	}
	
	public String getUsername()
	{
		return this.username;
	}
}
