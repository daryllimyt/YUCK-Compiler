def f():
	return 10
	
def main():
	x = 5*f()
	y = f()*f()+f()
	z = f()/12
	a = x*f()+f()/(y+7)-f()*z
	return f() - 10
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
