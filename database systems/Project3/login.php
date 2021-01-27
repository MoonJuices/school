<?php

session_start();

$_SESSION["host"] = $_POST["host"];
$_SESSION["user"] = $_POST["user"];
$_SESSION["passw"] = $_POST["password"];
$_SESSION["dbname"] = $_POST["user"];


echo "Attempting to connect to DB server: $_SESSION[host] ...";
$conn = mysqli_connect($_SESSION["host"], $_SESSION["user"], $_SESSION["passw"], $_SESSION["dbname"]);

if (!$conn)
{
	die("Could not connect:".mysqli_connect_error());
}	
else
{
	echo " connected!<br>";
	echo "<a href=mainmenu.html>Go To Main Menu</a>";
}

mysqli_close($conn);

?>
