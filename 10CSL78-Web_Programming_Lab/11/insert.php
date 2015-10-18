<!DOCTYPE html>
<html>
<head>
	<title>Insertion into Table</title>
</head>
<body>
<?php

$name = $_POST["ins_name"];
$adr1 = $_POST["ins_adr1"];
$adr2 = $_POST["ins_adr2"];
$email = $_POST["ins_email"];

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

	echo "Connection established.<br>Inserting details.<br>";

	$sql = "insert into prog11(`name`,`addr`,`addr_2`,`email`) values ('$name', '$adr1', '$adr2', '$email');";

	if ($conn->query($sql) === TRUE) {
	    echo "Row ('$name', '$adr1', '$adr2', '$email') inserted successfully.<br>";
	} else {
	    echo "An error occurred on insertion:<br><br><i><b>" . $sql . "<br>" . $conn->error . "</b></i><br><br>";
	}


	$conn->close();
	echo "Connection closed.";
}
?>
<br><br><center>
<form action="http://localhost/11.php">
	<input type="submit" value="Go Back">
</form>
</center>
</body>
</html>