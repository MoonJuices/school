<?php

session_start();

//variables from post
$ingredient = $_POST["ingredient"];
$quantity = $_POST["quantity"];

//connect to database through session
echo "Attempting to connect to DB server: $_SESSION[host] ...";
$conn = mysqli_connect($_SESSION["host"], $_SESSION["user"], $_SESSION["passw"], $_SESSION["dbname"]);

if (!$conn)
{
	die("Could not connect:".mysqli_connect_error());
}	
else
{
	echo " connected!<br>";
}

//create table if not exists
$queryString = "create table if not exists Inventory_T (Ingredient char(100), Quantity int, primary key (Ingredient))";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error creating table: " . mysqli_error($conn));

$queryString = "select Ingredient from Inventory_T where Ingredient = \"$ingredient\"";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error in Query: " . mysqli_error($conn));

$row = mysqli_fetch_assoc($status);
$result = $row["Ingredient"];

//check if ingredient exists
if($ingredient==$result)//if ingredient exists, update value
{
	$queryString = "update Inventory_T set Quantity = Quantity + $quantity where Ingredient = \"$ingredient\"";
	$status = mysqli_query($conn, $queryString);
	if (!$status)
    		die("Error Updating: " . mysqli_error($conn));
	echo "Ingredient Quantity Updated!<br>";

}
else//if ingredient does not exist, insert value
{
	$queryString = "insert into Inventory_T values(\"$ingredient\", $quantity)";
	$status = mysqli_query($conn, $queryString);
	if (!$status)
    		die("Error Inserting: " . mysqli_error($conn));
	echo "Ingredient added!<br>";

}

mysqli_close($conn);

?>

<a href=mainmenu.html>Go To Main Menu</a>