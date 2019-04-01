def main():
	x = 15
	y = 3*x
	while(x>0):
		if(y>=x):
			y -= x
			
		else:
			x -= 1
			
		
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
