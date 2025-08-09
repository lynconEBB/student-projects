<meta charset="utf-8">
<html>
    <head>
        <title>Informar Paciente</title>
        <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
    </head>
    <body> 
        <h1> Escolha o Paciente</h1>
        <?php
            require_once '../tbPaciente/crudPaciente.php';
            $obj=new CrudPac();
            $query=$obj->listar();
            $num=mysqli_num_rows($query);

            echo "<table border=1>";
            echo "<tr>
                <th> Codigo </th>
                <th> Data de Nascimento </th>
                <th> Cidade </th>
                <th> Bairro </th>
                <th> Nome </th>
                <th> CPF </th>
                <th> RG </th>
                <th> Número </th>
                <th> Observações </th>
                <th> Rua </th>
                <th> Escolha </th>
            </tr>";
            while($array=mysqli_fetch_object($query)){
            echo "<tr>";
                echo "<td>".$array->id."</td>";
                echo "<td>".$array->DataNascimento."</td>";
                echo "<td>".$array->Cidade."</td>";
                echo "<td>".$array->Bairro."</td>";
                echo "<td>".$array->Nome."</td>";
                echo "<td>".$array->CPF."</td>";
                echo "<td>".$array->RG."</td>";
                echo "<td>".$array->Numero."</td>";
                echo "<td>".$array->Observacoes."</td>";
                echo "<td>".$array->Rua."</td>";
                echo "<td><a href='formInformaVacina.php?idPac=".$array->id."'>Escolher</a></td> 
            </tr>";
            }
            echo "<table>";
        ?>
   </body>
</html>
