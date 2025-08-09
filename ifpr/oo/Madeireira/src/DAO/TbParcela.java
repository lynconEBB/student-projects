package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Parcela;

public class TbParcela implements IParcela {
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
		selectSql = "SELECT * FROM tbparcela";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_parcela = rs.getInt("id_parcela"); 
				double valor_parcela = rs.getDouble("valor_parcela");
				String data = rs.getString("vencimento_parcela");
				int id_venda = rs.getInt("id_venda");
				double valor_pagamento= rs.getDouble("valor_pago_parcela");
				double juros = rs.getDouble("juros_parcela");
				String data_pagamento = rs.getString("data_pagamento_parcela");
				
				System.out.println("ID: " + id_parcela
						+ " | valor da parcela: " + valor_parcela
						+ " | Data vencimento da parcela: " + data
						+ " | ID da venda: " + id_venda
						+ " | Data Pagamento "+ data_pagamento
						+ " | Juros: "+juros
						+ " | Valor Pago: "+valor_pagamento);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar parcelas.");
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
	selectSql = "SELECT * FROM tbparcela where id_venda = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_parcela = rs.getInt("id_parcela"); 
			double valor_parcela = rs.getDouble("valor_parcela");
			String data = rs.getString("vencimento_parcela");
			int id_venda = rs.getInt("id_venda");
			double valor_pagamento= rs.getDouble("valor_pago_parcela");
			double juros = rs.getDouble("juros_parcela");
			String data_pagamento = rs.getString("data_pagamento_parcela");
			
			System.out.println("ID: " + id_parcela
					+ " | valor da parcela: " + valor_parcela
					+ " | Data vencimento da parcela: " + data
					+ " | ID da venda: " + id_venda
					+ " | Data Pagamento "+ data_pagamento
					+ " | Juros: "+juros
					+ " | Valor Pago: "+valor_pagamento);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar parcelas.");
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

public void inserir(Parcela par) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbparcela (valor_parcela, vencimento_parcela, id_venda,juros_parcela,valor_pago_parcela,data_pagamento_parcela) VALUES (?, ?, ?,?,?,?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		
		preparedStatement.setDouble(1, par.getValor_parcela());
		preparedStatement.setString(2, par.getData_vencimento());
		preparedStatement.setInt(3, par.getId_venda());
		preparedStatement.setDouble(4, par.getJuros());
		preparedStatement.setDouble(5, par.getValor_pago());
		preparedStatement.setString(6, par.getData_pagamento());
		preparedStatement.executeUpdate();
		
		System.out.println("Parcela inserida com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir a parcela!");
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
	String deleteSql = "DELETE FROM tbparcela WHERE id_parcela = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("Parcela deletada.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar a parcela.");
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

public void atualizar(Parcela par2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbparcela SET valor_parcela = ? , vencimento_parcela = ?, id_venda =?,juros_parcela=?,valor_pago_parcela=?,data_pagamento_parcela=? where id_parcela= ?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setDouble(1, par2.getValor_parcela());
		preparedStatement.setString(2, par2.getData_vencimento());
		preparedStatement.setInt(3, par2.getId_venda());
		preparedStatement.setDouble(4, par2.getJuros());
		preparedStatement.setDouble(5, par2.getValor_pago());
		preparedStatement.setString(6, par2.getData_pagamento());
		preparedStatement.setInt(7, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela parcela foi atualizada.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar parcela.");
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
public void efetuarPagamento(String data,double juros, double valor_pagamento, int id) {
	Connection conexao = abrirConexao();
	String updateSql2 = "UPDATE tbparcela set data_pagamento_parcela = ?, juros_parcela =?,valor_pago_parcela=? where id_parcela = ?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql2);
		preparedStatement.setString(1, data);
		preparedStatement.setDouble(2,juros);
		preparedStatement.setDouble(3, valor_pagamento);
		preparedStatement.setInt(4, id);
		preparedStatement.executeUpdate();
		
		System.out.println("Pagamento efetuado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar efetuar pagamento.");
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

