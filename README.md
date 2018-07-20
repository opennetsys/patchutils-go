# go-patchutils

> Go bindings for [patchutils](https://github.com/twaugh/patchutils)

Currently only supports `combinediff`

```go
package main

import (
	"io"
	"log"
	"os"

	"github.com/miguelmota/go-patchutils"
)

func main() {
	out, err := patchutils.Combine("file1.patch", "file2.patch")
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

MIT
