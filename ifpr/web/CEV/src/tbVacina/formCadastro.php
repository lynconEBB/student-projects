<meta charset="utf-8">
<html>
   <head>
      <title>Cadastro de Vacinas</title>
      <link rel="stylesheet" type="text/css"  href="../CSS/tbvacinacao.css" />
   </head>
   <body>
	  <h1>Cadastro de Vacinas</h1>
      <form action="crud.php" method="post" enctype="multipart/form-data">

         <br> Nome: <input type=TEXT  name= nome>
         <br> Duração: <input type=TEXT  name= Duracao>
         <br> Descrição: <input type=TEXT  name= Descricao>
         <br> Idade Minima: <input type="NUMBER"  name=" idadeMinima">
         <br> Idade Maxima: <input type=TEXT  name= idadeMaxima>
         <input type="hidden" name="acao" value="1">
         <br>
         <input type="submit" value="Salvar">
         <br><br>
         <h3><a href='../menu.php'>Voltar para o Menu</a></h3>
      </form>
   </body>
</html>
