package model;

public class Parcela {
	private double valor_parcela;
	private String data_vencimento;
	private int id_venda;
	private double valor_pago;
	private double juros;
	private String data_pagamento;
	
	public Parcela(double valor_parcela, String data_vencimento, int id_venda, double valor_pago, double juros, String data_pagamento) {
		this.valor_parcela=valor_parcela;
		this.data_vencimento=data_vencimento;
		this.id_venda=id_venda;
		this.valor_pago=valor_pago;
		this.juros=juros;
		this.data_pagamento=data_pagamento;
	}

	public double getValor_parcela() {
		return valor_parcela;
	}

	public void setValor_parcela(double valor_parcela) {
		this.valor_parcela = valor_parcela;
	}

	public String getData_vencimento() {
		return data_vencimento;
	}

	public void setData_vencimento(String data_vencimento) {
		this.data_vencimento = data_vencimento;
	}

	public int getId_venda() {
		return id_venda;
	}

	public void setId_venda(int id_venda) {
		this.id_venda = id_venda;
	}

	public double getValor_pago() {
		return valor_pago;
	}

	public void setValor_pago(double valor_pago) {
		this.valor_pago = valor_pago;
	}

	public double getJuros() {
		return juros;
	}

	public void setJuros(double juros) {
		this.juros = juros;
	}

	public String getData_pagamento() {
		return data_pagamento;
	}

	public void setData_pagamento(String data_pagamento) {
		this.data_pagamento = data_pagamento;
	}




	
}
