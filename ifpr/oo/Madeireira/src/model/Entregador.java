package model;

public class Entregador {
	private String carteira;
	private String veiculo;
	private int id_func;
	
	public Entregador(String carteira, String veiculo,int id_func) {
		this.carteira=carteira;
		this.veiculo= veiculo;
		this.id_func=id_func;
	}

	public String getCarteira() {
		return carteira;
	}

	public void setCarteira(String carteira) {
		this.carteira = carteira;
	}

	public String getVeiculo() {
		return veiculo;
	}

	public void setVeiculo(String veiculo) {
		this.veiculo = veiculo;
	}

	public int getId_func() {
		return id_func;
	}

	public void setId_func(int id_func) {
		this.id_func = id_func;
	}
}
