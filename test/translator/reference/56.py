x=1.3

def main():
    global x
    y=x+x
    return x

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
