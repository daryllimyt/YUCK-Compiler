def f():
	x = 15
	y = 16
	return x*y
	
def main():
	a = 35
	b = 15*f()
	a = 5
	b = f()
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
