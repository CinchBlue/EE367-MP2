.PHONY: do_script

do_script:
	cd frequency
	make
	cd ..
	cd task1
	make
	cd ..
	cd task2
	make
	cd ..
	cd task3
	make
	cd ..
	cd task4
	make
	cd ..
	cd task5
	make
	cd ..
	cp frequency/frequency367 task4
	cp frequency/frequency367 task5
	cp task1/createcode367 task4
	cp task1/createcode367 task5
	cp task2/encode367 task4
	cp task2/encode367 task5
	cp task3/decode367 task4
	cp task3/decode367 task5
	cp task4/decodesplit367 task5
	cp task4/decodesplit367 task5 
	cp task4/compress367 task5
	cp task4/decompress367 task5
