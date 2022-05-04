#pragma once
#include "Oferta.h"
#include <exception>

class Valid
{
public:
	bool non_negative(int x) noexcept;
	bool non_negative1(double x) noexcept;
	bool is_id(string x);
	bool is_pret(string x);
};

void tests_validators(Valid valid);
void test_is_id(Valid valid);
void test_is_pret(Valid valid);