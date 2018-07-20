package main

import (
	"io"
	"log"
	"os"

	"github.com/c3systems/go-patchutils"
)

func main() {
	out, err := patchutils.CombineDiff("file1.patch", "file2.patch")
	if err != nil {
		log.Fatal(err)
	}

	io.Copy(os.Stdout, out)
}
