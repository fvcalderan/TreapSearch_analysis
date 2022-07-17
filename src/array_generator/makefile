all: gen load

gen:
	gcc gen_array.c -Wall -Wextra -o gen -lm
load:
	gcc load_array.c -Wall -Wextra -o load

clean:
	rm -f gen load
