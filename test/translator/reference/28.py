def main():
	x = 15
	y = 1
	while(x>0):
		x += 1
		if(x>20):
			break
			
		y += 1
		
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
