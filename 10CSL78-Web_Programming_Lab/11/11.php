<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" encoding="utf-8" style="margin:0; padding:0;">
<head>
	<title>Program 11 | Web Programming Lab</title>
</head>
<body style="margin:0; padding:0;">

<table width="100%" align="center"><tr><td>
<center><h3>Insert Details</h3></center>
<form action="insert.php" method="POST">
	<table width="100%">
		<tr>
			<td width="35%" align="right">Name:</td>
			<td width="65%" align="left"><input type="text" name="ins_name" required width="100%" /></td>
		</tr>
		<tr>
			<td align="right">Address Line 1:</td>
			<td align="left"><input type="text" name="ins_adr1" width="100%" /></td>
		</tr>
		<tr>
			<td align="right">Address Line 2:</td>
			<td align="left"><input type="text" name="ins_adr2" width="100%" /></td>
		</tr>
		<tr>
			<td align="right">Email:</td>
			<td align="left"><input type="text" name="ins_email" width="100%" required /></td>
		</tr>
		<tr>
			<td align="center" colspan="2"><br /><input type="submit" value="Submit" width="100%" /><input type="reset" value="Reset" width="100%" /></td>
		</tr>
	</table>
</form>
<br /><br /><hr /><br />
</td></tr><tr><td>

<center><h3>Search By Name</h3></center>
<form action="search.php" method="GET">
	<table width="100%">
		<tr>
			<td width="35%" align="right">Name:</td>
			<td width="65%" align="left"><input type="text" name="search_name" required width="100%" /></td>
		</tr>
		<tr>
			<td align="center" colspan="2"><br /><input type="submit" value="Submit" width="100%" /><input type="reset" value="Reset" width="100%" /></td>
		</tr>
	</table>
</form>

</td></tr></table>

</body>
</html>