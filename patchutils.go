package patchutils

import (
	"io"

	"github.com/c3systems/go-patchutils/wrapper"
)

// CombineDiff ...
func CombineDiff(filepathA, filepathB string) (io.Reader, error) {
	return wrapper.CombineDiff(filepathA, filepathB)
}
