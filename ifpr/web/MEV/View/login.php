<html>
    <head>
        <meta charset="utf-8">
        <title>Login de Cliente</title>
    </head>
    <body>
        <h3>Preencha os campos abaixo</h3>
        <FORM action="../Controller/ValidacaoLogin.php?action=login" method="POST">
            Digite o seu nome: 
            <input type="text" name="CAMPO_USUARIO"><BR>
            Digite sua senha: 
            <input type="password" name="CAMPO_SENHA"><BR>
            <input type="SUBMIT" value="Autenticar">
            <input type="reset" value="Limpar">
        </FORM>
    </body>
</html>