all: report

report: report.o words.o
	g++ -o $@ $^ -lcurl -lcurlpp

words.o: words/words.cpp
	g++ -c $<

.o: .cpp
	g++ -c $<

clean:
	rm -f report tt *.o