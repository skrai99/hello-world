<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ page import="java.util.*" %>
<%@ page import="com.teamcenter.webapp.util.*" %>
<%@ page import="com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException" %>
<%@ page import="com.teamcenter.soa.client.*" %>
<%@ page import="com.teamcenter.soa.client.model.*" %>
<%@ page import="com.teamcenter.services.strong.core.*" %>
<%@ page import="com.teamcenter.services.strong.query._2007_09.SavedQuery.*" %>
<%@ page import="com.teamcenter.soa.client.model.strong.WorkspaceObject" %>
<%@ page import="com.teamcenter.soa.client.model.strong.User" %>
<%@ page import="com.teamcenter.schemas.soa._2006_03.exceptions.*" %>
<%@ page import="com.teamcenter.soa.exceptions.NotLoadedException" %>
<%@ page import="com.teamcenter.services.strong.query._2007_06.SavedQuery.SavedQueryResults" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<%@page import="com.teamcenter.services.strong.query._2007_06.SavedQuery"%><html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>HelloTcWeb - Query Item</title>
</head>
<body>
<%!
		String inputPartId;
%>

	<% 
	 	inputPartId = request.getParameter("PARTID");
	    System.out.println("updated by sarwan"+inputPartId);
	%>
<%	

	
    Query items = new Query();
	String uid = request.getParameter("uid");
	Connection connection = (Connection) session.getAttribute(uid + "connection");
	DataManagementService dmService = DataManagementService.getService(connection);
	SavedQuery.SavedQueryResults found = items.queryItems(connection);
	String errorMsg="";
	ModelObject[] result = found.objects;
    String[] objUids = new String[result.length];
    for (int i = 0; i < result.length; i++)
    {
        objUids[i] = result[i].getUid();
        System.out.println("MODEL Objects"+objUids[i]);
    }

    ServiceData data = dmService.loadObjects(objUids);
	ModelObject[] modelArray = new ModelObject[data.sizeOfPlainObjects()];

	for (int i = 0; i < data.sizeOfPlainObjects(); i++)
	{
	    modelArray[i] = data.getPlainObject(i);
	}

    DisplayQueriedItems(modelArray, connection);
%>
	
<%!
	String[] TableColumns = { "Name", "Owner", "Last Modified" };
    ArrayList<String[]> TableRows = new ArrayList<String[]>();
    String errorMsg="";

		
	public void DisplayQueriedItems(ModelObject[] objects, Connection connection)
    {
         if (objects == null)
            return;

        // Ensure that the referenced User objects that we will use below are loaded
        getUsers(objects, connection);
		

    	
        for (int i = 0; i < objects.length; i++)
        {
            if (!(objects[i] instanceof WorkspaceObject))
                continue;

            WorkspaceObject wo = (WorkspaceObject)objects[i];
            try
            {
            	
            
               
		           	String name = wo.get_object_string();
		            User owner = (User)wo.get_owning_user();
		            
		            Calendar lastModified = wo.get_last_mod_date();
		            
		            //Calendar itemCreationDate  = wo.get_creation_date();
		            
		            String[] row = { name, owner.get_user_name(), String.format("%1$tm %1$te,%1$tY", lastModified) };
		            
		            //System.out.println("DATE Modified : "+ String.format("%1$te/%1$tm/%1$tY", lastModified) );
		            //System.out.println("DATE Created  : "+ String.format("%1$te/%1$tm/%1$tY", dateCreated) );
		            
		            if(name.contains(inputPartId))
		            {
		            	TableRows.add(row);
		            }
               
                }
            catch (NotLoadedException e)
            {
             	e.printStackTrace();
            	// Could do a DataManagementService.getProperties call at this point
            }
        }
    }

	private void getUsers(ModelObject[] objects, Connection connection)
	{
	    if (objects == null)
	        return;

	    DataManagementService dmService = DataManagementService.getService(connection);
	    ArrayList<User> unKnownUsers = new ArrayList<User>();
	    for (int i = 0; i < objects.length; i++)
	    {
	        if (!(objects[i] instanceof WorkspaceObject))
	            continue;

	        WorkspaceObject wo = (WorkspaceObject)objects[i];

	        User owner = null;
	        try
	        {
	            owner = (User) wo.get_owning_user();
	            String userName = owner.get_user_name();
	        }
	        catch (NotLoadedException e)
	        {
	            if (owner != null)
	                unKnownUsers.add(owner);
	        }
	    }
	    User[] users = new User[unKnownUsers.size()];
	    unKnownUsers.toArray(users);
	    String[] attributes = { "user_name" };


	    // *****************************
	    // Execute the service operation
	    // *****************************
	    dmService.getProperties(users, attributes);
	}
%>

<h3>Query Item</h3>
<table width ="60%" border="2" style="left: 36px; position: relative">
<tr>
<%
    for (int i=0; i < TableColumns.length; i++ )
    {
%>
    <th><%=TableColumns[i]%></th>
<%
    }
%>
</tr>
<%
    for ( String[] row : TableRows )
    {
%>
<tr>
	<td><%=row[0]%></td>
	<td><%=row[1]%></td>
	<td><%=row[2]%></td>
</tr>
<%
    }
%>
</table>


<SCRIPT type="text/javascript">

function submitAction(actionName, activeUid)
{
  if ( actionName == "logout" )
  {
     document.forms[0].action="Logout.jsp?uid=" + activeUid;
  }

  if ( actionName == "deleteItem" )
  {
     document.forms[0].action="Delete.jsp?uid=" + activeUid;
  }
  document.forms[0].submit();
}

</SCRIPT>

<form id="theForm" method="POST">

<%-- <input type="SUBMIT" name="Delete Item" value="Delete Item" onClick="submitAction('deleteItem','<%=uid%>')"/> --%>


<input type="SUBMIT" name="Logout" value="Logout" onClick="submitAction('logout','<%=uid%>')"/>
</form>



</body>
</html>