def main():
	a = 1
	b = 1
	c = 1
	if(a):
		b += 2
		
	else:
		if(c>5):
			c -= 5
			
		else:
			a = 4-a
			
		
	return 0
	

if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
