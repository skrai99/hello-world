<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ page import="com.teamcenter.soa.client.*" %>
<%@ page import="com.teamcenter.clientx.*" %>
<%@ page import="com.teamcenter.schemas.soa._2006_03.exceptions.InvalidCredentialsException" %>
<%@ page import="com.teamcenter.soa.client.model.strong.User" %>
<%@ page import="org.apache.commons.httpclient.HttpState" %>
<%@ page import="com.teamcenter.services.strong.core.SessionService" %>
<%@ page import="com.teamcenter.services.strong.core._2006_03.Session.LoginResponse" %>
<%@ page import="com.teamcenter.services.strong.core._2007_01.Session" %>
<%@ page import="com.teamcenter.soa.exceptions.CanceledOperationException" %>
<%@ page import="java.util.Random" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>BWPartQuery Form - Welcome</title>
</head>
<body>

<H3>Welcome, <%= request.getParameter("activeUsername")%> </H3>

<fieldset style="display:inline;margin-left:auto;margin-right:auto">
<legend>BW Part Query </legend>
<form id="form1" method="POST" action="BWPartQuery.jsp?uid=<%=request.getParameter("activeUid")%>">
<table BORDER="0">
<tr>
	<td>Enter Part Number</td>
	<td><INPUT TYPE="TEXT" NAME="PARTID" SIZE="20"></td>
</tr>

</table>
<input type="SUBMIT" name="Query Part" value="Query Part"/>
</form>
</fieldset>

<br></br>



</body>
</html>