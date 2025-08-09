package DAO;


import java.sql.Connection;

import java.sql.DriverManager;

import java.sql.PreparedStatement;

import java.sql.ResultSet;

import java.sql.Statement;


import model.Venda;


public class TbVenda implements IVenda{
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
			System.out.println("Erro na conex�o com o banco de dados!");
		}
		return conexao;
	}

public void listar(int id) {
	Connection conexao = abrirConexao();
	
	if(id == 0) {
		selectSql = "SELECT * FROM tbvenda";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_venda = rs.getInt("id_venda"); 
				String data = rs.getString("data_venda");
				String horario = rs.getString("horario_venda");
				double total = rs.getDouble("total_venda");
				int id_func = rs.getInt("id_func");
				int id_empresa = rs.getInt("id_empresa");
				int id_entregador = rs.getInt("id_entregador");
				System.out.println("=======================================================================================================================================");
				System.out.println("ID da venda: " + id_venda
						+ " | Data da venda: " + data
						+ " | Horario da venda: " + horario
						+ " | Total: " + total
						+ " | ID Funcionario: " + id_func
						+ " | ID Empresa:  " + id_empresa
						+ " | ID Entregador:  " + id_entregador);
				
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar as vendas.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conex�es "
						+ "com o banco de dados!");
			}
		}
	}else {
	selectSql = "SELECT * FROM tbvenda where id_venda = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_venda = rs.getInt("id_venda"); 
			String data = rs.getString("data_venda");
			String horario = rs.getString("horario_venda");
			double total = rs.getDouble("total_venda");
			int id_func = rs.getInt("id_func");
			int id_empresa = rs.getInt("id_empresa");
			int id_entregador = rs.getInt("id_entregador");
			System.out.println("===========================================================================================================================================");
			System.out.println("ID da venda: " + id_venda
					+ " | Data da venda: " + data
					+ " | Horario da venda: " + horario
					+ " | Total: " + total
					+ " | ID Funcionario: " + id_func
					+ " | ID Empresa:  " + id_empresa
					+ " | ID Entregador:  " + id_entregador);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar vendas.");
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

public int inserir(Venda venda) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbvenda (data_venda,horario_venda,total_venda,id_func,id_empresa,id_entregador) VALUES (?, ?, ?,?,?,?)";
	int idInserido = 0;
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql, Statement.RETURN_GENERATED_KEYS);
		
		preparedStatement.setString(1, venda.getData());
		preparedStatement.setString(2, venda.getHorario());
		preparedStatement.setDouble(3, venda.getTotal());
		preparedStatement.setInt(4, venda.getId_func());
		preparedStatement.setInt(5, venda.getId_empresa());
		preparedStatement.setInt(6, venda.getId_entregador());
		
		preparedStatement.executeUpdate();
		
		// pega o ultimo id inserido
	    ResultSet rs = preparedStatement.getGeneratedKeys();
	    while (rs.next()) {
	    	idInserido = rs.getInt(1);
	    }
		
		System.out.println("Venda inserida com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir a Venda!");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conex�es com o banco de dados!");
		}
	}
	
	return idInserido;
	
}

public void deletar(int id) {
	Connection conexao = abrirConexao();
	String deleteSql = "DELETE FROM tbvenda WHERE id_venda = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("Venda deletada.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar Venda.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conex�es com o banco de dados!");
		}
	}
}

public void atualizar(Venda venda2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbvenda SET data_venda = ? , horario_venda = ?, total_venda =?, id_func=? , id_empresa=?, id_entregador=? WHERE id_venda = ?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		
		preparedStatement = conexao.prepareStatement(updateSql);
		
		preparedStatement.setString(1, venda2.getData());
		preparedStatement.setString(2, venda2.getHorario());
		preparedStatement.setDouble(3, venda2.getTotal());
		preparedStatement.setInt(4, venda2.getId_func());
		preparedStatement.setInt(5, venda2.getId_empresa());
		preparedStatement.setInt(6, venda2.getId_entregador());
		preparedStatement.setInt(7, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela Venda foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar venda.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conex�es "
					+ "com o banco de dados!");
		}
	}
}
	
	public double fazerVenda(int id,double qdt,double comp) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String vender ="SELECT * FROM tbmadeira where id_madeira = ?";
	double t = 0;
	
	try {
		preparedStatement = conexao.prepareStatement(vender);
		preparedStatement.setInt(1, id);
		double preco=0;
		ResultSet rs = preparedStatement.executeQuery();
		while(rs.next()) {
		preco = rs.getDouble("preco_madeira");
		}
		t = qdt*preco*comp;
		System.out.println("Venda feita com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar fazer a Venda!");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
	
	return t;
	
}
	public void atualizarTotal(double t,int id) {
		Connection conexao = abrirConexao();
		String atualizar = "UPDATE tbvenda SET total_venda =? WHERE id_venda = ?";
		
		PreparedStatement preparedStatement = null;
		
		try {
			preparedStatement = conexao.prepareStatement(atualizar);
			preparedStatement.setDouble(1, t);
			preparedStatement.setInt(2, id);
			preparedStatement.executeUpdate();
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar atualizar venda.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conex�es "
						+ "com o banco de dados!");
			}
		}
	}
	
	public void listarPorCliente(String cliente) {
		Connection conexao = abrirConexao();
		selectSql = "SELECT * FROM tbvenda inner join tbcliente on tbcliente.id_cliente = tbvenda.id_cliente where nome_cliente = ?";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			preparedStatement.setString(1, cliente);
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_venda = rs.getInt("id_venda"); 
				String data = rs.getString("data_venda");
				String horario = rs.getString("horario_venda");
				double total = rs.getDouble("total_venda");
				int id_func = rs.getInt("id_func");
				int id_empresa = rs.getInt("id_empresa");
				int id_entregador = rs.getInt("id_entregador");
				System.out.println("=======================================================================================================================================");
				System.out.println("ID da venda: " + id_venda
						+ " | Data da venda: " + data
						+ " | Horario da venda: " + horario
						+ " | Total: " + total
						+ " | ID Funcionario: " + id_func
						+ " | ID Empresa:  " + id_empresa
						+ " | ID Entregador:  " + id_entregador);
				
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar as vendas.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conex�es "
						+ "com o banco de dados!");
			}
	}
	
}
}