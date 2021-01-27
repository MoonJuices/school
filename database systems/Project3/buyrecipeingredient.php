<?php

session_start();

//values from post
$recipename = $_POST["recipename"];

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
$queryString = "create table if not exists Recipes_T (RecipeName char(100), Ingredient char(100), Quantity int, primary key (RecipeName, Ingredient))";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error creating table: " . mysqli_error($conn));

$queryString = "create table if not exists Inventory_T (Ingredient char(100), Quantity int, primary key (Ingredient))";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error creating table: " . mysqli_error($conn));

$queryString = "select * from Recipes_T, Inventory_T where RecipeName = \"$recipename\" and Recipes_T.Ingredient = Inventory_T.Ingredient";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error in Query: " . mysqli_error($conn));

$canbuy = True;

//test if there are enough items for recipe in inventory
while($row = mysqli_fetch_row($status))
{
	if($row[2]>$row[4])
	{
		$canbuy = False;//if not enough items in inventory, can not buy
	}
	//echo $row[2]." ".$row[4]."<br>";
}

//echo $canbuy;

//if can buy, update Inventory_T to new values
if($canbuy)
{
	$queryString = "select * from Recipes_T, Inventory_T where RecipeName = \"$recipename\" and Recipes_T.Ingredient = Inventory_T.Ingredient";
	$status = mysqli_query($conn, $queryString);
	if (!$status)
    		die("Error in Query: " . mysqli_error($conn));
	while($row = mysqli_fetch_row($status))
	{
		//echo $row[2]." ".$row[3]."<br>";
		$queryString2 = "update Inventory_T set Quantity = Quantity - $row[2] where Ingredient = \"$row[3]\"";
		$status2 = mysqli_query($conn, $queryString2);
		if (!$status2)
			die("Error in Update: " . mysqli_error($conn));
	}
	echo "Purchase Succesful!<br>";
}
else
	echo "Purchase Unsuccessful! Not Enough Ingredients In Inventory!<br>";

mysqli_close($conn);

?>

<a href=mainmenu.html>Go To Main Menu</a>