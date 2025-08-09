-- MySQL dump 10.16  Distrib 10.1.26-MariaDB, for Win32 (AMD64)
--
-- Host: localhost    Database: madeireira
-- ------------------------------------------------------
-- Server version	10.1.26-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tbcontato`
--

DROP TABLE IF EXISTS `tbcontato`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbcontato` (
  `id_empresa` int(11) DEFAULT NULL,
  `id_funcionario` int(11) DEFAULT NULL,
  `telefone` char(11) DEFAULT NULL,
  `tipo` tinyint(4) DEFAULT NULL,
  KEY `fk_tbFuncionario_tbContato` (`id_funcionario`),
  KEY `fk_tbEmpresa_tbContato` (`id_empresa`),
  CONSTRAINT `fk_tbEmpresa_tbContato` FOREIGN KEY (`id_empresa`) REFERENCES `tbempresa` (`id_empresa`),
  CONSTRAINT `fk_tbFuncionario_tbContato` FOREIGN KEY (`id_funcionario`) REFERENCES `tbfuncionario` (`id_func`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbcontato`
--

LOCK TABLES `tbcontato` WRITE;
/*!40000 ALTER TABLE `tbcontato` DISABLE KEYS */;
INSERT INTO `tbcontato` VALUES (1,NULL,'45078954321',1),(2,NULL,'45764843876',1),(3,NULL,'41643967218',1),(NULL,1,'41543691203',2),(NULL,2,'55932854910',2),(NULL,3,'34764501287',2),(NULL,4,'34129438690',2),(NULL,4,'45984046014',2);
/*!40000 ALTER TABLE `tbcontato` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbempresa`
--

DROP TABLE IF EXISTS `tbempresa`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbempresa` (
  `id_empresa` int(11) NOT NULL,
  `CNPJ_empresa` varchar(45) DEFAULT NULL,
  `rua_empresa` varchar(30) DEFAULT NULL,
  `numero_empresa` int(11) DEFAULT NULL,
  `bairro_empresa` varchar(25) DEFAULT NULL,
  `cidade_empresa` varchar(30) DEFAULT NULL,
  `nome` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_empresa`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbempresa`
--

LOCK TABLES `tbempresa` WRITE;
/*!40000 ALTER TABLE `tbempresa` DISABLE KEYS */;
INSERT INTO `tbempresa` VALUES (1,'25.191.473/0001-44','Rua Ariquemes',45,'Jardim das Laranjeiras','Curitiba','Cosntrutora Ferreira'),(2,'32.749.344/2356-82','Avenida Brasil',790,'Centro','Foz do Iguaçu','Floricultura Camomila'),(3,'23.345.789/4442-65','Rua Jorge Amado',345,'Bairro do Limoeiro','Cascavel','Editora L&I');
/*!40000 ALTER TABLE `tbempresa` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbentregador`
--

DROP TABLE IF EXISTS `tbentregador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbentregador` (
  `carteira_de_motorista` varchar(11) DEFAULT NULL,
  `veiculo` varchar(45) DEFAULT NULL,
  `id_func` int(11) NOT NULL,
  PRIMARY KEY (`id_func`),
  CONSTRAINT `pk_tbFuncionario_tbEntregador` FOREIGN KEY (`id_func`) REFERENCES `tbfuncionario` (`id_func`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbentregador`
--

LOCK TABLES `tbentregador` WRITE;
/*!40000 ALTER TABLE `tbentregador` DISABLE KEYS */;
INSERT INTO `tbentregador` VALUES ('1843902-3','Mini_van',1),('8334128-4','Fiorino',3);
/*!40000 ALTER TABLE `tbentregador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbfuncionario`
--

DROP TABLE IF EXISTS `tbfuncionario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbfuncionario` (
  `id_func` int(11) NOT NULL,
  `nome` varchar(20) DEFAULT NULL,
  `CPF_func` char(11) DEFAULT NULL,
  `RG_func` char(9) DEFAULT NULL,
  `rua_func` varchar(30) DEFAULT NULL,
  `cidade_func` varchar(30) DEFAULT NULL,
  `numero_func` int(11) DEFAULT NULL,
  `bairro_func` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`id_func`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbfuncionario`
--

LOCK TABLES `tbfuncionario` WRITE;
/*!40000 ALTER TABLE `tbfuncionario` DISABLE KEYS */;
INSERT INTO `tbfuncionario` VALUES (1,'Astolfo Natercio','234.432.766','23.434.44','Rua da Jaca','Santa Terezinha',309,'Vila W'),(2,'Angelo Pinto','432.657.543','98.767.54','Avenida Andradina','Foz do Iguaçu',98,'Jardim America'),(3,'Natalia Silva','543.346.654','432.432.1','Rua Antartica','Pato Branco',763,'Jardim Petropolis'),(4,'Maria Souza','546.234.324','43.435.54','Avenida das Rosas','Canoas',345,'Bairro das Macieiras');
/*!40000 ALTER TABLE `tbfuncionario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbitem`
--

DROP TABLE IF EXISTS `tbitem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbitem` (
  `preço_parcial` decimal(6,2) DEFAULT NULL,
  `id_madeira` int(11) NOT NULL,
  `id_venda` int(11) NOT NULL,
  `dimensoes` decimal(6,2) DEFAULT NULL,
  PRIMARY KEY (`id_madeira`,`id_venda`),
  KEY `fk_tbVenda_tbItem` (`id_venda`),
  CONSTRAINT `fk_tbMadeira_tbItem` FOREIGN KEY (`id_madeira`) REFERENCES `tbmadeira` (`id_madeira`),
  CONSTRAINT `fk_tbVenda_tbItem` FOREIGN KEY (`id_venda`) REFERENCES `tbvenda` (`id_venda`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbitem`
--

LOCK TABLES `tbitem` WRITE;
/*!40000 ALTER TABLE `tbitem` DISABLE KEYS */;
/*!40000 ALTER TABLE `tbitem` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbmadeira`
--

DROP TABLE IF EXISTS `tbmadeira`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbmadeira` (
  `id_madeira` int(11) NOT NULL,
  `preço_madeira` decimal(6,2) NOT NULL,
  `tipo_madeira` varchar(30) NOT NULL,
  `nome_madeira` varchar(45) NOT NULL,
  PRIMARY KEY (`id_madeira`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbmadeira`
--

LOCK TABLES `tbmadeira` WRITE;
/*!40000 ALTER TABLE `tbmadeira` DISABLE KEYS */;
/*!40000 ALTER TABLE `tbmadeira` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbpagamento`
--

DROP TABLE IF EXISTS `tbpagamento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbpagamento` (
  `valor_pagamento` decimal(7,2) DEFAULT NULL,
  `juros_pagamento` decimal(4,2) DEFAULT NULL,
  `data_pagamento` date DEFAULT NULL,
  `id_pagamento` int(11) NOT NULL,
  `id_parcela` int(11) DEFAULT NULL,
  PRIMARY KEY (`id_pagamento`),
  CONSTRAINT `fk_tbParcela_tbPagamento` FOREIGN KEY (`id_pagamento`) REFERENCES `tbparcela` (`id_parcela`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbpagamento`
--

LOCK TABLES `tbpagamento` WRITE;
/*!40000 ALTER TABLE `tbpagamento` DISABLE KEYS */;
/*!40000 ALTER TABLE `tbpagamento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbparcela`
--

DROP TABLE IF EXISTS `tbparcela`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbparcela` (
  `id_parcela` int(11) NOT NULL,
  `vencimento_parcela` date NOT NULL,
  `valor_parcela` decimal(7,2) NOT NULL,
  `id_venda` int(11) DEFAULT NULL,
  PRIMARY KEY (`id_parcela`),
  KEY `fk_tbVenda_tbParcela` (`id_venda`),
  CONSTRAINT `fk_tbVenda_tbParcela` FOREIGN KEY (`id_venda`) REFERENCES `tbvenda` (`id_venda`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbparcela`
--

LOCK TABLES `tbparcela` WRITE;
/*!40000 ALTER TABLE `tbparcela` DISABLE KEYS */;
/*!40000 ALTER TABLE `tbparcela` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tbvenda`
--

DROP TABLE IF EXISTS `tbvenda`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tbvenda` (
  `id_venda` int(11) NOT NULL,
  `data_venda` date DEFAULT NULL,
  `horario_venda` time(4) DEFAULT NULL,
  `total_venda` decimal(9,2) DEFAULT NULL,
  `id_func` int(11) DEFAULT NULL,
  `id_empresa` int(11) DEFAULT NULL,
  `id_entregador` int(11) DEFAULT NULL,
  PRIMARY KEY (`id_venda`),
  KEY `fk_tbFuncionario_tbVenda` (`id_func`),
  KEY `fk_tbEmpresa_tbVenda` (`id_empresa`),
  KEY `fk_tbEntregador_tbVenda` (`id_entregador`),
  CONSTRAINT `fk_tbEmpresa_tbVenda` FOREIGN KEY (`id_empresa`) REFERENCES `tbempresa` (`id_empresa`),
  CONSTRAINT `fk_tbEntregador_tbVenda` FOREIGN KEY (`id_entregador`) REFERENCES `tbentregador` (`id_func`),
  CONSTRAINT `fk_tbFuncionario_tbVenda` FOREIGN KEY (`id_func`) REFERENCES `tbfuncionario` (`id_func`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tbvenda`
--

LOCK TABLES `tbvenda` WRITE;
/*!40000 ALTER TABLE `tbvenda` DISABLE KEYS */;
/*!40000 ALTER TABLE `tbvenda` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-09-10 19:08:07
