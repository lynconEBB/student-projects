<?php
require_once '../Controller/ValidacaoLogin.php';
if(ValidacaoLogin::verificar()==true) {
    echo "<a href='../View/formCadastroPessoa.php'>Cadastro</a><br>";
    echo "<a href='../View/relatorioGeralPessoa.php'>Relatório</a>";
}
