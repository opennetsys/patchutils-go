# go-patchutils

> Go bindings for [patchutils](https://github.com/twaugh/patchutils)

[![License](http://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/c3systems/go-patchutils/master/LICENSE.md) [![Build Status](https://travis-ci.org/c3systems/go-patchutils.svg?branch=master)](https://travis-ci.org/c3systems/go-patchutils) [![Go Report Card](https://goreportcard.com/badge/github.com/c3systems/go-patchutils?)](https://goreportcard.com/report/github.com/c3systems/go-patchutils) [![GoDoc](https://godoc.org/github.com/c3systems/go-patchutils?status.svg)](https://godoc.org/github.com/c3systems/go-patchutils)

## Install

```bash
go get -u github.com/c3systems/go-patchutils
```

## Usage

Currently only supports the `combinediff` command from patchutils.

```go
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
```

## Test

```bash
make test
```

## License

go-patchutils and patchutils are licensed under GNU GPL V2.
