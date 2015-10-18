<!DOCTYPE html>
<html>
<head>
	<title>Search Results</title>
</head>
<body>
<?php

$name = $_GET["search_name"];

$servername = "localhost";
#change following details accordingly:
$username = "root";
$password = "<password_here>";
$dbname = "wp_lab";


$conn = mysqli_connect($servername, $username, $password, $dbname);

if (!$conn){
	echo "Unable to connect to the mysql server." . $conn->connect_error . "<br>";
}
else{

	echo "Connection established.<br>Searching for '$name' in records.<br>";

	$search_query = "select name, addr, addr_2, email from prog11 where name like '%$name%'";
	$search_result = $conn->query($search_query);

	if ($search_result->num_rows <= 0) {
	    echo "Empty set returned. '$name' was not found.<br>";
	    exit;
	}
}
?>
<center>
<form action="http://localhost/11.php">
	<input type="submit" value="Go Back">
</form>
<br><br>

<table width="100%;">
	<tr>
		<th width="30%" align="left">Name</th>
		<th width="30%" align="left">Address Line 1</th>
		<th width="30%" align="left">Address Line 2</th>
		<th width="10%" align="left">Age</th>
	</tr>
	<?php
		while($row = $search_result->fetch_assoc()) {
			echo "<tr>\n";
        	echo "<td>" . $row["name"]. "</td>\n";
        	echo "<td>" . $row["addr"]. "</td>\n";
        	echo "<td>" . $row["addr_2"]. "</td>\n";
        	echo "<td>" . $row["email"]. "</td>\n";
        	echo "</tr>\n";
    	}
	?>
</table>
</center>

</body>
</html>