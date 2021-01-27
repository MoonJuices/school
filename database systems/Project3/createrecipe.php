<?php

session_start();

//variables from post
$recipename = $_POST["recipename"];
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

//create tables if not exists
$queryString = "create table if not exists Recipes_T (RecipeName char(100), Ingredient char(100), Quantity int, primary key (RecipeName, Ingredient))";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error creating table: " . mysqli_error($conn));

$queryString = "create table if not exists Inventory_T (Ingredient char(100), Quantity int, primary key (Ingredient))";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error creating table: " . mysqli_error($conn));

$queryString = "select RecipeName, Ingredient from Recipes_T where RecipeName = \"$recipename\" and Ingredient = \"$ingredient\"";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error in Query: " . mysqli_error($conn));

$row = mysqli_fetch_assoc($status);
$result1 = $row["RecipeName"];
$result2 = $row["Ingredient"];

//if the recipe name and ingredient combo already exists, update the quantity
if($recipename==$result1&&$ingredient==$result2)
{
	$queryString = "update Recipes_T set Quantity = $quantity where RecipeName = \"$recipename\" and Ingredient = \"$ingredient\"";
	$status = mysqli_query($conn, $queryString);
	if (!$status)
    		die("Error Updating: " . mysqli_error($conn));
	echo "Ingredient Quantity Updated!<br>";

}
else//if the recipe name and ingredient combo does not exist, insert into table
{
	$queryString = "insert into Recipes_T values(\"$recipename\",\"$ingredient\",$quantity)";
	$status = mysqli_query($conn, $queryString);
	if(!$status)
		die("Error Inserting: " . mysqli_error($conn));
	echo "Recipe added!<br>";

}

$queryString = "select Ingredient from Inventory_T where Ingredient = \"$ingredient\"";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error in Query: " . mysqli_error($conn));

$row = mysqli_fetch_assoc($status);
$result = $row["Ingredient"];

//if the ingredient did not exist in inventory, make new ingredient with quantity 0
if($ingredient!=$result)
{
	$queryString = "insert into Inventory_T values(\"$ingredient\", 0)";
	$status = mysqli_query($conn, $queryString);
	if (!$status)
    		die("Error Inserting: " . mysqli_error($conn));
	echo "Ingredient added!<br>";

}

mysqli_close($conn);

?>

<a href=mainmenu.html>Go To Main Menu</a>