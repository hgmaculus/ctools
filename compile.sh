for f in *.c
do
	gcc $f -o $(basename "$f" .c)
done
