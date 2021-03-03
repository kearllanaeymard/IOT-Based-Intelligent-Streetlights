<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IOT</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <link href="main.css" rel="stylesheet">
</head>
<body>

<?php
    //Connect to database and create table
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "pupiotdata";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
        echo "<a href='install.php'>If first time running click here to install database</a>";
    }
?> 

    
<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
  <div class="container">
    <a class="navbar-brand" href="/iot/index.php">IOT Development</a>
    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
      <div class="navbar-nav">
        <a class="nav-link" aria-current="page" href="/iot/index.php">Home</a>
        <li class="nav-item dropdown">
          <a class="nav-link dropdown-toggle active" href="#" id="navbarDropdownMenuLink" role="button" data-bs-toggle="dropdown" aria-expanded="false">
            Tables
          </a>
          <ul class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">
            <li><a class="dropdown-item" href="/iot/activationdata.php">Street Lights</a></li>
            <li><a class="dropdown-item" href="/iot/stationdata.php">Stations</a></li>
          </ul>
        </li>
      </div>
    </div>
  </div>
</nav>

<br>

<div class="container">
    <?php 
    $sql = "SELECT * FROM logs ORDER BY id DESC";
    if ($result=mysqli_query($conn,$sql))
    {
      // Fetch one and one row
      echo "<table class='table table-striped table-hover'>";
      echo "<thead>";
      echo "<tr><th>Stations</th><th>Date</th><th>Time</th></tr>";
      echo "</thead>";
      echo "<tbody>";
      while ($row=mysqli_fetch_row($result))
      {
        echo "<tr>";
        echo "<td>".$row[1]."</td>";
        echo "<td>".$row[2]."</td>";
        echo "<td>".$row[3]."</td>";
        echo "</tr>";
      }
      echo "</tbody>";
      echo "</table>";
      // Free result set
      mysqli_free_result($result);
    }

    mysqli_close($conn);
?>
</div>

<br><br><br><br><br><br><br><br><br>
<!-- Site footer -->
<footer class="site-footer">
      <div class="container">
        <div class="row">
          <div class="col-sm-12 col-md-6">
            <h6>About</h6>
            <p class="text-justify">IOT <i>Intelligent Street lights </i> are composed of special features which enables the automation of the streetlights. These IoT Intelligent lights can ensure low power consumption than the traditional streetlights. Lastly, these street lights consist of database and user interface which can lessen manpower and enables remote monitoring.</p>
          </div>

          <div class="col-xs-6 col-md-3">
            <h6>Members</h6>
            <ul class="footer-links">
              <li>E. Baltazar</li>
              <li>S. Borda</li>
              <li>G. Cruz</li>
              <li>J. Lincopines</li>
              <li>A.J. Llanzana</li>
              <li>S. Macatangay</li>
              <li>A.N. Opeña</li>
            </ul>
          </div>

          <div class="col-xs-6 col-md-3">
            <h6>Quick Links</h6>
            <ul class="footer-links">
              <li><a href="/iot/activationdata.php">Street lights Logs</a></li>
              <li><a href="/iot/stationdata.php">Station Logs</a></li>
            </ul>
          </div>
        </div>
        <hr>
      </div>
      <div class="container">
        <div class="row">
          <div class="col-md-8 col-sm-6 col-xs-12">
            <p class="copyright-text">Copyright &copy; 2021 All Rights Reserved</p>
          </div>

        </div>
      </div>
</footer>


<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/js/bootstrap.bundle.min.js" integrity="sha384-b5kHyXgcpbZJO/tY9Ul7kGkf1S0CWuKcCD38l8YkeH8z8QjE0GmW1gYU5S9FOnJ0" crossorigin="anonymous"></script>
</body>
</html>