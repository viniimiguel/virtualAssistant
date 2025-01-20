#include <iostream>
#include "httpRequestGroq.h"
#include <locale>
#include "currency.h"
#include "market.h"
#include "events.h"
#include <memory>
#include <thread>

int main() {
	std::locale::global(std::locale("en_US.UTF-8"));

	Currency usd;

	usd.setGovernment("USA");
	usd.setName("USD");
	usd.setSupply(100);
	usd.setDemand(100);
	usd.setVolatility(0.05);
	usd.setDebt(0);

	usd.updateValue();
	std::cout << "o valor da moeda e: " << usd.getValue() << std::endl;
	Market* mkt = new Market({&usd});

	Events events({ &usd }, mkt);


	events.overSupply("USA");
	std::cout << usd.getSupply() << std::endl;

	mkt->displayMarket(events.getActived());


	return 0;
}