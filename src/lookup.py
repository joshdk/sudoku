import sys




def row_neighbors(x,y):
	return [9*y+n for n in range(0,9)]


def col_neighbors(x,y):
	return [9*n+x for n in range(0,9)]


def sub_neighbors(x,y):
	x=x-x%3
	y=y-y%3

	cells=[]
	for i in range(y,y+3):
		for j in range(x,x+3):
			cells.append(9*i+j)
	return cells


def neighbors(x,y):
	cells=set(row_neighbors(x,y)+col_neighbors(x,y)+sub_neighbors(x,y))
	cells.discard(9*y+x)
	return sorted(cells)


def create_table():
	sys.stdout.write("static const unsigned int lookup[81][20]={\n");
	for y in range(0,9):
		for x in range(0,9):
			cells=neighbors(x,y)
			sys.stdout.write("{")
			for cell in cells:
				sys.stdout.write("0x%02x," % (cell))
			sys.stdout.write("},\n")
	sys.stdout.write("};\n")




def main(argv=None):
	if argv is None:
		argv = sys.argv
	argc=len(argv)

	create_table()




if __name__ == "__main__":
	sys.exit(main())
