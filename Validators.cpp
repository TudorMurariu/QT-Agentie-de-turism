#include "Validators.h"

bool Valid::non_negative(int x) noexcept {
	return x >= 0;
}

bool Valid::is_id(string x)
{
	/* Verificam daca un string este id*/
	int num;
	try {
		num = stoi(x);
	}
	catch (exception e) {
		return false;
	}

	return non_negative(num);
}

bool Valid::non_negative1(double x) noexcept {
	return x >= 0;
}

bool Valid::is_pret(string x)
{
	/* Verificam daca un string este pret*/
	double pret;
	try {
		pret = stod(x);
	}
	catch (exception e) {
		return false;
	}

	return non_negative1(pret);
}

void tests_validators(Valid valid)
{
	test_is_id(valid);
	test_is_pret(valid);
}

void test_is_id(Valid valid)
{
	assert(valid.is_id("32") == true);
	assert(valid.is_id("0") == true);
	assert(valid.is_id("6577") == true);
	assert(valid.is_id("-2") == false);
	assert(valid.is_id("a32a") == false);
	assert(valid.is_id("") == false);
	assert(valid.is_id("a32   5") == false);
}

void test_is_pret(Valid valid)
{
	assert(valid.is_id("5.7") == true);
	assert(valid.is_id("0") == true);
	assert(valid.is_id("0.99") == true);
	assert(valid.is_id("a32.a") == false);
	assert(valid.is_id("") == false);
	assert(valid.is_id("a32   5") == false);
	assert(valid.is_id("-2") == false);
	assert(valid.is_id("adwaw") == false);
}
