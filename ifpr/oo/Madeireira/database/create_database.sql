DROP DATABASE IF EXISTS madeireira;

CREATE DATABASE madeireira CHARSET=UTF8;

USE madeireira;

CREATE TABLE tbtipo(
	id_tipo int NOT NULL AUTO_INCREMENT,
	espessura_tipo decimal(4,2) NOT NULL,
	nome_tipo varchar(45) NOT NULL,
	CONSTRAINT pk_tbtipo PRIMARY KEY (id_tipo)
	)DEFAULT CHARSET=UTF8;
CREATE TABLE tbempresa (
  id_empresa int(11) NOT NULL AUTO_INCREMENT,
  CNPJ_empresa varchar(45),
  rua_empresa varchar(30),
  numero_empresa int(11),
  bairro_empresa varchar(25),
  cidade_empresa varchar(30),
  nome_empresa varchar(45) ,
  telefone_empresa varchar(11),
  CONSTRAINT pk_tbempresa PRIMARY KEY (id_empresa)
) DEFAULT CHARSET=UTF8;

CREATE TABLE tbfuncionario (
  id_func int(11) NOT NULL AUTO_INCREMENT,
  nome_func varchar(20),
  CPF_func char(11) ,
  RG_func char(9) ,
  rua_func varchar(30),
  cidade_func varchar(30),
  numero_func int(11),
  bairro_func varchar(25),
  telefone_func varchar(11),
  CONSTRAINT pk_tbfuncionario PRIMARY KEY (id_func)
)DEFAULT CHARSET=UTF8;

CREATE TABLE tbentregador (
  carteira_de_motorista varchar(11),
  veiculo_entregador varchar(45),
  id_func int(11) NOT NULL,
  CONSTRAINT pk_tbentregador PRIMARY KEY (id_func),
  CONSTRAINT pk_tbFuncionario_tbEntregador FOREIGN KEY (id_func) REFERENCES tbfuncionario (id_func)
  	ON DELETE CASCADE
  	ON UPDATE CASCADE
)DEFAULT CHARSET=UTF8;

CREATE TABLE tbmadeira (
  id_madeira int(11) NOT NULL AUTO_INCREMENT,
  preco_madeira decimal(6,2) NOT NULL,
  id_tipo int NOT NULL,
  nome_madeira varchar(45) NOT NULL,
  CONSTRAINT pk_tbmadeira PRIMARY KEY (id_madeira),
  CONSTRAINT fk_tbtipo_tbmadeira FOREIGN KEY (id_tipo) REFERENCES tbtipo (id_tipo)
  	ON DELETE CASCADE
  	ON UPDATE CASCADE
)DEFAULT CHARSET=UTF8;

CREATE TABLE tbvenda (
  id_venda int(11) NOT NULL AUTO_INCREMENT,
  data_venda date,
  horario_venda time(4),
  total_venda decimal(9,2),
  id_func int(11),
  id_empresa int(11),
  id_entregador int(11),
  CONSTRAINT pk_tbvenda PRIMARY KEY (id_venda),
  CONSTRAINT fk_tbEmpresa_tbVenda FOREIGN KEY (id_empresa) REFERENCES tbempresa (id_empresa)ON DELETE CASCADE	ON UPDATE CASCADE,
  CONSTRAINT fk_tbEntregador_tbVenda FOREIGN KEY (id_entregador) REFERENCES tbentregador (id_func)ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT fk_tbFuncionario_tbVenda FOREIGN KEY (id_func) REFERENCES tbfuncionario (id_func)
  	ON DELETE CASCADE
  	ON UPDATE CASCADE
) DEFAULT CHARSET=UTF8;

CREATE TABLE tbitem (
  preco_madeira decimal(6,2) NOT NULL,
  preco_parcial decimal(6,2) NOT NULL,
  id_madeira int(11)NOT NULL,
  id_venda int(11) NOT NULL,
  comprimento decimal(6,2) DEFAULT 1,
  quantidade_item int default 1,
  CONSTRAINT pk_tbitem PRIMARY KEY (id_madeira,id_venda),
  CONSTRAINT fk_tbMadeira_tbItem FOREIGN KEY (id_madeira) REFERENCES tbmadeira (id_madeira)ON DELETE CASCADE	ON UPDATE CASCADE,
  CONSTRAINT fk_tbVenda_tbItem FOREIGN KEY (id_venda) REFERENCES tbvenda (id_venda)ON DELETE CASCADE	ON UPDATE CASCADE
) DEFAULT CHARSET=UTF8;

CREATE TABLE tbparcela (
  id_parcela int(11) NOT NULL AUTO_INCREMENT,
  vencimento_parcela date NOT NULL,
  valor_parcela decimal(7,2) NOT NULL,
  id_venda int(11),
  juros_parcela decimal(4,2) NULL default 0,
  valor_pago_parcela decimal(7,2) NULL default 0,
  data_pagamento_parcela date NULL default '00000000',
  CONSTRAINT pk_tbparcela PRIMARY KEY (id_parcela),
  CONSTRAINT fk_tbVenda_tbParcela FOREIGN KEY (id_venda) REFERENCES tbvenda(id_venda)
  	ON DELETE CASCADE
  	ON UPDATE CASCADE
)DEFAULT CHARSET=UTF8;










