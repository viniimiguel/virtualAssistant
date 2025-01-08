#pragma once
#include <vector>
#include "currency.h"
#include <cstdlib>
#include <iostream>
#include <random>

class Events
{
private:
	std::vector<Currency*> currencies;
public:
	Events(const std::vector<Currency*>& currencies) : currencies(currencies){}
	void inflation(const std::string& currencyName);
	void interestRate(const std::string& currencyName);
	// deopis tenho que adicionar uma forma de horario e data para esta simula��o de eventos e divida para que seja possivel calcular o juros da divida
	void publicDebt(const std::string& currencyGovernment, const std::string& currencyDebtGovernment, double debt);
	void governmentLoan(const std::string& currencyGovernment,const std::string& currencyLoanGovernment, double loan);
	void pib(const std::string& currencyGovernment);
	void demandShock(const std::string& currencyName);
	void overDemand(const std::string& currencyName);
	void overSupply(const std::string& currencyName);
	void underSupply(const std::string& currencyName);
};