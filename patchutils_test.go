package patchutils

import (
	"io"
	"os"
	"testing"
)

func TestCombine(t *testing.T) {
	out, err := Combine("./test/tmp1.patch", "./test/tmp2.patch")
	if err != nil {
		t.Fatal(err)
	}

	io.Copy(os.Stdout, out)
}
