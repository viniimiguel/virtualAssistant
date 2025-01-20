#include "events.h"
#include <memory>
#include "market.h"

void Events::inflation(const std::string& currencyName)
{
	for (Currency* currency : currencies)
	{
		if (currency->getName() == currencyName)
		{
			double inflationRate = currency->getVolatility();
			double newSupply = currency->getSupply() * (1 + inflationRate);
			currency->setSupply(newSupply);

			double newValue = currency->getDemand() / newSupply;
			currency->setValue(newValue);
		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}
void Events::interestRate(const std::string& currencyGovernment)
{
	for(Currency* currency : currencies)
	{
		if(currency->getGovernment() == currencyGovernment)
		{
			double demand = currency->getDemand();
			double supply = currency->getSupply();
			double volatility = currency->getVolatility();
			double inflation = 0.04; // depois tenho que mudar pra deixar o valor da infla��o dinamico nesta fun��o
			double economicGrowth = 0.02; // depois tenho que mudar pra deixar o valor do crescimento econ�mico dinamico nesta fun��o

			double interestRate = 0.01 * demand / supply + 0.02 * volatility + 0.0005 * inflation - 0.003 * economicGrowth;

		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}
void Events::publicDebt(const std::string& currencyGovernment, const std::string& currencyDebtGovernment, double debt)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1.4, 2.4);

	double randomFees = dis(gen);
	Currency* governmentCurrency = nullptr;
	Currency* debtCurrency = nullptr;

	for(Currency* currency : currencies)
	{
		

		if(currency->getGovernment() == currencyGovernment)
		{
			governmentCurrency = currency;
		}
		else if (currency->getGovernment() == currencyDebtGovernment)
		{
			debtCurrency = currency;
		}
		if(governmentCurrency && debtCurrency)
		{
			break;
		}
	}
	if(!governmentCurrency || !debtCurrency)
	{
		std::cerr << "Erro: N�o foi poss�vel encontrar as moedas especificadas." << std::endl;
	}
	if (debt > governmentCurrency->getDebt()) {
		std::cerr << "voce nao pode pagar mais do que deve voce pagou apenas a sua divida." << std::endl;
		debt = governmentCurrency->getDebt();
	}
	double convertCurrency = debt * governmentCurrency->getValue() / debtCurrency->getValue();
	double newSupplyGovernment = debtCurrency->getSupply() + convertCurrency;
	debtCurrency->setSupply(newSupplyGovernment);

	double newCurrencySupply = governmentCurrency->getSupply() - convertCurrency;
	governmentCurrency->setSupply(newCurrencySupply);

	governmentCurrency->setDebt(0);

	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);

}
void Events::governmentLoan(const std::string& currencyGovernment, const std::string& currencyLoanGovernment, double loan)
{
	Currency* governmentCurrency = nullptr;
	Currency* loanCurrency = nullptr;

	for (Currency* currency : currencies)
	{
		if (currency->getGovernment() == currencyGovernment)
		{
			governmentCurrency = currency;
		}
		else if (currency->getGovernment() == currencyLoanGovernment)
		{
			loanCurrency = currency;
		}

		if (governmentCurrency && loanCurrency)
		{
			break;
		}
	}

	if (!governmentCurrency || !loanCurrency)
	{
		std::cerr << "Erro: Nao foi poss�vel encontrar as moedas especificadas." << std::endl;
		return;
	}
	if (loan > loanCurrency->getSupply()) {
		std::cerr << "Erro: Nao e possivel emprestar mais do que voce tem!" << std::endl;
		return;
	}
	double convertedLoan = loan * loanCurrency->getValue() / governmentCurrency->getValue();

	double newSupplyGovernment = governmentCurrency->getSupply() + convertedLoan;
	double newSupplyLoan = loanCurrency->getSupply() - loan;

	governmentCurrency->setSupply(newSupplyGovernment);
	governmentCurrency->setDebt(loan);

	loanCurrency->setSupply(newSupplyLoan);

	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
	
}
void Events::demandShock(const std::string& currencyGovernment)
{
	for(Currency* currency : currencies)
	{
		if(currency->getGovernment() == currencyGovernment)
		{
			double demandShock = currency->getSupply() * 0.1;
			double newDemand = currency->getDemand() - demandShock;
			currency->setDemand(newDemand);
			double newValue = currency->getDemand() / currency->getSupply();
			currency->setValue(newValue);
			std::cout << newValue << std::endl;
		}
		else
		{
			std::cout << "Currency not found" << std::endl;
		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}
void Events::overDemand(const std::string& currencyGovernment)
{
	for(Currency* currency : currencies)
	{
		if(currency->getGovernment() == currencyGovernment)
		{
			double overDemand = currency->getDemand() * 0.2;
			double newDemand = currency->getDemand() + overDemand;
			currency->setDemand(newDemand);
			double newValue = currency->getDemand() / currency->getSupply();
			currency->setValue(newValue);
		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}
void Events::overSupply(const std::string& currencyGovernment) {
	for (Currency* currency : currencies) {
		if (currency->getGovernment() == currencyGovernment) {
			double overSupply = currency->getDemand() * 0.1;
			double newSupply = currency->getSupply() + overSupply;
			currency->setSupply(newSupply);
			double newValue = currency->getDemand() / newSupply;
			currency->setValue(newValue);
		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}
void Events::underSupply(const std::string& currencyGovernment)
{
	for (Currency* currency : currencies)
	{
		if (currency->getGovernment() == currencyGovernment)
		{
			double underSupply = currency->getDemand() * 0.1;
			double newSupply = currency->getSupply() - underSupply;
			if (newSupply < 0.1) {
				newSupply = 0.1;
			}
			currency->setSupply(newSupply);
			double newValue = currency->getDemand() / (newSupply + 1e-6);
			currency->setValue(newValue);
		}
	}
	if (mkt) {
		mkt->updateMakert();
		mkt->displayMarket(actived);
	}
	setActived(true);
}