def main():
	x = 15
	y = 10
	a = 0
	if(x>0):
		a += 10
		
	if(y>0):
		a -= 10
		return 0
		
	else:
		a = 22
		return 0
		
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
