def f(x):
	y = x+15
	
def g(a,b,c,d):
	x = a+12
	x = x*b
	y = c+a
	y = d+14
	return x-y
	
def main():
	a = 21
	b = 42
	c = 33
	d = 90
	f(a)
	f(0)
	e = g(a,b,c,d)
	e = g(1,2,3,4)
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
