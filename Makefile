all:

.PHONY: test/prep
test/prep: diff1 diff2

.PHONY: test
test:
	@go test -v *.go

.PHONY: diff1
diff1:
	@diff -ud test/file1.txt test/file2.txt | sed -E 's/(-{3}|\+{3}).*\/.*.txt/\1 state\.txt/' > test/tmp1.patch

.PHONY: diff2
diff2:
	@diff -ud test/file2.txt test/file3.txt | sed -E 's/(-{3}|\+{3}).*\/.*.txt/\1 state\.txt/' > test/tmp2.patch