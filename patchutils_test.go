package patchutils

import (
	"io/ioutil"
	"reflect"
	"testing"
)

func TestCombineDiff(t *testing.T) {
	out, err := CombineDiff("./test/tmp1.patch", "./test/tmp2.patch")
	if err != nil {
		t.Error(err)
	}

	b, err := ioutil.ReadAll(out)
	if err != nil {
		t.Error(err)
	}

	expected, err := ioutil.ReadFile("./test/combined.patch")

	if !reflect.DeepEqual(expected, b) {
		t.Errorf("expected\n%s\ngot\n%s", string(expected), string(b))
	}
}
