<?php
    session_start();
    if(!isset($_SESSION["autenticado"]) || $_SESSION["autenticado"] != TRUE) {
        echo "Acesso não autorizado!<br>";
        echo "Por gentileza, faça o seu login <a href=\"login.php\">clicando aqui</a>.";
        exit();
    } else {
        echo "Você está logado como usuário: ".$_SESSION["usuario"];
?>

<html lang="pt-br">
    <head>
        <meta charset="utf-8">
        <title>Menu CEV - Carteira Eletronica de Vacinação</title>
        <link rel="stylesheet" type="text/css"  href="css/tbvacinacao.css" />
    </head>
    <body>
        <h1>CEV - Carteira Eletrônica de Vacinação</h1>
        <br>
        <h4><a href="tbPaciente/relatorioGeralPaciente.php">Menu Paciente</a></h4>
        <h4><a href="tbVacina/relatorioGeral.php">Menu Vacina</a></h4>
        <h4><a href="tbVacinacao/menuVacinacao.php">Menu Vacinação</a></h4>
    </body>
</html>

<?php
  }
?>
