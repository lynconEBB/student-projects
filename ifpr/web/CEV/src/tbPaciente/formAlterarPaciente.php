<?php 
   require_once 'crudPaciente.php';
   $obj=new CrudPac();
   $query=$obj->listaPorId($_REQUEST["id"]);
   $paciente=mysqli_fetch_object($query);
?>
<meta charset="utf-8">
<html>
   <head>
      <title>Cadastro de Paciente - Alteração </title>
      <link rel="stylesheet" type="text/css"  href="../css/tbvacinacao.css" />
   </head>
   <body>	
      <h1>Cadastro de Paciente - Alteração</h1>
      <form action="crudPaciente.php" method="post">

         <br> Nome do Paciente:  <input type=TEXT  name= Nome value = "<?php echo $paciente->Nome; ?>">
         <br> Email : <input type = TEXT name= Email value = "<?php echo $paciente->Email; ?>">
         <br> Data de Nascimento: <input type=TEXT  name= DataNascimento value = "<?php echo $paciente->DataNascimento; ?>">
         <br> Cidade: <input type=TEXT  name= Cidade value = "<?php echo $paciente->Cidade; ?>">
         <br> Bairro: <input type=TEXT  name= Bairro value = "<?php echo $paciente->Bairro; ?>">
         <br> Rua: <input type=TEXT  name= Rua value = "<?php echo $paciente->Rua; ?>">
         <br> CPF: <input type=TEXT  name= CPF value = "<?php echo $paciente->CPF; ?>">
         <br> RG: <input type=TEXT  name= RG value = "<?php echo $paciente->RG; ?>">
         <br> Número: <input type=TEXT  name= Numero value = "<?php echo $paciente->Numero; ?>">
         <br> Observações: <input type=TEXT  name= Observacoes value = "<?php echo $paciente->Observacoes; ?>">

         <input type="hidden" name="acao" value="4">
         <input type="hidden" name="id" value="<?php echo $_REQUEST["id"]?>">
         <br><br><input type="submit" value="Salvar">
         <h3><a href='../menu.php'>Voltar para o Menu</a></h3>
      </form>
   </body>
</html>
