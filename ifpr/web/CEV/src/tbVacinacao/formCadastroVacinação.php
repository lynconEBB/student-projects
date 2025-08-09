<!DOCTYPE html>
<html lang="pt-br">
<head>
    <title>Cadastro de Vacinação</title>
     <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
</head>
<body>
    <h1>Confirmar Dados de Vacinação</h1>
    <?php
        require_once "../tbPaciente/crudPaciente.php";
        $paciente=new CrudPac();
        $queryPac=$paciente->retornarNome($_REQUEST["idPac"]);

        require_once "../tbVacina/crud.php";
        $vacina=new Crud();
        $queryVac=$vacina->retornarNome($_REQUEST["idVac"]);

        echo "<table border=1>";
        echo "<tr>
            <th> Paciente </th>
            <th> Vacina </th>
        </tr>";
            echo "<tr>";
            while($arrayPac=mysqli_fetch_object($queryPac)){
                echo "<td>".$arrayPac->Nome."</td>";
            }
            while($arrayVac=mysqli_fetch_object($queryVac)){
                echo "<td>".$arrayVac->Nome."</td>";
            }
                
            echo"</tr>";
        echo "<table>";
?>
<div id="data">
    <form action="crudVacinacao.php" method="post" enctype="multipart/form-data">
         <br> Data(AAAA-MM-DD): <input type=TEXT  name='Data'>
         <input type="hidden" name="idPac" value="<?php echo $_REQUEST["idPac"]?>">
         <input type="hidden" name="idVac" value="<?php echo $_REQUEST["idVac"]?>">
         <input type="hidden" name="acao" value="1">
         <br><br><input type="submit" value="Salvar">
    </form>
</div>
</body>
</html>


