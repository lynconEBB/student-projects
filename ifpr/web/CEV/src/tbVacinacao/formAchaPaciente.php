<meta charset="utf-8">
<html lang="pt-br">
    <head>
        <title>Escolher Paciente</title>
       <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
    </head>
    <body> 
        <h1> Escolha de qual paciente a carteira será exibida?</h1>
        <?php
            require_once $_SERVER['DOCUMENT_ROOT'].'/tbPaciente/crudPaciente.php';
            $obj=new CrudPac();
            $query=$obj->listar();
            $num=mysqli_num_rows($query);

            echo "<table border=1>";
            echo "<tr>
                <th> Nome </th>
                <th> Visualizar </th>
            </tr>";
            while($array=mysqli_fetch_object($query)) {
                echo "<tr>";
                    echo "<td>".$array->Nome."</td>";
                    echo "<td><a href='exibeCarteira.php?idPac=".$array->id."'>Escolher</a></td> 
                </tr>";
            }
            echo "<table>";
        ?>
   </body>
</html>
