package patchutils

import (
	"io"

	"github.com/miguelmota/go-patchutils/wrapper"
)

// CombineDiff ...
func CombineDiff(filepathA, filepathB string) (io.Reader, error) {
	return wrapper.CombineDiff(filepathA, filepathB)
}
