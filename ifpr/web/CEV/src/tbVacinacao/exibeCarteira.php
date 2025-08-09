<meta charset="utf-8">
<html>
    <head>
        <title>Carteira de Vacinação</title>
        <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
    </head>
    <body> 
        <h1> Carteira de Vacinação</h1>
        <?php
            require_once 'crudVacinacao.php';
            $obj=new Crud();
            $queryVac=$obj->listaPorIdPaciente();
            $queryPac=$obj->retornarNome();

            echo "<table>";
            echo "<tr>
               <th colspan='3'>Paciente</th>
            </tr>
            <tr>
                <th>ID</th>
                <th colspan='2'>Nome</th>
            </tr>";
            while($arrayPac=mysqli_fetch_object($queryPac)){
            echo "<tr>
                <td>".$_REQUEST["idPac"]."</td>
                <td colspan='2'>".$arrayPac->Nome."</td>
            </tr>";
            }
            echo "<tr>
               <th colspan='3'>Vacinações</th>
            </tr>
            <tr>
                <th>ID</th>
                <th>Nome Vacina</th>
                <th>Data</th>
            </tr>";
            while($arrayVac=mysqli_fetch_object($queryVac)){
            echo "<tr>
                <td >".$arrayVac->id."</td>
                <td >".$arrayVac->Nome."</td>
                <td >".$arrayVac->Data."</td>
            </tr>";
            }
            echo "</table>";
        ?>
        <h3><a href="../menu.php">Voltar</a></h3>
   </body>
</html>
