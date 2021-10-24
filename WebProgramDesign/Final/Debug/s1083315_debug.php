      <?php
	 $ID = $_POST["ID"];
     $IV = $_POST["IV"];
	 $now = date("Y-m-d H:i:s");
	 $query = 'SELECT * FROM `debug` WHERE ".$now." BETWEEN `starttime` AND `endtime`';
	 if (isset($_POST["ID"]) and ($ID >=100 and $ID<=150))
		{$query += ' and `ID` = ".$ID."';}
	 if (isset($_POST["IV"]) and ($IV >=0 and $IV<=100) and $IV!="")
		{$query += ' and `IV` >= ".$IV."';}
	 if ( !( $database = mysqli_connect( "localhost", "class", "class" ) ) )
            die( "Could not connect to database </body></html>" );
         if ( !mysqli_select_db( $database, "1081Web" ) )
            die( "Could not open products database </body></html>" );
         if ( !( $result = mysqli_query( $database,$query  ) ) )
         {
            print( "<p>Could not execute query! $query</p>" );
            die( /*mysqli_error($result) .*/ "</body></html>" );
         }
         mysqli_close( $database );
      ?>
         <?php
            while ( $row = mysqli_fetch_row( $result ) )
            {
               foreach ( $row as $value )
		{
		    print( "$value " );
		}
		print( "<br>" );
            }
         ?>

