<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "pupiotdata";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    //Get current date and time
    date_default_timezone_set('Asia/Manila');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");

    if(!empty($_GET['streetlights']))
    {
    	$station = $_GET['streetlights'];

	    $sql = "INSERT INTO ldr (streetlights, Date, Time)
		
		VALUES ('".$station."', '".$d."', '".$t."')";

		if ($conn->query($sql) === TRUE) {
		    echo "Data Recorded Successfully";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>