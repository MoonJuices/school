<?php

session_start();

//variables from post
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

$queryString = "select Ingredient, Quantity from Recipes_T where RecipeName = \"$recipename\"";
$status = mysqli_query($conn, $queryString);
if (!$status)
    die("Error in Query: " . mysqli_error($conn));

echo "Recipe: ".$recipename."<br>";

echo "<table border=1>";
echo "<tr> <th>Ingredient</th> <th>Quantity</th> </tr>";

while($row = mysqli_fetch_assoc($status))
    {
        echo "<tr> <td>".$row["Ingredient"]."</td>".  
                  "<td>".$row["Quantity"]."</td> </tr>";
    }

echo "</table>";

mysqli_close($conn);

?>

<a href=mainmenu.html>Go To Main Menu</a>