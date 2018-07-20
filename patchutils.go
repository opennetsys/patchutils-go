package patchutils

/*
#cgo CFLAGS: -g -O2 -Wall
#include "wrapper.c"
*/
import "C"
import (
	"bufio"
	"errors"
	"io"
	"os"
	"strings"
)

// Combine ...
func Combine(filepathA, filepathB string) (io.Reader, error) {

	fp := C.combine_diff(C.CString(filepathA), C.CString(filepathB))

	filepath := C.GoString(fp)

	if strings.HasPrefix(filepath, "error:") {
		return nil, errors.New(strings.Replace(filepath, "error: ", "", -1))
	}

	file, err := os.Open(filepath)
	if err != nil {
		return nil, err
	}

	return bufio.NewReader(file), nil
}
