package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Tipo;

public class TbTipo implements ITipo {
	public static final String DB_URL = "jdbc:mysql://localhost:3306/madeireira";
	public static final String DB_USUARIO = "root";
	public static final String DB_SENHA = "";
	String selectSql;
	
	private Connection abrirConexao() {
		Connection conexao = null;
		try {conexao = DriverManager
				.getConnection(DB_URL, DB_USUARIO,DB_SENHA);
			System.out.println("Conexão realizada com sucesso!");
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
		selectSql = "SELECT * FROM tbtipo";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_madeira = rs.getInt("id_tipo"); 
				double espessura = rs.getDouble("espessura_tipo");
				String nome= rs.getString("nome_tipo");
				
				System.out.println("ID: " + id_madeira
						+ " | Espessura: " + espessura
						+ " | Nome: " + nome);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar madeiras.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
			}
		}
	}else {
	selectSql = "SELECT * FROM tbtipo where id_tipo = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_madeira = rs.getInt("id_tipo"); 
			double espessura = rs.getDouble("espessura_tipo");
			String nome= rs.getString("nome_tipo");
			
			System.out.println("ID: " + id_madeira
					+ " | Espessura: " + espessura
					+ " | Nome: " + nome);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar tipos de madeiras.");
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

public void inserir(Tipo tipo) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbtipo (espessura_tipo,nome_tipo) VALUES ( ?, ?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		
		preparedStatement.setDouble(1, tipo.getEspessura());
		preparedStatement.setString(2, tipo.getNome());
		preparedStatement.executeUpdate();
		
		System.out.println("Tipo de madeira inserido com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir o tipo de madeira!");
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
	String deleteSql = "DELETE FROM tbtipo WHERE id_tipo = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("tipo deletado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar o tipo.");
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

public void atualizar(Tipo tipo2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbtipo SET espessura_tipo = ? , nome_tipo = ? where id_tipo= ?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setDouble(1, tipo2.getEspessura());
		preparedStatement.setString(2, tipo2.getNome());
		preparedStatement.setInt(3, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela tipo foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar tipos.");
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
