package patchutils

import (
	"io"

	"github.com/miguelmota/go-patchutils/wrapper"
)

// Combine ...
func Combine(filepathA, filepathB string) (io.Reader, error) {
	return wrapper.Combine(filepathA, filepathB)
}
