<?php
require_once '../Controller/ValidacaoLogin.php';
if(ValidacaoLogin::verificar()==true) {
    echo "<a href='formCadastroVenda.php'>Cadastro</a><br>";
    echo "<a href='formEscolheNota.php'>Relatório</a>";
}
?>