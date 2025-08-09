<meta charset="utf-8">
<html lang="pt-br">
   <head>
      <title>Cadastro de Pacientes</title>
      <link rel="stylesheet" type="text/css"  href="../css/tbvacinacao.css" />
   </head>
   <body>
	  <h1>Cadastro de Pacientes</h1> 
      <form action="crudPaciente.php" method="post" enctype="multipart/form-data">
         <br> Nome do Paciente:  <input type=TEXT  name= Nome>
         <br> Senha : <input type=password name=Senha>
         <br> Email : <input type= TEXT name= Email>
         <br> Data de Nascimento: <input type=TEXT  name= DataNascimento>
         <br> Cidade: <input type=TEXT  name= Cidade>
         <br> Bairro: <input type=TEXT  name= Bairro>
         <br> Rua: <input type=TEXT  name= Rua>
         <br> CPF: <input type=TEXT  name= CPF>
         <br> RG: <input type=TEXT  name= RG>
         <br> Número: <input type=TEXT  name= Numero>
         <br> Observações: <input type=TEXT  name= Observacoes>

         <input type="hidden" name="acao" value="1">
         <br><br><input type="submit" value="Salvar">
         <h3>
             <a href='../menu.php'>Voltar para o Menu</a>
         </h3>
      </form>
   </body>
</html>
