package patchutils

/*
#cgo CFLAGS: -g -O2 -Wall
#include "wrapper.c"
*/
import "C"
import (
	"bytes"
	"fmt"
	"io"
)

// Combine ...
func Combine(filepathA, filepathB string) (io.Reader, error) {

	exitCode := C.Combine(C.CString(filepathA), C.CString(filepathB))
	if exitCode != 0 {
		return nil, fmt.Errorf("exit %v", exitCode)
	}

	//io.Copy(os.Stdout, C.stdout)

	b := []byte("TODO")
	out := bytes.NewReader(b)

	return out, nil
}
