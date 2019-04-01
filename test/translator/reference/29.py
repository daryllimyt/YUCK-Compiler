def main():
	x = 15
	y = 20
	z = 0
	while(y>0):
		y -= 1
		if((x+y)%2==0):
			continue
			
		z += 1
		
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
