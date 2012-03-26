template <typename T>
T gcd(const T& a, const T& b) {
	if(a < b) {
		return gcd(b, a);
	} else {
		if(b == T(0)) {
			return a;
		} else {
			return gcd(b, a % b);
		}
	}
}
