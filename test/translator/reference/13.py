def f():
	x = 15
	y = 16
	return x*y
	
def main():
	a = 21
	b = 13
	c = f()
	a = 11
	b = 24
	d = b+a
	e = 6+10
	c = 15
	d = 5*f()
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
