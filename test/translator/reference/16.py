def main():
	a = 1
	b = 2
	c = 3
	d = 4
	e = 5
	f = 6
	g = 7
	h = 8
	i = 9
	j = 10
	x = 0
	x += 1
	b -= 1
	c *= 5
	d /= 4
	e %= 3
	f &= 1
	g |= 15
	h ^= 10
	i <<= 1
	j >>= 2
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
