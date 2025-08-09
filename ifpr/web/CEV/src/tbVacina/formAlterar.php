<?php 
   require_once 'crud.php';
   $obj=new Crud();
   $query=$obj->listaPorId($_REQUEST["id"]);
   $vacina=mysqli_fetch_object($query);
?>
<meta charset="utf-8">
<html>
   <head>
      <title>Cadastro de Vacinas - Alteração </title>
      <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
   </head>
   <body>	
      
      <h1>Alteração de Vacina  </h1>
      <form action="crud.php" method="post">

         <br> Nome:  <input type=TEXT  name= nome value = "<?php echo $vacina->Nome; ?>">
         <br> Duração: <input type=TEXT  name= Duracao value = "<?php echo $vacina->Duracao; ?>">
         <br> Descrição: <input type=TEXT  name= Descricao value = "<?php echo $vacina->Descricao; ?>">
         <br> Idade Minima: <input type=TEXT  name= idadeMinima value = "<?php echo $vacina->IdadeMinima; ?>">
         <br> Idade Maxima: <input type=TEXT  name= idadeMaxima value = "<?php echo $vacina->IdadeMaxima; ?>">
         <input type="hidden" name="acao" value="4">
         <input type="hidden" name="id" value="<?php echo $_REQUEST["id"]?>">
         <br><input type="submit" value="Salvar">
         <br><br>
         <h3><a href='../menu.php'>Voltar para o Menu</a></h3>
      </form>
   </body>
</html>
