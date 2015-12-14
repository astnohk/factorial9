#include <cstdio>
#define DIGIT 17
class decimal
{
	private:
		unsigned short _digit[100];
		unsigned short _carry[100];
	public:
		unsigned short data[DIGIT];
		decimal(void)
		{
			for (int i = 0; i <= 99; i++) {
				_digit[i] = i % 10;
				_carry[i] = (i / 10) % 10;
			}
			for (int i = 0; i < DIGIT; i++) {
				data[i] = 0;
			}
		}
		decimal(unsigned long int num)
		{
			for (int i = 0; i <= 99; i++) {
				_digit[i] = i % 10;
				_carry[i] = (i / 10) % 10;
			}
			for (int i = 0; i < DIGIT; i++) {
				data[i] = (num % 10);
				num /= 10;
			}
		}
		decimal &
		operator=(decimal num)
		{
			for (int i = 0; i < DIGIT; i++) {
				data[i] = num.data[i];
			}
			return *this;
		}
		decimal &
		operator++(void)
		{
			unsigned short d = data[0] + 1u;
			data[0] = _digit[d];
			for (int i = 1; _carry[d] > 0 && i < DIGIT; i++) {
				d = data[i] + _carry[d];
				data[i] = _digit[d];
			}
			return *this;
		}
		decimal &
		operator+=(const decimal& num)
		{
			unsigned short d = 0u;
			for (int i = 0; i < DIGIT; i++) {
				d = data[i] + num.data[i] + _carry[d];
				data[i] = _digit[d];
			}
			return *this;
		}
		decimal &
		operator*=(const decimal& num)
		{
			unsigned short tmp[DIGIT];
			unsigned short d = 0u;
			if (num.data[0] != 0) {
				for (int i = 0; i < DIGIT; i++) {
					d = data[i] * num.data[0] + _carry[d];
					tmp[i] = _digit[d];
				}
			}
			for (int k = 1; k < DIGIT; k++) {
				d = 0;
				for (int i = 0; num.data[k] != 0 && k + i < DIGIT; i++) {
					d = tmp[k + i] + data[i] * num.data[k] + _carry[d];
					tmp[k + i] = _digit[d];
				}
			}
			for (int i = 0; i < DIGIT; i++) {
				data[i] = tmp[i];
			}
			return *this;
		}
		decimal &
		operator>>=(const int num)
		{
			for (int i = 0; i < DIGIT; i++) {
				data[i] = i + num < DIGIT ? data[i + num] : 0u;
			}
			return *this;
		}
		unsigned long int
		to_ulint(int lim_digit)
		{
			unsigned long int num = 0u, digit = 1u;
			for (int i = 0; i < DIGIT && i < lim_digit; i++) {
				num += data[i] * digit;
				digit *= 10u;
			}
			return num;
		}
};

int
main(void)
{
	decimal count(1u), prod, cum_prod(1u);
	int N, digit;
	scanf("%d", &N);
	for (int i = 2; i <= N; i++) {
		prod = ++count;
		for (digit = 0; digit < DIGIT && prod.data[digit] == 0; digit++);
		prod >>= digit;
		cum_prod *= prod;
		for (digit = 0; digit < DIGIT && cum_prod.data[digit] == 0; digit++);
		cum_prod >>= digit;
	}
	printf("%lu", cum_prod.to_ulint(9));
	return 0;
}

