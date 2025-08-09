package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Item;
import model.Madeira;

public class TbItem implements IItem {

	public static final String DB_URL = "jdbc:mysql://localhost:3306/madeireira";
	public static final String DB_USUARIO = "root";
	public static final String DB_SENHA = "";
	String selectSql;
	
	private Connection abrirConexao() {
		Connection conexao = null;
		try {conexao = DriverManager
				.getConnection(DB_URL, DB_USUARIO,DB_SENHA);
		
		} catch(Exception e) {
			e.printStackTrace();
			System.out.println("==============================");
			System.out.println("Erro na conexão com o banco de dados!");
		}
		return conexao;
	}

public void listar(int id) {
	Connection conexao = abrirConexao();
	
	if(id == 0) {
		selectSql = "SELECT * FROM tbitem";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				double preco_madeira = rs.getDouble("preco_madeira");
				double preco_parcial = rs.getDouble("preco_parcial"); 
				int id_venda = rs.getInt("id_venda");
				int id_madeira = rs.getInt("id_madeira");
				double comp = rs.getDouble("comprimento");
				int qtd = rs.getInt("quantidade_item");
				
				System.out.println("Preço Madeira: "+ preco_madeira
						+ " | Preco parcial: " + preco_parcial
						+ " | ID Madeira : " + id_madeira
						+ " | ID Venda: " + id_venda
						+ " | COmprimento : " + comp
						+ " | Quantidade : " + qtd);
				
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar itens.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conexões "
						+ "com o banco de dados!");
			}
		}
	}else {
	selectSql = "SELECT * FROM tbitem where id_venda = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			double preco_madeira = rs.getDouble("preco_madeira");
			double preco_parcial = rs.getDouble("preco_parcial"); 
			int id_venda = rs.getInt("id_venda");
			int id_madeira = rs.getInt("id_madeira");
			double comp = rs.getDouble("comprimento");
			int qtd = rs.getInt("quantidade_item");
			
			
			System.out.println("Preço Madeira: "+ preco_madeira
					+ " | Preco parcial: " + preco_parcial
					+ " | ID Madeira : " + id_madeira
					+ " | ID Venda: " + id_venda
					+ " | COmprimento : " + comp
					+ " | Quantidade : " + qtd);
			
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar item.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
}
	
}

public void inserir(Item item) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbitem (preco_madeira,preco_parcial, id_venda,id_madeira,comprimento,quantidade_item) VALUES (?,?, ?, ?,?,?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		preparedStatement.setDouble(1, item.getPrecomad());
		preparedStatement.setDouble(2, item.getPreco());
		preparedStatement.setInt(3, item.getId_venda());
		preparedStatement.setInt(4, item.getId_madeira());
		preparedStatement.setDouble(5, item.getComprimento());
		preparedStatement.setInt(6, item.getQuantidade());
		preparedStatement.executeUpdate();
		
		System.out.println("item inserido com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir o item!");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
	
}

public void deletar(int id) {
	Connection conexao = abrirConexao();
	String deleteSql = "DELETE FROM tbitem WHERE id_venda = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("Item deletado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar o item.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
	
}

public void atualizar(Item item2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbitem SET preco_madeira = ? preco_parcial = ? , id_madeira =?, dimensoes=? where id_venda =?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setDouble(1, item2.getPrecomad());
		preparedStatement.setDouble(2, item2.getPreco());
		preparedStatement.setInt(3, item2.getId_madeira());
		preparedStatement.setDouble(4, item2.getComprimento());
		preparedStatement.setInt(5, item2.getId_venda());
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela Item foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar Item.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões "
					+ "com o banco de dados!");
		}
	}
}
}
